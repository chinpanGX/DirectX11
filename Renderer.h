/*------------------------------------------------------------
	
	[Renderer.h]
	2D�`��p�̃N���X : Texture,Sprite,SpriteRenderer
	Author : �o���đ�

-------------------------------------------------------------*/
#pragma once
#include "DirectX11Wrapper.h"

// �e�N�X�`���N���X�c�e�N�X�`���̊Ǘ�
class Texture
{
private:
	unsigned int m_ImageCount = 0; // �e�N�X�`�����J�E���g
	ID3D11ShaderResourceView* m_Texture[256];
public:
	Texture();
	~Texture() {};
	unsigned int LoadTexture(DirectX11Wrapper::DirectX11& dx, const char* FileName); // ���[�h
	void Unload(unsigned int Texture);				// �A�����[�h
	ID3D11ShaderResourceView* SetTexture(unsigned int Texture); // �Z�b�g
};

// �X�v���C�g�c�o�b�t�@��`��̏������Ǘ�
class Sprite
{
private:
	ID3D11Buffer* m_VtxBuffer = NULL;
	float m_Alpha = 1.0f;
public:
	void Init(DirectX11Wrapper::DirectX11& dx);
	void Uninit();
	// DrawPosition : ���ۂɕ`�悷��摜�̒��S���W�ADrawSize : ���ۂɕ`�悷�邪�摜�T�C�Y�ATexUpLeft,TexDownRight : �`�悷�錳�摜�̑傫��,MAX1.0f
	void Draw(DirectX11Wrapper::DirectX11& dx, ID3D11ShaderResourceView* texture, D3DXVECTOR2 drawPosition, D3DXVECTOR2 drawSize, D3DXVECTOR2 texUpLeft, 
		D3DXVECTOR2 texDownRight, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	void SetAlpha(float alpha) { m_Alpha = alpha; }
};


#pragma region Class_SpriteRenderer
// 2D�p�X�v���C�g�����_���[�c�e�N�X�`���A�X�v���C�g���܂Ƃ߂��N���X
class SpriteRenderer
{
private:
	unsigned int m_Storage;
	DirectX11Wrapper::DirectX11& m_dx = DirectX11Wrapper::DirectX11::Instance();
	Texture m_Texture;
	Sprite m_Sprite;
public:
	void Load(const char* Filename);
	void Unload();
	void Draw(D3DXVECTOR2 drawPosition, D3DXVECTOR2 drawSize, D3DXVECTOR2 texUpLeft, D3DXVECTOR2 texDownRight, D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	void SetAlpha(float alpha);
};
#pragma endregion 2D�p�X�v���C�g�����_���[

