/*---------------------------------------------------------

	[Application.h]
	Author : 出合翔太

----------------------------------------------------------*/
#pragma once
#include <Windows.h>

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

