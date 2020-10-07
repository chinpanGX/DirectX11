/*------------------------------------------------------------

	[Model.cpp]
	Author : 出合翔太

--------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include "Application.h"
#include "Model.h"
#include "Renderer.h"

std::vector<std::string> Model::m_FileName{};

#pragma region Load_HelperFunc
// モデルの読み込み
void Model::LoadObject(const char * FileName, MODEL * Model)
{
	char dir[MAX_PATH];
	strcpy(dir, FileName);
	PathRemoveFileSpec(dir); // パスからファイル名を取り除く
	
	D3DXVECTOR3	*positionArray;
	D3DXVECTOR3	*normalArray;
	D3DXVECTOR2	*texcoordArray;

	unsigned int	positionNum = 0;
	unsigned int	normalNum = 0;
	unsigned int	texcoordNum = 0;
	unsigned int	vertexNum = 0;
	unsigned int	indexNum = 0;
	unsigned int	in = 0;
	unsigned int	subsetNum = 0;

	MODEL_MATERIAL	*materialArray = NULL;
	unsigned int	materialNum = 0;

	char str[256];
	char *s;
	char c;

	FILE *file;
	file = fopen(FileName, "rt");
	assert(file);
	   
	//要素数カウント
	while (true)
	{
		fscanf(file, "%s", str);
		if (feof(file) != 0)
		{
			break;
		}
		// 文字列の比較して一致するかどうか
		if (strcmp(str, "v") == 0)
		{
			positionNum++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			normalNum++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			texcoordNum++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			subsetNum++;
		}
		else if (strcmp(str, "f") == 0)
		{
			in = 0;
			do
			{
				fscanf(file, "%s", str);
				vertexNum++;
				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//四角は三角に分割
			if (in == 4)
				in = 6;

			indexNum += in;
		}
	}


	//メモリ確保
	positionArray = new D3DXVECTOR3[positionNum];
	normalArray = new D3DXVECTOR3[normalNum];
	texcoordArray = new D3DXVECTOR2[texcoordNum];
	Model->VertexArray = new VERTEX_3D[vertexNum];
	Model->VertexNum = vertexNum;
	Model->IndexArray = new unsigned int[indexNum];
	Model->IndexNum = indexNum;
	Model->SubsetArray = new SUBSET[subsetNum];
	Model->SubsetNum = subsetNum;
	   	 
	//要素読込
	D3DXVECTOR3 *position = positionArray;
	D3DXVECTOR3 *normal = normalArray;
	D3DXVECTOR2 *texcoord = texcoordArray;

	unsigned int vc = 0;
	unsigned int ic = 0;
	unsigned int sc = 0;
	
	fseek(file, 0, SEEK_SET);

	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;

		if (strcmp(str, "mtllib") == 0)
		{
			//マテリアルファイル
			fscanf(file, "%s", str);

			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);

			LoadMaterial(path, &materialArray, &materialNum);
		}
		else if (strcmp(str, "o") == 0)
		{
			//オブジェクト名
			fscanf(file, "%s", str);
		}
		else if (strcmp(str, "v") == 0)
		{
			//頂点座標
			fscanf(file, "%f", &position->x);
			fscanf(file, "%f", &position->y);
			fscanf(file, "%f", &position->z);
			position++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			//法線
			fscanf(file, "%f", &normal->x);
			fscanf(file, "%f", &normal->y);
			fscanf(file, "%f", &normal->z);
			normal++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			//テクスチャ座標
			fscanf(file, "%f", &texcoord->x);
			fscanf(file, "%f", &texcoord->y);
			texcoord->y = 1.0f - texcoord->y;
			texcoord++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			//マテリアル
			fscanf(file, "%s", str);

			if (sc != 0)
				Model->SubsetArray[sc - 1].IndexNum = ic - Model->SubsetArray[sc - 1].StartIndex;

			Model->SubsetArray[sc].StartIndex = ic;


			for (unsigned int i = 0; i < materialNum; i++)
			{
				if (strcmp(str, materialArray[i].Name) == 0)
				{
					Model->SubsetArray[sc].Material.Material = materialArray[i].Material;
					strcpy(Model->SubsetArray[sc].Material.TextureName, materialArray[i].TextureName);
					strcpy(Model->SubsetArray[sc].Material.Name, materialArray[i].Name);

					break;
				}
			}

			sc++;

		}
		else if (strcmp(str, "f") == 0)
		{
			//面
			in = 0;
			do
			{
				fscanf(file, "%s", str);
				s = strtok(str, "/");
				Model->VertexArray[vc].Position = positionArray[atoi(s) - 1];
				if (s[strlen(s) + 1] != '/')
				{
					//テクスチャ座標が存在しない場合もある
					s = strtok(NULL, "/");
					Model->VertexArray[vc].TexCoord = texcoordArray[atoi(s) - 1];
				}
				s = strtok(NULL, "/");
				Model->VertexArray[vc].Normal = normalArray[atoi(s) - 1];
				Model->VertexArray[vc].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				Model->IndexArray[ic] = vc;
				ic++;
				vc++;
				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//四角は三角に分割
			if (in == 4)
			{
				Model->IndexArray[ic] = vc - 4;
				ic++;
				Model->IndexArray[ic] = vc - 2;
				ic++;
			}
		}
	}
	if (sc != 0)
	{
		Model->SubsetArray[sc - 1].IndexNum = ic - Model->SubsetArray[sc - 1].StartIndex;
	}
	delete[] positionArray;
	delete[] normalArray;
	delete[] texcoordArray;
	delete[] materialArray;
}

// マテリアル読み込み
void Model::LoadMaterial(const char * FileName, MODEL_MATERIAL ** MaterialArray, unsigned int * MaterialNum)
{
	char dir[MAX_PATH];
	strcpy(dir, FileName);
	PathRemoveFileSpec(dir);
	char str[256];
	FILE *file;
	file = fopen( FileName, "rt" );
	assert(file);

	MODEL_MATERIAL *materialArray;
	unsigned int materialNum = 0;

	//要素数カウント
	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
		{
			break;
		}
		if (strcmp(str, "newmtl") == 0)
		{
			materialNum++;
		}
	}
	//メモリ確保
	materialArray = new MODEL_MATERIAL[ materialNum ];
	//要素読込
	int mc = -1;
	fseek( file, 0, SEEK_SET );
	while( true )
	{
		fscanf( file, "%s", str );
		if (feof(file) != 0)
		{
			break;
		}
		if( strcmp( str, "newmtl" ) == 0 )
		{
			//マテリアル名
			mc++;
			fscanf( file, "%s", materialArray[ mc ].Name );
			strcpy( materialArray[ mc ].TextureName, "" );
			materialArray[mc].Material.Emission.r = 0.0f;
			materialArray[mc].Material.Emission.g = 0.0f;
			materialArray[mc].Material.Emission.b = 0.0f;
			materialArray[mc].Material.Emission.a = 0.0f;
		}
		else if( strcmp( str, "Ka" ) == 0 )
		{
			//アンビエント
			fscanf( file, "%f", &materialArray[ mc ].Material.Ambient.r );
			fscanf( file, "%f", &materialArray[ mc ].Material.Ambient.g );
			fscanf( file, "%f", &materialArray[ mc ].Material.Ambient.b );
			materialArray[ mc ].Material.Ambient.a = 1.0f;
		}
		else if( strcmp( str, "Kd" ) == 0 )
		{
			//ディフューズ
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.r );
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.g );
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.b );
			materialArray[ mc ].Material.Diffuse.a = 1.0f;
		}
		else if( strcmp( str, "Ks" ) == 0 )
		{
			//スペキュラ
			fscanf( file, "%f", &materialArray[ mc ].Material.Specular.r );
			fscanf( file, "%f", &materialArray[ mc ].Material.Specular.g );
			fscanf( file, "%f", &materialArray[ mc ].Material.Specular.b );
			materialArray[ mc ].Material.Specular.a = 1.0f;
		}
		else if( strcmp( str, "Ns" ) == 0 )
		{
			//スペキュラ強度
			fscanf( file, "%f", &materialArray[ mc ].Material.Shininess );
		}
		else if( strcmp( str, "d" ) == 0 )
		{
			//アルファ
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.a );
		}
		else if( strcmp( str, "map_Kd" ) == 0 )
		{
			//テクスチャ
			fscanf( file, "%s", str );
			char path[256];
			strcpy( path, dir );
			strcat( path, "\\" );
			strcat( path, str );
			strcat( materialArray[ mc ].TextureName, path );
		}
	}
	*MaterialArray = materialArray;
	*MaterialNum = materialNum;
}
#pragma endregion Loadのヘルパー関数

// 初期化
void Model::Init()
{
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;
	std::string search_name = +"asset\\model\\*.obj";
	hFind = FindFirstFile(search_name.c_str(), &win32fd); // ファイル検索
	// ファイルが見つからなかったとき
	do
	{
		//ディレクトリでない場合は配列に格納する
		if (!(win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			m_FileName.push_back(win32fd.cFileName);
		}
	} while (FindNextFile(hFind, &win32fd));

	//空けたら閉じる
	FindClose(hFind);

	//参照するために前にファイル名を付けていく
	for (unsigned int i = 0; i < m_FileName.size(); i++)
	{
		m_FileName[i] = "asset\\model\\" + m_FileName[i];
	}
}

// 描画
void Model::Draw()
{
	// 頂点バッファの設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	m_dx.GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	// インデックスバッファの設定
	m_dx.GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0); 
	// プリミティブポロジ設定
	m_dx.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	for (unsigned int i = 0; i < m_SubsetNum; i++)
	{
		// マテリアルの設定
		m_dx.SetMaterial(m_SubsetArray[i].Material.Material);
		// テクスチャの設定
		m_dx.GetDeviceContext()->PSSetShaderResources(0, 1, &m_SubsetArray[i].Material.Texture);
		// ポリゴン描画
		m_dx.GetDeviceContext()->DrawIndexed(m_SubsetArray[i].IndexNum, m_SubsetArray[i].StartIndex, 0);
	}
}

// ロード
void Model::Load(const char* FileName)
{
	MODEL model;
	LoadObject(FileName, &model);
	// 頂点バッファ生成
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.ByteWidth = sizeof(VERTEX_3D) * model.VertexNum;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA vsd;
	ZeroMemory(&vsd, sizeof(vsd));
	vsd.pSysMem = model.VertexArray;
	m_dx.GetDevice()->CreateBuffer(&vbd, &vsd, &m_VertexBuffer);
	
	// インデックスバッファ生成
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = sizeof(unsigned int) * model.IndexNum;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA isd;
	ZeroMemory(&isd, sizeof(isd));
	isd.pSysMem = model.IndexArray;
	m_dx.GetDevice()->CreateBuffer(&ibd, &isd, &m_IndexBuffer);
	

	// サブセット設定
	m_SubsetArray = new SUBSET[model.SubsetNum];
	m_SubsetNum = model.SubsetNum;
	for (unsigned int i = 0; i < model.SubsetNum; i++)
	{
		m_SubsetArray[i].StartIndex = model.SubsetArray[i].StartIndex;
		m_SubsetArray[i].IndexNum = model.SubsetArray[i].IndexNum;
		m_SubsetArray[i].Material.Material = model.SubsetArray[i].Material.Material;
		m_SubsetArray[i].Material.Texture = NULL;
		D3DX11CreateShaderResourceViewFromFile(m_dx.GetDevice(), model.SubsetArray[i].Material.TextureName, NULL, NULL, &m_SubsetArray[i].Material.Texture, NULL);
		assert(m_SubsetArray[i].Material.Texture);
	}
	delete[] model.VertexArray;
	delete[] model.IndexArray;
	delete[] model.SubsetArray;
}

// アンロード
void Model::Unload()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	for (unsigned int i = 0; i < m_SubsetNum; i++)
	{
		m_SubsetArray[i].Material.Texture->Release();
	}
	delete[] m_SubsetArray; 
}
