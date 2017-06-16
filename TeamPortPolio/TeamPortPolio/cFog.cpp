#include "stdafx.h"
#include "cFog.h"
#include "cCamera.h"


cFog::cFog()
	: m_pFogEffect(NULL)
	, m_pErrorBuffer(NULL)
	, m_fogTechHandle(NULL)
{
}

cFog::~cFog()
{
}

void cFog::Setup(char* sFullPath)
{
	D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	D3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	D3DXCreateEffectFromFile(D3DDevice, sFullPath, 0, 0, D3DXSHADER_DEBUG, 0, &m_pFogEffect, &m_pErrorBuffer);

	m_fogTechHandle = m_pFogEffect->GetTechniqueByName("Fog");
}

void cFog::Update(cCamera* pCamera)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI * 0.25f, (float)rc.right / (float)rc.bottom, 1.0f, 1000.0f);

	D3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &pCamera->GetEye(), &pCamera->GetLookAt(), &pCamera->GetUp());

	D3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cFog::Destroy()
{
	if (m_pFogEffect)
	{
		m_pFogEffect->Release();
		m_pFogEffect = NULL;
	}

	delete this;
}

void cFog::Render_Begin(int passIndex)
{
	m_pFogEffect->SetTechnique(m_fogTechHandle);
	m_pFogEffect->Begin(NULL, 0);
	m_pFogEffect->BeginPass(passIndex);
}

void cFog::Render_End()
{
	m_pFogEffect->EndPass();
	m_pFogEffect->End();
}