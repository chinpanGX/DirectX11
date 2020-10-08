/*-------------------------------------------------------------

	[Model.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include <vector>
#include "DirectX11Wrapper.h"

// マテリアル構造体
struct MODEL_MATERIAL
{
	char						Name[256];
	DirectX11Wrapper::MATERIAL	Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;

};

// 描画サブセット構造体
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


// モデル構造体
struct MODEL
{
	DirectX11Wrapper::VERTEX_3D		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};


class Model
{
private:
	DirectX11Wrapper::DirectX11& m_dx = DirectX11Wrapper::DirectX11::Instance();
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
	SUBSET* m_SubsetArray;
	unsigned int m_SubsetNum;

	void LoadObject(const char* FileName, MODEL* Model);
	void LoadMaterial(const char* FileName, MODEL_MATERIAL** MaterialArray, unsigned int* MaterialNum);
public:
	static std::vector<std::string> m_FileName;
	enum ModelFileName
	{
		MODEL_BULLET,
		MODEL_CUBE,
		MODEL_ENEMY01,
		MODEL_ENEMY02,
		MODEL_ENEMY03,
		MODEL_PLAYER,
		MODEL_STAGE,
		MODEL_SKYBOX,
	};

	static void Init();
	void Draw();
	void Load(const char* FileName);
	void Unload();
	D3DXCOLOR GetColor() { return m_SubsetArray->Material.Material.Diffuse; }
	void SetColor(D3DXCOLOR Color) {  m_SubsetArray->Material.Material.Diffuse = Color; }
};

