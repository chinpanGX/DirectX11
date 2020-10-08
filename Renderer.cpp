/*-------------------------------------------------------------

	[Renderer.cpp]
	Author : �o���đ�

--------------------------------------------------------------*/
#include "Renderer.h"
#include "Application.h"

using namespace DirectX11Wrapper;

#pragma region Define_Texture_Func
Texture::Texture()
{
	m_Texture[256] = NULL;
}

// ���[�h
unsigned int Texture::LoadTexture(DirectX11& dx, const char * FileName)
{
	unsigned int texture = 0;
	D3DX11CreateShaderResourceViewFromFile(dx.GetDevice(), FileName, NULL, NULL, &m_Texture[m_ImageCount++], NULL);
	texture = m_ImageCount - 1;
	return texture;
}

// �A�����[�h
void Texture::Unload(unsigned int Texture)
{
	m_Texture[Texture]->Release();
}

// �Z�b�g
ID3D11ShaderResourceView* Texture::SetTexture(unsigned int Texture)
{
	return m_Texture[Texture];
}
#pragma endregion Texture�N���X�̊֐���`


#pragma region Define_Sprite_Func
void Sprite::Init(DirectX11& dx)
{
	VERTEX_3D vertex[4];
	{
		vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(10.0f, 0.0f);

		vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, 10.0f);

		vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(10.0f, 10.0f);
	}

	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	dx.GetDevice()->CreateBuffer(&bd, &sd, &m_VtxBuffer);
}

void Sprite::Uninit()
{
	m_VtxBuffer->Release();
}

void Sprite::Draw(DirectX11& dx, ID3D11ShaderResourceView * texture, D3DXVECTOR2 drawPosition, D3DXVECTOR2 drawSize, D3DXVECTOR2 texUpLeft, D3DXVECTOR2 texDownRight, D3DXCOLOR color)
{
	//���C�g����
	LIGHT light;
	light.Enable = false;
	dx.SetLight(light);

	D3D11_MAPPED_SUBRESOURCE msr;
	dx.GetDeviceContext()->Map(m_VtxBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(drawPosition.x - drawSize.x * 0.5f, drawPosition.y - drawSize.y * 0.5f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = texUpLeft;

	vertex[1].Position = D3DXVECTOR3(drawPosition.x + drawSize.x * 0.5f, drawPosition.y - drawSize.y * 0.5f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(texDownRight.x, texUpLeft.y);

	vertex[2].Position = D3DXVECTOR3(drawPosition.x - drawSize.x * 0.5f, drawPosition.y + drawSize.y * 0.5f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(texUpLeft.x, texDownRight.y);

	vertex[3].Position = D3DXVECTOR3(drawPosition.x + drawSize.x * 0.5f, drawPosition.y + drawSize.y * 0.5f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = texDownRight;

	dx.GetDeviceContext()->Unmap(m_VtxBuffer, 0);

	//�}�g���N�X�ݒ�
	dx.SetWorldViewProjection2D();

	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	dx.GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VtxBuffer, &stride, &offset);

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = color;
	dx.SetMaterial(material);

	//�e�N�X�`���ݒ�
	dx.GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	dx.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	dx.GetDeviceContext()->Draw(4, 0);

	//�ύX��͖߂��Ă���
	m_Alpha = 1.0f;
}
#pragma endregion Sprite�N���X�̊֐���`


#pragma region Spriterenderer_Func
// ���[�h
void SpriteRenderer::Load(const char * Filename)
{
	m_Sprite.Init(m_dx);
	m_Storage = m_Texture.LoadTexture(m_dx, Filename);
}

// �A�����[�h
void SpriteRenderer::Unload()
{
	m_Sprite.Uninit();
	m_Texture.Unload(m_Storage);
}

// �`��
void SpriteRenderer::Draw(D3DXVECTOR2 drawPosition, D3DXVECTOR2 drawSize, D3DXVECTOR2 texUpLeft, D3DXVECTOR2 texDownRight, D3DXCOLOR color)
{
	m_Sprite.Draw(m_dx, m_Texture.SetTexture(m_Storage), drawPosition, drawSize, texUpLeft, texDownRight, color);
}

// ���l�̃Z�b�g
void SpriteRenderer::SetAlpha(float alpha)
{
	m_Sprite.SetAlpha(alpha);
}
#pragma endregion SpriteRenderer
