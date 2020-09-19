/*---------------------------------------------------------

	[Application.h]
	Author : 出合翔太

----------------------------------------------------------*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h> // エラー処理
#include <iostream>

#pragma warning(push)
#pragma warning(disable:4005)

// DirectXのAPI
#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>
// 算術ライブラリ
#include <DirectXMath.h>
// シェーダーのコンパイラ
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

	void CreateGameWindow(HWND& hwnd, WNDCLASSEX& windowClass); // ゲーム用ウィンドウ
	Application() {};	// コンストラクタ
	// コピーと代入を禁止
	Application(const Application&) = delete;
	void operator= (const Application&) = delete;

public:
	static Application& Instance(); // インスタンス生成
	bool Init(HINSTANCE hInstance);					// 初期化
	void AppRun();					// アプリループ
	void Uninit();					// 終了処理
	SIZE GetWindowSize()const;
	HWND Gethwnd()const { return m_hWnd; }
	~Application() {};
};

