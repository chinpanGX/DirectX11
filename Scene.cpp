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
#include "Manager.h"

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
	if (KeyBoard::IsTrigger(DIK_T) || GamePad::IsTrigger(0,BTN_2))
	{
		Manager::SetScene<Game>();
	}
}

void Title::Draw()
{
	Scene::Draw();
}
#pragma endregion Titleのクラスの関数定義
