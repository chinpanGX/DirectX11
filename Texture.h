/*-------------------------------------------------------------
	
	[Texture.h]
	Author : �o���đ�

--------------------------------------------------------------*/
#pragma once
#include "Application.h"

class Texture
{
private:
	unsigned int m_ImageCount = 0; // �e�N�X�`�����J�E���g
	ID3D11ShaderResourceView* m_Texture[256]; 
public:
	Texture();
	~Texture() {};
	unsigned int LoadTexture(const char* FileName); // ���[�h
	void Unload(unsigned int Texture);				// �A�����[�h
	ID3D11ShaderResourceView* SetTexture(unsigned int Texture); // �Z�b�g
};

class Sprite
{
private:
	ID3D11Buffer* m_VtxBuffer = NULL;
	float m_Alpha = 1.0f;
public:
	void Init();
	void Uninit();
	// DrawPosition : ���ۂɕ`�悷��摜�̒��S���W�ADrawSize : ���ۂɕ`�悷�邪�摜�T�C�Y�ATexUpLeft,TexDownRight : �`�悷�錳�摜�̑傫��,MAX1.0f
	void Draw(ID3D11ShaderResourceView* texture, D3DXVECTOR2 drawPosition, D3DXVECTOR2 drawSize, D3DXVECTOR2 texUpLeft, D3DXVECTOR2 texDownRight, D3DXCOLOR color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	void SetAlpha(float alpha) { m_Alpha = alpha; }
};
