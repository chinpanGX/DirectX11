/*-----------------------------------------------------------

	[Wrapper.h]
	DirectX11�֘A�̃��b�p�[
	Author : �o���đ�

------------------------------------------------------------*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h> // �G���[����
#include <iostream>

#pragma warning(push)
#pragma warning(disable:4005)

// DirectX��API
#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>
// �Z�p���C�u����
#include <DirectXMath.h>
// �V�F�[�_�[�̃R���p�C��
#include <d3dcompiler.h>

#pragma warning(pop)

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

// �����^�C���G���[�}�N��
#define STRINGFY(s)  #s
#define TO_STRING(x) STRINGFY(x)
#define FILE_PREFIX __FILE__ "(" TO_STRING(__LINE__) "): " 
#define ThrowIfFailed(hr, msg) Utility::CheckResultCode( hr, FILE_PREFIX msg)


namespace Utility
{
	class Exception : public std::runtime_error
	{
	public:
		Exception(const std::string& msg) : std::runtime_error(msg.c_str()) {}
	};

	inline void CheckResultCode(HRESULT hr, const std::string& errorMsg)
	{
		if (FAILED(hr))
		{
			throw Exception(errorMsg);
		}
	}
}

namespace DirectX11Wrapper
{
	// ���_�\����
	struct VERTEX_3D
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR3 Normal;
		D3DXVECTOR4 Diffuse;
		D3DXVECTOR2 TexCoord;
	};

	// �}�e���A���\����
	struct MATERIAL
	{
		D3DXCOLOR	Ambient;
		D3DXCOLOR	Diffuse;
		D3DXCOLOR	Specular;
		D3DXCOLOR	Emission;
		float		Shininess;
		float		Dummy[3];//16byte���E�p
	};

	// �}�e���A���\����
	struct DX11_MODEL_MATERIAL
	{
		MATERIAL		Material;
		class CTexture*	Texture;
	};

	// �`��T�u�Z�b�g�\����
	struct DX11_SUBSET
	{
		unsigned int	StartIndex;
		unsigned int	IndexNum;
		DX11_MODEL_MATERIAL	Material;
	};

	// ���C�g�\����
	struct LIGHT
	{
		BOOL		Enable;
		BOOL		Dummy[3];//16byte���E�p
		D3DXVECTOR4	Direction;
		D3DXCOLOR	Diffuse;
		D3DXCOLOR	Ambient;
	};

	// DirectX11�̃��b�p�[
	class DirectX11
	{
	private:
		ID3D11Device*				m_Device = NULL;
		ID3D11DeviceContext*		m_ImmediateContext = NULL;
		IDXGISwapChain*				m_SwapChain = NULL;
		ID3D11RenderTargetView*		m_RenderTargetView = NULL;
		ID3D11DepthStencilView*		m_DepthStencilView = NULL;
		ID3D11VertexShader*			m_VertexShader = NULL;
		ID3D11PixelShader*			m_PixelShader = NULL;
		ID3D11InputLayout*			m_VertexLayout = NULL;
		ID3D11Buffer*				m_WorldBuffer = NULL;
		ID3D11Buffer*				m_ViewBuffer = NULL;
		ID3D11Buffer*				m_ProjectionBuffer = NULL;
		ID3D11Buffer*				m_MaterialBuffer = NULL;
		ID3D11Buffer*				m_LightBuffer = NULL;
		ID3D11DepthStencilState*	m_DepthStateEnable = NULL;
		ID3D11DepthStencilState*	m_DepthStateDisable = NULL;

		DirectX11() {}
		// �R�s�[�Ƒ�����֎~
		void operator= (const DirectX11&) = delete;
	public:
		static DirectX11& Instance();
		void Init();
		void Uninit();
		void Begin();
		void End();
		void SetDepthEnable(bool Enable);
		void SetWorldViewProjection2D();
		void SetWorldMatrix(D3DXMATRIX * WorldMatrix);
		void SetViewMatrix(D3DXMATRIX * ViewMatrix);
		void SetProjectionMatrix(D3DXMATRIX * ProjectionMatrix);
		void SetMaterial(MATERIAL Material);
		void SetLight(LIGHT Light);

		ID3D11Device* GetDevice() { return m_Device; }
		ID3D11DeviceContext* GetDeviceContext() { return m_ImmediateContext; }
	};
}