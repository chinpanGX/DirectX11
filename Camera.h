/*--------------------------------------------------------------

	[Camera.h]
	Author : o‡ãÄ‘¾

---------------------------------------------------------------*/
#pragma once
#include "BaseGameObject.h"

#pragma region Declare_Class_Camera
class Camera : public GameObject
{
private:
	D3DXVECTOR3 m_Target;
	D3DXMATRIX m_ViewMatrix;
	D3DXMATRIX m_ProjectionMatrix;
public:
	Camera() {}
	~Camera() {}
	void Init()override;
	void Uninit()override {};
	void Update()override;
	void Draw()override;
	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }
};
#pragma endregion CameraƒNƒ‰ƒXéŒ¾
