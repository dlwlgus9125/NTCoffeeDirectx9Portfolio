#include "stdafx.h"
#include "cCamera.h"



void cCamera::Setup()
{
	m_vEye = D3DXVECTOR3(0, 0, -5);
	m_vLookAt = D3DXVECTOR3(0, 0, 0);
	m_vUp = D3DXVECTOR3(0, 1, 0);
	//m_pvTarget = NULL;
	m_fCameraDistance = 5.0f;
	m_isLButtonDown = false;
	m_vCamRotAngle = D3DXVECTOR3(0, 0, 0);

	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;

	//m_pvTarget = pvTarget;

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DX_PI / 4.0F,
		rc.right / (float)rc.bottom,
		1.0f,
		1000.0f);

	D3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Update()
{
	//MoveCamera();
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);

	matR = matRX * matRY;

	m_fCameraDistance = MATH->Clamp(m_fCameraDistance, 1.0f, m_fCameraDistance);

	m_vEye = D3DXVECTOR3(0, 0, -m_fCameraDistance);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

	//cout << m_vCamRotAngle.x << " " << m_vCamRotAngle.y << " " << m_vCamRotAngle.z << endl;
	//m_vEye = m_vEye + m_vLookAt;

	
		//m_vLookAt = m_LookAtPos;
	//m_vLookAt += D3DXVECTOR3(0, 1.0f, 0);
	m_vEye = m_vEye + m_vLookAt;

		//m_vLookAt.y += 1.0f;
		//m_vEye.y += 1.0f;

	//if (INPUT->IsKeyPress(VK_0)) m_fCameraDistance++;
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &(m_vLookAt + D3DXVECTOR3(0, 1.0f, 0)), &m_vUp);

	D3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::Destroy()
{
}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_LBUTTONDOWN:
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		m_isLButtonDown = true;
		break;


	case WM_LBUTTONUP:
		m_isLButtonDown = false;
		break;


	case WM_MOUSEMOVE:
		if (m_isLButtonDown)
		{
			POINT ptCurrMouse;
			ptCurrMouse.x = LOWORD(lParam);
			ptCurrMouse.y = HIWORD(lParam);
			float fDeltaX = (float)ptCurrMouse.x - m_ptPrevMouse.x;
			float fDeltaY = (float)ptCurrMouse.y - m_ptPrevMouse.y;
			m_vCamRotAngle.y += (fDeltaX / 100.f);
			m_vCamRotAngle.x += (fDeltaY / 100.f);
			if (m_vCamRotAngle.x < -D3DX_PI / 2.0f + 0.0001f)
				m_vCamRotAngle.x = -D3DX_PI / 2.0f + 0.0001f;
			if (m_vCamRotAngle.x > D3DX_PI / 2.0f - 0.0001f)
				m_vCamRotAngle.x = D3DX_PI / 2.0f - 0.0001f;
			m_ptPrevMouse = ptCurrMouse;
		}	 break;

	case WM_MOUSEWHEEL:
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 500.f);
		if (m_fCameraDistance < 0.0001f)
			m_fCameraDistance = 0.0001f;
		break;
	}
}

void cCamera::MoveCamera()
{
	D3DXVECTOR3 dir = m_vLookAt - m_vEye;

	D3DXVec3Normalize(&dir, &dir);


	if (GetKeyState('W') & 0x8000)	m_vLookAt = m_vLookAt + (dir * 0.1f);
	if (GetKeyState('S') & 0x8000)	m_vLookAt = m_vLookAt - (dir * 0.1f);

}
