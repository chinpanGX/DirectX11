/*------------------------------------------------------------

	[Model.cpp]
	Author : 出合翔太

--------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include "Renderer.h"
#include "Model.h"

std::vector<std::string> Model::m_FileName{};

#pragma region Load_HelperFunc
// モデルの読み込み
void Model::LaodObject(const char * FileName, MODEL * Model)
{
	char dir[MAX_PATH];
	strcpy(dir, FileName);
	PathRemoveFileSpec(dir); // パスからファイル名を取り除く

	D3DXVECTOR3* pPositonArray;
	D3DXVECTOR3* pNomalArray;
	D3DXVECTOR2* pTexcooadArray;

	unsigned int positionNum = 0;
	unsigned int nomalNum = 0;
	unsigned int texCooadNum = 0;
	unsigned int vertaxNum = 0;
	unsigned int indexNum = 0;
	unsigned int in = 0;
	unsigned int subsetNum = 0;

	MODEL_MATERIAL* pMaterialArray = NULL;
	unsigned int materialNum = 0;

	char str[256];
	char* s;
	char c;

	// ファイルオープン
	FILE* File;
	File = fopen(FileName, "rt");
	assert(File); // エラーチェック

	// 要素数をカウント
	while (true)
	{
		fscanf(File, "%s", str);
		// ファイルの終端指示子(ファイルの終わりに到達)が設定されればループを抜ける
		if (feof(File) != 0) 
		{
			break;
		}
		// 文字列を比較し、一致すればif文の中に入る
		if (strcmp(str, "v") == 0)
		{
			positionNum++; 
		}
		else if (strcmp(str,"vn") == 0)
		{
			nomalNum++;
		}
		else if (strcmp(str, "vt") == 0) 
		{
			texCooadNum++;
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
				fscanf(File, "%s", str);
				vertaxNum++;
				in++;
				c = fgetc(File);
			} while (c != '\n' && c != '\r');

			// 四角は三角に分割
			if (in == 4)
			{
				in = 6;
			}
			indexNum += in;
		}
	}

	// メモリを確保
	pPositonArray = new D3DXVECTOR3[positionNum];
	pNomalArray = new D3DXVECTOR3[nomalNum];
	pTexcooadArray = new D3DXVECTOR2[texCooadNum];

	Model->VertexArray = new VERTEX_3D[vertaxNum];
	Model->VertexNum = vertaxNum;

	Model->IndexArray = new unsigned int[indexNum];
	Model->IndexNum = indexNum;

	Model->SubsetArray = new SUBSET[subsetNum];
	Model->SubsetNum = subsetNum;

	// 要素読み込み
	D3DXVECTOR3* position = pPositonArray;
	D3DXVECTOR3* normal = pNomalArray;
	D3DXVECTOR2* texcoord = pTexcooadArray;
	unsigned int vc = 0;
	unsigned int ic = 0;
	unsigned int sc = 0;
	fseek(File, 0, SEEK_SET); // ファイルポインタを移動させる。基準はファイルの先頭。

	while (true)
	{
		fscanf(File, "%s", str);
		// ファイルの終端指示子(ファイルの終わりに到達)が設定されればループを抜ける
		if (feof(File) != 0)
		{
			break;
		}
		if (strcmp(str, "mtllib") == 0)
		{
			// マテリアルファイル
			fscanf(File, "%s", str);
			char path[256];
			strcpy(path, dir);
			strcpy(path, "\\");
			strcpy(path, str);
			LaodMaterial(path, &pMaterialArray, &materialNum); // マテリアルの読み込み
		}
		else if (strcmp(str, "o") == 0)
		{
			fscanf(File, "%s", str); // オブジェクト名
		}
		else if (strcmp(str, "v") == 0)
		{
			// 頂点座標
			fscanf(File, "%f", &position->x);
			fscanf(File, "%f", &position->y);
			fscanf(File, "%f", &position->z);
			position++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			// 法線
			fscanf(File, "%f", &normal->x);
			fscanf(File, "%f", &normal->y);
			fscanf(File, "%f", &normal->z);
			normal++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			// テクスチャ座標
			fscanf(File, "%f", &texcoord->x);
			fscanf(File, "%f", &texcoord->y);
			texcoord++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			// マテリアル
			fscanf(File, "%s", str);
			if (sc != 0)
			{
				Model->SubsetArray[sc - 1].IndexNum = ic - Model->SubsetArray[sc - 1].StartIndex;
			}
			Model->SubsetArray[sc].StartIndex = ic;
			for (unsigned int i = 0; i < materialNum; i++)
			{
				if (strcmp(str, pMaterialArray[i].Name) == 0)
				{
					Model->SubsetArray[sc].Material.Material = pMaterialArray[i].Material;
					strcpy(Model->SubsetArray[sc].Material.TextureName, pMaterialArray[i].TextureName);
					strcpy(Model->SubsetArray[sc].Material.Name, pMaterialArray[i].Name);
					break;
				}
			}
			sc++;
		}
		else if (strcmp(str, "f") == 0)
		{
			// 面
			in = 0;
			do
			{
				fscanf(File, "%s", str);
				s = strtok(str, "/");
				Model->VertexArray[vc].Position = pPositonArray[atoi(s) - 1];
				if (s[strlen(s) + 1] != '/')
				{
					// テクスチャ座標が存在しない場合もある
					s = strtok(NULL, "/");
					Model->VertexArray[vc].TexCoord = pTexcooadArray[atoi(s) - 1];
				}
				s = strtok(NULL, "/");
				Model->VertexArray[vc].Normal = pNomalArray[atoi(s) - 1];
				Model->VertexArray[vc].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				Model->IndexArray[ic] = vc;
				ic++;
				vc++;
				in++;
				c = fgetc(File);
			} while (c != '\n' && c != '\r');

			// 四角は三角に分割
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
	delete[] pPositonArray;
	delete[] pNomalArray;
	delete[] pTexcooadArray;
	delete[] pMaterialArray;
}

// マテリアル読み込み
void Model::LaodMaterial(const char * FileName, MODEL_MATERIAL ** MaterialArray, unsigned int * MaterialNum)
{
	char dir[MAX_PATH];
	strcpy(dir, FileName);
	PathRemoveFileSpec(dir); // パスからファイル名を取り除く

	char str[256];
	FILE* File;
	File = fopen(FileName, "rt");
	assert(File); // エラーチェック

	MODEL_MATERIAL* pMaterialArray;
	unsigned int materialNum = 0;

	// 要素数のカウント
	while (true)
	{
		fscanf(File, "%s", str);
		// ファイルの終端指示子(ファイルの終わりに到達)が設定されればループを抜ける
		if (feof(File) != 0) 
		{
			break;
		}
		// 文字列の比較して一致するかどうか
		if (strcmp(str, "newmtl") == 0)
		{
			materialNum++;
		}
	}

	// メモリの確保
	pMaterialArray = new MODEL_MATERIAL[materialNum];

	// 要素読み込み
	int mc = -1;
	fseek(File, 0, SEEK_SET); // ファイルポインタを移動させる。基準はファイルの先頭。
	while (true)
	{
		fscanf(File, "%s", str);
		// ファイルの終端指示子(ファイルの終わりに到達)が設定されればループを抜ける
		if (feof(File) != 0)
		{
			break;
		}
		// 文字列の比較して一致するかどうか
		if (strcmp(str,"newmtl") == 0)
		{
			// マテリアル名
			mc++;
			fscanf(File, "%s", pMaterialArray[mc].Name);
			strcpy(pMaterialArray[mc].TextureName, "");

			pMaterialArray[mc].Material.Emission.r = 0.0f;
			pMaterialArray[mc].Material.Emission.g = 0.0f;
			pMaterialArray[mc].Material.Emission.b = 0.0f;
			pMaterialArray[mc].Material.Emission.a = 0.0f;
		}
		else if (strcmp(str, "ka") == 0)
		{
			// アンビエント
			fscanf(File, "%s", &pMaterialArray[mc].Material.Ambient.r);
			fscanf(File, "%s", &pMaterialArray[mc].Material.Ambient.g);
			fscanf(File, "%s", &pMaterialArray[mc].Material.Ambient.b);
			pMaterialArray[mc].Material.Ambient.a = 1.0f;
		}
		else if (strcmp(str, "Kd") == 0)
		{
			//ディフューズ
			fscanf(File, "%f", &pMaterialArray[mc].Material.Diffuse.r);
			fscanf(File, "%f", &pMaterialArray[mc].Material.Diffuse.g);
			fscanf(File, "%f", &pMaterialArray[mc].Material.Diffuse.b);
			pMaterialArray[mc].Material.Diffuse.a = 1.0f;
		}
		else if (strcmp(str, "Ks") == 0)
		{
			//スペキュラ
			fscanf(File, "%f", &pMaterialArray[mc].Material.Specular.r);
			fscanf(File, "%f", &pMaterialArray[mc].Material.Specular.g);
			fscanf(File, "%f", &pMaterialArray[mc].Material.Specular.b);
			pMaterialArray[mc].Material.Specular.a = 1.0f;
		}
		else if (strcmp(str, "Ns") == 0)
		{
			//スペキュラ強度
			fscanf(File, "%f", &pMaterialArray[mc].Material.Shininess);
		}
		else if (strcmp(str, "d") == 0)
		{
			//アルファ
			fscanf(File, "%f", &pMaterialArray[mc].Material.Diffuse.a);
		}
		else if (strcmp(str, "map_Kd") == 0)
		{
			//テクスチャ
			fscanf(File, "%s", str);

			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);

			strcat(pMaterialArray[mc].TextureName, path);
		}
	}
	*MaterialArray = pMaterialArray;
	*MaterialNum = materialNum;

	delete[] pMaterialArray;
}

#pragma endregion Loadのヘルパー関数

// 初期化
void Model::Init()
{
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;
	std::string search_name = + "Rom\\Model\\*.obj";
	hFind = FindFirstFile(search_name.c_str(), &win32fd); // ファイル検索
	// ファイルが見つからなかったとき
	if (hFind = INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("file not found"); // ランタイムエラー
	}
	do
	{
		// ディレクトリでない場合は配列に格納する
		if (!(win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			m_FileName.push_back(win32fd.cFileName);
		}
	} while (FindNextFile(hFind, &win32fd));
	FindClose(hFind); // 開けたら閉じる
	// 参照するために前にファイル名を付けていく
	for (unsigned int i = 0; i < m_FileName.size(); i++)
	{
		m_FileName[i] = "Rom\\Model\\" + m_FileName[i];
	}
}

// 描画
void Model::Draw()
{
	// 頂点バッファの設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IAGetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	// インデックスバッファの設定
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0); 
	// プリミティブポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	for (unsigned int i = 0; i < m_SubsetNum; i++)
	{
		// マテリアルの設定
		Renderer::SetMaterial(m_SubsetArray[i].Material.Material);
		// テクスチャの設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_SubsetArray[i].Material.Texture);
		// ポリゴン描画
		Renderer::GetDeviceContext()->DrawIndexed(m_SubsetArray[i].IndexNum, m_SubsetArray[i].StartIndex, 0);
	}
}

// ロード
void Model::Load(const char* FileName)
{
	MODEL model;
	LaodObject(FileName, &model);

	//頂点バッファ生成
	D3D11_BUFFER_DESC vtxbd;
	ZeroMemory(&vtxbd, sizeof(vtxbd));
	vtxbd.Usage = D3D11_USAGE_DEFAULT;
	vtxbd.ByteWidth = sizeof(VERTEX_3D) * model.VertexNum;
	vtxbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vtxbd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA vtxsd;
	ZeroMemory(&vtxsd, sizeof(vtxsd));
	vtxsd.pSysMem = model.VertexArray;
	Renderer::GetDevice()->CreateBuffer(&vtxbd, &vtxsd, &m_VertexBuffer);
		
	// インデックスバッファ生成
	D3D11_BUFFER_DESC idxbd;
	ZeroMemory(&idxbd, sizeof(idxbd));
	idxbd.Usage = D3D11_USAGE_DEFAULT;
	idxbd.ByteWidth = sizeof(unsigned int) * model.IndexNum;
	idxbd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	idxbd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA idxsd;
	ZeroMemory(&idxsd, sizeof(idxsd));
	idxsd.pSysMem = model.IndexArray;
	Renderer::GetDevice()->CreateBuffer(&idxbd, &idxsd, &m_IndexBuffer);
		
	// サブセット設定
	m_SubsetArray = new SUBSET[model.SubsetNum];
	m_SubsetNum = model.SubsetNum;
	for (unsigned int i = 0; i < model.SubsetNum; i++)
	{
		m_SubsetArray[i].StartIndex = model.SubsetArray[i].StartIndex;
		m_SubsetArray[i].IndexNum = model.SubsetArray[i].IndexNum;
		m_SubsetArray[i].Material.Material = model.SubsetArray[i].Material.Material;
		m_SubsetArray[i].Material.Texture = NULL;
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(), model.SubsetArray[i].Material.TextureName, NULL, NULL, &m_SubsetArray[i].Material.Texture, NULL);
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
