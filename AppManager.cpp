/*--------------------------------------------------------------

	[AppManager.cpp]
	ゲームアプリ、フェードを管理
	Author : 出合翔太

---------------------------------------------------------------*/
#include "AppManager.h"
#include <time.h>
#include "Model.h"

// スタティック変数
Scene* AppManager::m_Scene = NULL;
Fade AppManager::m_Fade;

#pragma region Define_AppManager_Func
// 初期化
void AppManager::Init()
{
	srand((unsigned int)time(NULL));
	Renderer::Init();
	Model::Init();
	m_Fade.Init();
	SetScene<Title>();
	m_Fade.m_FadeState = m_Fade.FADE_IN;
	ChangeScene(m_Fade.m_NextScene);
}

// 終了処理
void AppManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;
	Renderer::Uninit();
}

// 更新処理
void AppManager::Update()
{
	m_Fade.Update();
	m_Scene->Update();
}

// 描画処理
void AppManager::Draw()
{
	Renderer::Begin();
	//3D用ライト設定
	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetLight(light);
	m_Scene->Draw();
	m_Fade.Draw();
	Renderer::End();
}

// 画面遷移
void AppManager::ChangeScene(Scene * scene)
{
	if (m_Scene)
	{
		m_Scene->Uninit();
		delete m_Scene;
	}
	m_Scene = scene;
	scene->Init();
}

#pragma endregion AppManagerの関数定義
