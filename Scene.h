/*--------------------------------------------------------------
	
	[Scene.h]
	�V�[���֘A�̏������Ǘ�
	Author : �o���đ�

---------------------------------------------------------------*/
#pragma once
#include <list>
#include <vector>
#include <typeinfo>
#include <string>
#include "GameObject.h"

// ���C���[�̗�
enum layer : int
{
	LAYER_CAMERA,
	LAYER_2D,
	LAYER_3D,
	LAYER_MAX
};

#pragma region Class_Scene
class Scene
{
protected:
	std::list<GameObject*> m_GameObject[LAYER_MAX];
	virtual void Load() = 0;	// ���[�h
	virtual void Unload() = 0;	// �A�����[�h
public:
	Scene() {}
	virtual ~Scene() {}
	virtual void Init() = 0; // ������
	// �I������
	virtual void Uninit()
	{
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();
		}
		Unload();
	}
	// �X�V����
	virtual void Update()
	{
		for (GameObject* object : m_GameObject[LAYER_CAMERA])
		{
			object->Update();
		}
		for (GameObject* object : m_GameObject[LAYER_3D])
		{
			object->Update();
		}
		for (int i = 0; i < LAYER_MAX; i++)
		{
			// �����_���i�����֐��j
			m_GameObject[i].remove_if([](GameObject* object)
				{
					return object->Destroy();
				}
			);
		}
	}
	// �`�揈��
	virtual void Draw()
	{
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}
	
	// �ǉ�
	template <typename T>
	T* AddGameObject(int layer)
	{
		T* gameObject = new T();
		m_GameObject[layer].push_back(gameObject);
		gameObject->Init();
		return gameObject;
	}

	// �Q�b�^�[
	template<typename T>
	T* GetGameObject(int layer)
	{
		for (GameObject* object : m_GameObject[layer])
		{
			if (typeid(*object) == typeid(T))
				return (T*)object;
		}
		return NULL;
	}
	template<typename T>
	std::vector<T*>GetGameObjects(int layer)
	{
		std::vector<T*>objects;
		for (GameObject* object : m_GameObject[layer])
		{
			if (typeid(*object) == typeid(T))
				objects.push_back((T*)object);
		}
		return objects;
	}
};
#pragma endregion Scene�N���X�̐錾

#pragma region class_Game-public_Scene
class Game : public Scene
{
private:
	void Load()override;
	void Unload()override;
public:	 
	void Init()override;
	void Update()override;
	void Draw()override;
};
#pragma endregion Game�N���X�̐錾�FScene�N���X���p��

#pragma region class_Title-public_Scene
class Title : public Scene
{
private:
	void Load()override;
	void Unload()override;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
#pragma endregion Title�N���X�̐錾:Scene�N���X���p�� 
