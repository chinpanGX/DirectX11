/*----------------------------------------------------------

	[Manager.cpp]
	Author : �o���đ�

-----------------------------------------------------------*/
#include "Manager.h"
#include <time.h>
#include "Model.h"
#include "Scene.h"
#include "Bg.h"

// �X�^�e�B�b�N�ϐ�
Scene* Manager::m_Scene = NULL;
Fade Manager::m_Fade;
DirectX11Wrapper::DirectX11& Manager::m_dx = DirectX11Wrapper::DirectX11::Instance();

#pragma region Define_AppManager_Func
// ������
void Manager::Init()
{
	srand((unsigned int)time(NULL));
	m_dx.Init();
	Model::Init();
	m_Fade.Init();
	SetScene<Title>();
	m_Fade.m_FadeState = m_Fade.FADE_IN;
	ChangeScene(m_Fade.m_NextScene);
}

// �I������
void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;
	m_dx.Uninit();
}

// �X�V����
void Manager::Update()
{
	m_Fade.Update();
	m_Scene->Update();
}

// �`�揈��
void Manager::Draw()
{
	m_dx.Begin();
	//3D�p���C�g�ݒ�
	DirectX11Wrapper::LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_dx.SetLight(light);
	m_Scene->Draw();
	m_Fade.Draw();
	m_dx.End();
}

// ��ʑJ��
void Manager::ChangeScene(Scene * scene)
{
	if (m_Scene)
	{
		m_Scene->Uninit();
		delete m_Scene;
	}
	m_Scene = scene;
	scene->Init();
}
#pragma endregion AppManager�̊֐���`

