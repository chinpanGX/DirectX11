/*---------------------------------------------------------

	[Application.h]
	Author : 出合翔太

----------------------------------------------------------*/
#include "Application.h"
#include "InputDevice.h"
#include "AppManager.h"

// グローバル変数
const unsigned int g_WindowWidth = 1280;
const unsigned int g_WindowHeight = 720;

// ウィンドウプロシージャ
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
	// ウィンドウの生成＆登録
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.lpfnWndProc = (WNDPROC)WndProc; // コールバック関数の指定
	windowClass.lpszClassName = "Dx11";			// アプリケーション名
	windowClass.hInstance = GetModuleHandle(0);	// ハンドルの指定
	RegisterClassEx(&windowClass);				// アプリケーションクラス
	RECT wrc = { 0,0,g_WindowWidth, g_WindowHeight };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
	// ウィンドウオブジェクトの生成
	hwnd = CreateWindow(windowClass.lpszClassName,	// クラス名
		"ゲームアプリ",								// タイトルバー
		WS_OVERLAPPEDWINDOW,						// ウィンドウタイプ
		CW_USEDEFAULT, CW_USEDEFAULT,				// 表示xy座標はOSに任せる
		wrc.right - wrc.left, wrc.bottom - wrc.top, // ウィンドウ幅と高さ
		NULL, NULL, windowClass.hInstance, NULL);	// ウィンドウハンドル, メニューハンドル,呼び出しアプリケーションハンドル, 追加パラメータ
}

Application & Application::Instance()
{
	static Application instance;
	return instance;
}

bool Application::Init(HINSTANCE hInstance)
{
	auto result = CoInitializeEx(0, COINITBASE_MULTITHREADED);
	CreateGameWindow(m_hWnd, m_WindowClass); // ゲームウィンドウ
	InputDevice::Init(hInstance,m_hWnd); // コントローラの初期化
	return true;
}

void Application::AppRun()
{
	// ウィンドウ表示
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	// フレームカウントの初期化
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;

	AppManager::Init();

	// メッセージループ
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) // PostQuitMessage()が呼ばれたらループ終了
			{
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
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
				// 更新処理
				InputDevice::Update(); // コントローラの更新
				AppManager::Update();
				// 描画処理
				AppManager::Draw();
			}
		}
	}
}

void Application::Uninit()
{
	AppManager::Uninit();
	InputDevice::Uninit();  // コントローラの終了処理 
	timeEndPeriod(1); // 分解能を戻す
	UnregisterClass(m_WindowClass.lpszClassName, m_WindowClass.hInstance); // ウィンドウクラスの登録を解除
}

SIZE Application::GetWindowSize() const
{
	SIZE ret;
	ret.cx = g_WindowWidth;
	ret.cy = g_WindowHeight;
	return ret;
}