#include "stdafx.h"
#include "cUIProgressBar.h"


cUIProgressBar::cUIProgressBar()
	: m_pTexture(NULL)
{
}


cUIProgressBar::~cUIProgressBar()
{
}

void cUIProgressBar::Update(float deltaTime)
{
	cUIObject::Update(deltaTime);
}

void cUIProgressBar::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	D3DXMATRIXA16 matS, matWorld;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixScaling(&matS, 0.99f, 0.9f, 1.0f);
	matWorld = matS * m_matWorld;
	pSprite->SetTransform(&matWorld);

	pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	pSprite->End();
	
	cUIObject::Render(pSprite);
}

void cUIProgressBar::Destroy() 
{
	cUIObject::Destroy();
}