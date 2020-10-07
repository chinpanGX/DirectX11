/*---------------------------------------------------------

	[Application.h]
	Author : �o���đ�

----------------------------------------------------------*/
#pragma once
#include <Windows.h>

class Application
{
private:
	WNDCLASSEX	m_WindowClass;
	HWND		m_hWnd;

	void CreateGameWindow(HWND& hwnd, WNDCLASSEX& windowClass); // �Q�[���p�E�B���h�E
	Application() {};	// �R���X�g���N�^
	// �R�s�[�Ƒ�����֎~
	Application(const Application&) = delete;
	void operator= (const Application&) = delete;

public:
	static Application& Instance(); // �C���X�^���X����
	bool Init(HINSTANCE hInstance);					// ������
	void AppRun();					// �A�v�����[�v
	void Uninit();					// �I������
	SIZE GetWindowSize()const;
	HWND Gethwnd()const { return m_hWnd; }
	~Application() {};
};

