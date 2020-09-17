/*--------------------------------------------------------------
	
	[Scene.h]
	Author : 出合翔太

---------------------------------------------------------------*/
#pragma once
#include <list>
#include <vector>
#include <typeinfo>
#include <string>

#include "BaseGameObject.h"
#include "Model.h"

enum layer :int
{
	LAYER_CAMERA,
	LAYER_3D,
	LAYER_MAX
};

#pragma region Declare_Class_Scene
class Scene
{
protected:
	std::list<GameObject*> m_GameObject[LAYER_MAX];
	virtual void Load() = 0;
	virtual void Unload() = 0;
public:
	Scene() {}
	virtual ~Scene() {}
	virtual void Init() = 0; // 初期化
	// 終了処理
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
	// 更新処理
	virtual void Update()
	{
		for (GameObject* object : m_GameObject[LAYER_3D])
		{
			object->Update();
		}
		for (int i = 0; i < LAYER_MAX; i++)
		{
			// ラムダ式（無名関数）
			m_GameObject[i].remove_if([](GameObject* object)
			{
				return object->Destroy();
			}
			);
		}
	}
	// 描画処理
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

	template <typename T>
	T* AddGameObject(int layer)
	{
		T* gameObject = new T();
		m_GameObject[layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}
	
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

#pragma endregion Sceneクラスの宣言

#pragma region Declare_Class_Game-public_Scene
class Game : public Scene
{
protected:
	void Load()override;
	void Unload()override;
public:	 
	void Init()override;
	void Update()override;
	void Draw()override;
};
#pragma endregion Gameクラスの宣言：Sceneクラスを継承