/*--------------------------------------------------------------

	[Scene.h]
	Author : �o���đ�

---------------------------------------------------------------*/
#include "Scene.h"
#include "Player.h"
#include "Camera.h"

#pragma region Define_Game_Func
// ���[�h
void Game::Load()
{
	
}

// �A�����[�h
void Game::Unload()
{
}

// ������
void Game::Init()
{
	Load();
	AddGameObject<Player>(LAYER_3D)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -5.0f));
	AddGameObject<Camera>(LAYER_CAMERA);
}

// �X�V
void Game::Update()
{
	Scene::Update();
}

// �`��
void Game::Draw()
{
	Scene::Draw();
}
#pragma endregion Game�N���X�̒�`