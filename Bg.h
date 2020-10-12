/*--------------------------------------------------------------

	[Bg.h]
	背景に関係するクラス
	Author : 出合翔太

---------------------------------------------------------------*/
#pragma once
#include "GameObject.h"
#include "Renderer.h"

// 背景描画用の基底クラス
class BG : public GameObject
{
protected:
	D3DXVECTOR2 m_Scrren;
	SpriteRenderer m_SpriteRenderer;
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	D3DXVECTOR2 GetScrren();
};

// フェード
class Fade : public BG
{
private:
	float m_Alpha = 1.0f;	// a値
public:
	enum FadeState : int
	{
		FADE_NONE,
		FADE_IN,
		FADE_OUT
	};
	FadeState m_FadeState = FADE_NONE;
	static class Scene* m_NextScene;

	Fade() {}
	~Fade() {}
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

namespace DrawBG
{
	// タイトル背景
	class Title : public BG
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
}