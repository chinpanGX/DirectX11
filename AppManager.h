/*--------------------------------------------------------------
	
	[AppManager.h]
	Author : èoçá„ƒëæ

---------------------------------------------------------------*/
#pragma once

class AppManager
{
private:
	static class Scene* m_Scene;
	void SetLight();
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

