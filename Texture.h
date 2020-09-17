/*-------------------------------------------------------------
	
	[Texture.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include "BaseGameObject.h"

class Texture
{
private:
	static const unsigned int m_TextureNum = 1;		   // テクスチャの数
	unsigned int m_ImageCount = 0;					   // テクスチャをカウント
	ID3D11ShaderResourceView* m_Texture[m_TextureNum]; 
	float m_Alpha = 1.0f;

public:
	Texture() { m_Texture[m_TextureNum] = NULL; };
	~Texture() {};
	unsigned int LoadTexture(const char* FileName); // ロード
	void Unload(unsigned int Texture);				// アンロード
	// DrawPosition : 実際に描画する画像の中心座標、DrawSize : 実際に描画するが画像サイズ、TexUpLeft,TexDownRight : 描画する元画像の大きさ,MAX1.0f
	void Draw(unsigned int Texture, ID3D11Buffer* VertexBuffer, D3DXVECTOR2 DrawPosition, D3DXVECTOR2 DrawSize, D3DXVECTOR2 TexUpLeft, D3DXVECTOR2 TexDownRight);
	void SetAlpha(float alpha) { m_Alpha = alpha; }
};

