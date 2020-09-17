/*------------------------------------------------------------

	[Texture.cpp]
	Author : �o���đ�

-------------------------------------------------------------*/
#include "Texture.h"
#include "Renderer.h"

// ���[�h
unsigned int Texture::LoadTexture(const char * FileName)
{
	unsigned int texture = 0;
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(), FileName, NULL, NULL, &m_Texture[m_ImageCount++], NULL);
	texture = m_ImageCount - 1;
	return texture;
}

// �A�����[�h
void Texture::Unload(unsigned int Texture)
{
	m_Texture[Texture]->Release();
}

// �`��
void Texture::Draw(unsigned int Texture, ID3D11Buffer * VertexBuffer, D3DXVECTOR2 DrawPosition, D3DXVECTOR2 DrawSize, D3DXVECTOR2 TexUpLeft, D3DXVECTOR2 TexDownRight)
{
	//���C�g����
	LIGHT light;
	light.Enable = false;
	Renderer::SetLight(light);

	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vtx = (VERTEX_3D*)msr.pData;
	vtx[0].Position = D3DXVECTOR3(DrawPosition.x -DrawSize.x * 0.5, DrawPosition.y - DrawSize.y * 0.5f,0.0f);
	vtx[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vtx[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vtx[0].TexCoord = TexUpLeft;

	vtx[1].Position = D3DXVECTOR3(DrawPosition.x + DrawSize.x * 0.5, DrawPosition.y - DrawSize.y * 0.5f, 0.0f);
	vtx[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vtx[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vtx[1].TexCoord = D3DXVECTOR2(TexDownRight.x, TexUpLeft.y);

	vtx[2].Position = D3DXVECTOR3(DrawPosition.x - DrawSize.x * 0.5, DrawPosition.y + DrawSize.y * 0.5f, 0.0f);
	vtx[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vtx[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vtx[2].TexCoord = D3DXVECTOR2(TexUpLeft.x, TexDownRight.y);

	vtx[3].Position = D3DXVECTOR3(DrawPosition.x - DrawSize.x * 0.5, DrawPosition.y - DrawSize.y * 0.5f, 0.0f);
	vtx[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vtx[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vtx[3].TexCoord = TexDownRight;

	Renderer::GetDeviceContext()->Unmap(VertexBuffer, 0);

	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Alpha);
	Renderer::SetMaterial(material);
	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSGetShaderResources(0, 1, &m_Texture[Texture]);
	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);
	//�ύX��͖߂��Ă���
	m_Alpha = 1.0f;
}
