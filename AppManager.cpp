/*--------------------------------------------------------------

	[AppManager.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "AppManager.h"
#include <time.h>
#include "Renderer.h"
#include "Scene.h"

Scene* AppManager::m_Scene = NULL;

void AppManager::SetLight()
{
	//3D用ライト設定
	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetLight(light);
}

void AppManager::Init()
{
	srand((unsigned int)time(NULL));
	Renderer::Init();
	Model::Init();
}

void AppManager::Uninit()
{
	Renderer::Uninit();
}

void AppManager::Update()
{
	m_Scene->Update();
}

void AppManager::Draw()
{
	Renderer::Begin();
	SetLight();
	m_Scene->Draw();
	Renderer::End();
}
