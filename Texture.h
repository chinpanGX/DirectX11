/*-------------------------------------------------------------
	
	[Texture.h]
	Author : �o���đ�

--------------------------------------------------------------*/
#pragma once
#include "BaseGameObject.h"

class Texture
{
private:
	static const unsigned int m_TextureNum = 1;		   // �e�N�X�`���̐�
	unsigned int m_ImageCount = 0;					   // �e�N�X�`�����J�E���g
	ID3D11ShaderResourceView* m_Texture[m_TextureNum]; 
	float m_Alpha = 1.0f;

public:
	Texture() { m_Texture[m_TextureNum] = NULL; };
	~Texture() {};
	unsigned int LoadTexture(const char* FileName); // ���[�h
	void Unload(unsigned int Texture);				// �A�����[�h
	// DrawPosition : ���ۂɕ`�悷��摜�̒��S���W�ADrawSize : ���ۂɕ`�悷�邪�摜�T�C�Y�ATexUpLeft,TexDownRight : �`�悷�錳�摜�̑傫��,MAX1.0f
	void Draw(unsigned int Texture, ID3D11Buffer* VertexBuffer, D3DXVECTOR2 DrawPosition, D3DXVECTOR2 DrawSize, D3DXVECTOR2 TexUpLeft, D3DXVECTOR2 TexDownRight);
	void SetAlpha(float alpha) { m_Alpha = alpha; }
};

