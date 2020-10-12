/*--------------------------------------------------------------

	[Bg.h]
	�w�i�Ɋ֌W����N���X
	Author : �o���đ�

---------------------------------------------------------------*/
#pragma once
#include "GameObject.h"
#include "Renderer.h"

// �w�i�`��p�̊��N���X
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

// �t�F�[�h
class Fade : public BG
{
private:
	float m_Alpha = 1.0f;	// a�l
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
	// �^�C�g���w�i
	class Title : public BG
	{
	public:
		void Init()override;
		void Uninit()override;
		void Update()override;
		void Draw()override;
	};
}