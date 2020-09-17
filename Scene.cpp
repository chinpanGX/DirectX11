/*--------------------------------------------------------------

	[Scene.h]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Scene.h"
#include "Player.h"
#include "Camera.h"

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
#pragma endregion Gameクラスの定義