/*--------------------------------------------------------------

	[Player.cpp]


---------------------------------------------------------------*/
#include "Player.h"
#include "Model.h"
#include "Renderer.h"

void Player::Init()
{
	m_Model = new Model();
	m_Model->Load(Model::m_FileName[Model::MODEL_PLAYER].c_str());
	assert(m_Model);
	m_Model->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_Position = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXQuaternionIdentity(&m_Quaternion);
}

void Player::Uninit()
{
	m_Model->Unload();
	delete m_Model;
}

void Player::Update()
{
}

void Player::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	//D3DXMatrixRotationQuaternion(&rot,&m_Quaternion);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
