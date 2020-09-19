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
#include "AppManager.h"
#include "Renderer.h"

// �X�^�e�B�b�N�ϐ�
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
#pragma endregion Fade�̊֐���`

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
	if (KeyBoard::IsTrigger(DIK_T) || GamePad::IsTrigger(0,BUTTON_2))
	{
		AppManager::SetScene<Game>();
	}
}

void Title::Draw()
{
	Scene::Draw();
}
#pragma endregion Title�̃N���X�̊֐���`
