/*-------------------------------------------------------------
	
	[Texture.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include "Application.h"

class Texture
{
private:
	unsigned int m_ImageCount = 0; // テクスチャをカウント
	ID3D11ShaderResourceView* m_Texture[256]; 
public:
	Texture();
	~Texture() {};
	unsigned int LoadTexture(const char* FileName); // ロード
	void Unload(unsigned int Texture);				// アンロード
	ID3D11ShaderResourceView* SetTexture(unsigned int Texture); // セット
};

class Sprite
{
private:
	ID3D11Buffer* m_VtxBuffer = NULL;
	float m_Alpha = 1.0f;
public:
	void Init();
	void Uninit();
	// DrawPosition : 実際に描画する画像の中心座標、DrawSize : 実際に描画するが画像サイズ、TexUpLeft,TexDownRight : 描画する元画像の大きさ,MAX1.0f
	void Draw(ID3D11ShaderResourceView* texture, D3DXVECTOR2 drawPosition, D3DXVECTOR2 drawSize, D3DXVECTOR2 texUpLeft, D3DXVECTOR2 texDownRight, D3DXCOLOR color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	void SetAlpha(float alpha) { m_Alpha = alpha; }
};
