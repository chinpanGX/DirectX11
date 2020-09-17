/*--------------------------------------------------------------

	[Player.h]
	Author : 出合翔太

---------------------------------------------------------------*/
#pragma once
#include "BaseGameObject.h"

class Player : public GameObject
{
private:
	class Model* m_Model; // 前方宣言
	D3DXQUATERNION m_Quaternion; // クォータニオン
public:
	Player() {}
	~Player() {}
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

