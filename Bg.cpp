/*--------------------------------------------------------------
	
	[Bg.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Bg.h"
#include "Manager.h"
#include "Application.h"

#pragma region FuncName_of_classBG_is_GetScrren
// 基底クラスBG
// スクリーンのゲッター
D3DXVECTOR2 BG::GetScrren()
{
	auto &app = Application::Instance();
	m_Scrren.x = (float)app.GetWindowSize().cx;
	m_Scrren.y = (float)app.GetWindowSize().cy;
	return m_Scrren;
}
#pragma endregion BGクラスの関数GetScrren()

// フェードの処理
#pragma region FuncName_of_classFade
Scene* Fade::m_NextScene = NULL; // スタティック変数

void Fade::Init()
{
	m_SpriteRenderer.Load("asset/Texture/black.png");
}

void Fade::Uninit()
{
	m_SpriteRenderer.Unload();
}

void Fade::Update()
{
	switch (m_FadeState)
	{
	case FADE_OUT:
		m_Alpha += 0.025f;
		if (m_Alpha > 1.0f)
		{
			Manager::ChangeScene(m_NextScene);
			m_FadeState = FADE_IN;
		}
		break;
	case FADE_IN:
		m_Alpha -= 0.025f;
		if (m_Alpha < 0.0f)
		{
			m_FadeState = FADE_NONE;
		}
		break;
	}
}

void Fade::Draw()
{
	m_SpriteRenderer.Draw(BG::GetScrren() * 0.5f, BG::GetScrren(), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Alpha));
}
#pragma endregion Fadeの関数定義

// タイトルの処理
#pragma region Define_TitleBG_Func
void DrawBG::Title::Init()
{
	m_SpriteRenderer.Load("asset/texture/title01.png");
}

void DrawBG::Title::Uninit()
{
	m_SpriteRenderer.Unload();
}

void DrawBG::Title::Update()
{

}

void DrawBG::Title::Draw()
{
	m_SpriteRenderer.Draw(BG::GetScrren() * 0.5f, BG::GetScrren(), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
}
#pragma endregion Titleの関数定義
