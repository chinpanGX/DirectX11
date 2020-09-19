/*--------------------------------------------------------------

	[Camera.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Camera.h"
#include "Renderer.h"
#include "AppManager.h"
#include "Player.h"
#include "InputDevice.h"

// 初期化
void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 2.0f, -1.0f);
	m_Target = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

void Camera::Update()
{
	/*
	Player* player = AppManager::GetScene()->GetGameObject<Player>(LAYER_3D);

	m_Target = player->GetPosition();
	m_Position = player->GetPosition() + player->GetVector(VECTOR_BACKWARD) * 4.0f + D3DXVECTOR3(0.0f, 2.0f, 0.0f);

	if (m_Position.x > 19.0f)
		m_Position.x = 19.0f;
	if (m_Position.x < -19.0f)
		m_Position.x = -19.0f;

	if (m_Position.z > 19.0f)
		m_Position.z = 19.0f;
	if (m_Position.z < -19.0f)
		m_Position.z = -19.0f;
		*/
	if (KeyBoard::IsPress(DIK_W))
	{
		m_Position.z -= 1.0f;
	}
	else if (KeyBoard::IsPress(DIK_S))
	{
		m_Position.z += 1.0f;
	}
	else if (KeyBoard::IsPress(DIK_A))
	{
		m_Position.x -= 1.0f;
	}
	else if (KeyBoard::IsPress(DIK_D))
	{
		m_Position.x += 1.0f;
	}
	else if(KeyBoard::IsPress(DIK_Q))
	{
		m_Position.y += 1.0f;
	}
	else if (KeyBoard::IsPress(DIK_E))
	{
		m_Position.y -= 1.0f;
	}
}

void Camera::Draw()
{
	//ビューマトリクス設定
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target,&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	Renderer::SetViewMatrix(&m_ViewMatrix);

	auto &app = Application::Instance();
	//プロジェクションマトリクス設定
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f,(float)app.GetWindowSize().cx / app.GetWindowSize().cy, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);
}
