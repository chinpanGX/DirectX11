/*--------------------------------------------------------------

	[Player.h]
	Author : �o���đ�

---------------------------------------------------------------*/
#pragma once
#include "BaseGameObject.h"

class Player : public GameObject
{
private:
	class Model* m_Model; // �O���錾
	D3DXQUATERNION m_Quaternion; // �N�H�[�^�j�I��
public:
	Player() {}
	~Player() {}
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

