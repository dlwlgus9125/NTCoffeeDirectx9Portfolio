#include "stdafx.h"
#include "cSceneCamera.h"

void cSceneCamera::Setup(float posX, float posY, float fProjAngle, float dist)
{
	m_vEye = D3DXVECTOR3(0, 0, -5);
	m_vLookAt = D3DXVECTOR3(0, 0, 0);
	m_vUp = D3DXVECTOR3(0, 1, 0);
	m_vCamRotAngle = D3DXVECTOR3(0, 0, 0);

	m_fDistance = dist;
	m_fPosX = posX;
	m_fPosY = posY;

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DX_PI / fProjAngle,
		rc.right / (float)rc.bottom,
		1.0f,
		1000.0f);

	matProj._41 += posX;
	matProj._42 += posY;
	D3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cSceneCamera::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);

	matR = matRX * matRY;

	m_vEye = D3DXVECTOR3(0, 0, m_fDistance);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

	m_vEye = m_vEye + m_vLookAt;

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &(m_vLookAt + D3DXVECTOR3(0, 1.0f, 0)), &m_vUp);

	D3DDevice->SetTransform(D3DTS_VIEW, &matView);
}
