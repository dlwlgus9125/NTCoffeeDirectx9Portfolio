#pragma once

#define CAMERA cCamera::Instance() 

class cCamera : public Singleton<cCamera>
{
private:
	D3DXVECTOR3	 m_vEye;
	D3DXVECTOR3	 m_vLookAt;
	D3DXVECTOR3	 m_vUp;
	//D3DXVECTOR3	* m_pvTarget;
	
	POINT		m_ptPrevMouse;
	bool		m_isLButtonDown;
	float		m_fCameraDistance;
	D3DXVECTOR3 m_vCamRotAngle;

public:
	void Setup();
	void Update();
	void Destroy();
	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void MoveCamera();
	void SetLookAt(D3DXVECTOR3 lookAt, float rotY) { m_vLookAt = lookAt; }//m_vCamRotAngle.y = rotY;
	void SetCameraDistance(float x) { m_fCameraDistance=x; }
	float GetCameraDitance() {		return m_fCameraDistance;	}
	// >> : SkyBox에서 끌어쓰기 위해 추가
	D3DXVECTOR3& GetEye() { return m_vEye; }
	D3DXVECTOR3 GetCamRotAngle() { return m_vCamRotAngle; }
	D3DXVECTOR3& GetLookAt() { return m_vLookAt; }
	D3DXVECTOR3& GetUp() { return m_vUp; }
	cCamera* GetCamera() { return this; }
	// << :
	void SetCaneraRotateAngle(float angle) { m_vCamRotAngle.y = angle; }
	void SetCameraRotateAngle(D3DXVECTOR3 angle)
	{ 
		m_vCamRotAngle.x = angle.x;
		m_vCamRotAngle.z = angle.z;
	}
	void SetEye(D3DXVECTOR3 vEye) {m_vEye = vEye;}
};

