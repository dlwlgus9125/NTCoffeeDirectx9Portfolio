#pragma once
#define SCENE_CAMERA cSceneCamera::Instance() 

class cSceneCamera : public Singleton<cSceneCamera>
{
private:
	D3DXVECTOR3	 m_vEye;
	D3DXVECTOR3	 m_vLookAt;
	D3DXVECTOR3	 m_vUp;

	bool		m_isLButtonDown;
	D3DXVECTOR3 m_vCamRotAngle;

	SYNTHESIZE(float, m_fPosX, PosX);
	SYNTHESIZE(float, m_fPosY, PosY);
	SYNTHESIZE(float, m_fProjAngle, ProjAngle);
	SYNTHESIZE(float, m_fDistance, Distance);

public:
	void Setup(float posX, float posY, float fProjAngle, float dist);
	void Update();
};

