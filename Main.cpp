/*--------------------------------------------------------------

	[Main.cpp]
	Author : èoçá„ƒëæ

---------------------------------------------------------------*/
#include <windows.h>
#include "Application.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto& app = Application::Instance();
	if (!app.Init(hInstance))
	{
		return -1;
	}
	app.AppRun();
	app.Uninit();
	return 0;
}

