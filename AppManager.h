/*--------------------------------------------------------------
	
	[AppManager.h]
	Author : �o���đ�

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

