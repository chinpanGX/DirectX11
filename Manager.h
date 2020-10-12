/*----------------------------------------------------------

	[Manager.h]
	�Q�[���A�v���P�[�V����
	Author : �o���đ�

-----------------------------------------------------------*/
#pragma once
#include<memory>
#include<vector>
#include<map>
#include "DirectX11Wrapper.h"

class Manager
{
private:
	static class Scene* m_Scene;
	static class Fade m_Fade;
	static class DirectX11Wrapper::DirectX11& m_dx;
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static class Scene* GetScene() { return m_Scene; }
	static void ChangeScene(Scene* scene);	// ��ʑJ��
	// �V�[���̃Z�b�g
	template <typename T>
	static void SetScene()
	{
		if (m_Fade.m_FadeState != Fade::FADE_NONE)
		{
			return;
		}
		m_Fade.m_FadeState = Fade::FADE_OUT;
		T* scene = new T;
		m_Fade.m_NextScene = scene;
	}
};

