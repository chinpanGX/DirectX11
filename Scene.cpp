/*--------------------------------------------------------------

	[Scene.h]
	�V�[���֘A�̏������Ǘ�
	Author : �o���đ�

---------------------------------------------------------------*/
#include "Scene.h"
#include "Player.h"
#include "Camera.h"
#include "Bg.h"
#include "InputDevice.h"
#include "Manager.h"

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
#pragma endregion Game�N���X�̊֐���`

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
#pragma endregion Title�̃N���X�̊֐���`
