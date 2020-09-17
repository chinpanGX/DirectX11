/*--------------------------------------------------------------

	[Camera.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Camera.h"
#include "Renderer.h"
#include "Application.h"

// 初期化
void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 2.0f, -1.0f);
	m_Target = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

void Camera::Update()
{

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
