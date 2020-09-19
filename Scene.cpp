/*--------------------------------------------------------------

	[Scene.h]
	シーン関連の処理を管理
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Scene.h"
#include "Player.h"
#include "Camera.h"
#include "Bg.h"
#include "InputDevice.h"
#include "AppManager.h"
#include "Renderer.h"

// スタティック変数
Scene* Fade::m_NextScene = NULL;

#pragma region Define_Fade_Func
void Fade::Init()
{
	m_Sprite.Init();
	m_Storage = m_Texture.LoadTexture("asset/Texture/black.png");
}

void Fade::Uninit()
{
	m_Sprite.Uninit();
	m_Texture.Unload(m_Storage);
}

void Fade::Update()
{
	switch (m_FadeState)
	{
	case FADE_OUT:
		m_Alpha += 0.025f;
		if (m_Alpha > 1.0f)
		{
			AppManager::ChangeScene(m_NextScene);
			m_FadeState = FADE_IN;
		}
		break;
	case FADE_IN:
		m_Alpha -= 0.025f;
		if (m_Alpha < 0.0f)
		{
			m_FadeState = FADE_NONE;
		}
		break;
	}
}

void Fade::Draw()
{
	m_Sprite.Draw(m_Texture.SetTexture(m_Storage), BG::GetScrren() * 0.5f, BG::GetScrren(), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,m_Alpha));
}
#pragma endregion Fadeの関数定義

#pragma region Define_Game_Func
// ロード
void Game::Load()
{
	
}

// アンロード
void Game::Unload()
{
}

// 初期化
void Game::Init()
{
	Load();
	AddGameObject<Player>(LAYER_3D)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -5.0f));
	AddGameObject<Camera>(LAYER_CAMERA);
}

// 更新
void Game::Update()
{
	Scene::Update();
}

// 描画
void Game::Draw()
{
	Scene::Draw();
}
#pragma endregion Gameクラスの関数定義

#pragma region Define_Title_Func
void Title::Load()
{
}

void Title::Unload()
{
}

void Title::Init()
{
	AddGameObject<TitleBG>(LAYER_2D);
}

void Title::Uninit()
{
	
}

void Title::Update()
{
	Scene::Update();
	if (KeyBoard::IsTrigger(DIK_T) || GamePad::IsTrigger(0,BUTTON_2))
	{
		AppManager::SetScene<Game>();
	}
}

void Title::Draw()
{
	Scene::Draw();
}
#pragma endregion Titleのクラスの関数定義
