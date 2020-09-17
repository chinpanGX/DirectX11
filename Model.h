/*-------------------------------------------------------------

	[Model.h]
	Author : 出合翔太

--------------------------------------------------------------*/
#pragma once
#include <vector>

// マテリアル構造体
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
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
	VERTEX_3D		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};


class Model
{
private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
	SUBSET* m_SubsetArray;
	unsigned int m_SubsetNum;

	void LaodObject(const char* FileName, MODEL* Model);
	void LaodMaterial(const char* FileName, MODEL_MATERIAL** MaterialArray, unsigned int* MaterialNum);
public:
	static std::vector<std::string> m_FileName;
	enum ModelFileName
	{

	};

	static void Init();
	void Draw();
	void Load(const char* FileName);
	void Unload();
	D3DXCOLOR GetColor() { return m_SubsetArray->Material.Material.Diffuse; }
	void SetColor(D3DXCOLOR Color) {  m_SubsetArray->Material.Material.Diffuse = Color; }
};

