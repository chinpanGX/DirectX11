/*---------------------------------------------------------

	[Application.h]
	Author : �o���đ�

----------------------------------------------------------*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h> // �G���[����
#include <iostream>

#pragma warning(push)
#pragma warning(disable:4005)

// DirectX��API
#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>
// �Z�p���C�u����
#include <DirectXMath.h>
// �V�F�[�_�[�̃R���p�C��
#include <d3dcompiler.h>

#pragma warning(pop)

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

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

