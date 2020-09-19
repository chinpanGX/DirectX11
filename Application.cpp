/*---------------------------------------------------------

	[Application.h]
	Author : �o���đ�

----------------------------------------------------------*/
#include "Application.h"
#include "InputDevice.h"
#include "AppManager.h"

// �O���[�o���ϐ�
const unsigned int g_WindowWidth = 1280;
const unsigned int g_WindowHeight = 720;

// �E�B���h�E�v���V�[�W��
LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Application::CreateGameWindow(HWND & hwnd, WNDCLASSEX & windowClass)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	// �E�B���h�E�̐������o�^
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.lpfnWndProc = (WNDPROC)WndProc; // �R�[���o�b�N�֐��̎w��
	windowClass.lpszClassName = "Dx11";			// �A�v���P�[�V������
	windowClass.hInstance = GetModuleHandle(0);	// �n���h���̎w��
	RegisterClassEx(&windowClass);				// �A�v���P�[�V�����N���X
	RECT wrc = { 0,0,g_WindowWidth, g_WindowHeight };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
	// �E�B���h�E�I�u�W�F�N�g�̐���
	hwnd = CreateWindow(windowClass.lpszClassName,	// �N���X��
		"�Q�[���A�v��",								// �^�C�g���o�[
		WS_OVERLAPPEDWINDOW,						// �E�B���h�E�^�C�v
		CW_USEDEFAULT, CW_USEDEFAULT,				// �\��xy���W��OS�ɔC����
		wrc.right - wrc.left, wrc.bottom - wrc.top, // �E�B���h�E���ƍ���
		NULL, NULL, windowClass.hInstance, NULL);	// �E�B���h�E�n���h��, ���j���[�n���h��,�Ăяo���A�v���P�[�V�����n���h��, �ǉ��p�����[�^
}

Application & Application::Instance()
{
	static Application instance;
	return instance;
}

bool Application::Init(HINSTANCE hInstance)
{
	auto result = CoInitializeEx(0, COINITBASE_MULTITHREADED);
	CreateGameWindow(m_hWnd, m_WindowClass); // �Q�[���E�B���h�E
	InputDevice::Init(hInstance,m_hWnd); // �R���g���[���̏�����
	return true;
}

void Application::AppRun()
{
	// �E�B���h�E�\��
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	// �t���[���J�E���g�̏�����
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;

	AppManager::Init();

	// ���b�Z�[�W���[�v
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) // PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
			{
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;
				// �X�V����
				InputDevice::Update(); // �R���g���[���̍X�V
				AppManager::Update();
				// �`�揈��
				AppManager::Draw();
			}
		}
	}
}

void Application::Uninit()
{
	AppManager::Uninit();
	InputDevice::Uninit();  // �R���g���[���̏I������ 
	timeEndPeriod(1); // ����\��߂�
	UnregisterClass(m_WindowClass.lpszClassName, m_WindowClass.hInstance); // �E�B���h�E�N���X�̓o�^������
}

SIZE Application::GetWindowSize() const
{
	SIZE ret;
	ret.cx = g_WindowWidth;
	ret.cy = g_WindowHeight;
	return ret;
}