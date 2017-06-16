#include "stdafx.h"
#include "cUIButton.h"


cUIButton::cUIButton()
{
}


cUIButton::~cUIButton()
{
}

void cUIButton::Setup_Button(string sPath_idle, string sPath_mouseover, string sPath_clicked, int eEventID)
{
	m_mapTexture[UI_IDLE] = TEXTURE->GetTexture(sPath_idle);
	m_mapTexture[UI_MOUSEOVER] = TEXTURE->GetTexture(sPath_mouseover);
	m_mapTexture[UI_PRESSED] = TEXTURE->GetTexture(sPath_clicked);
	m_mapTexture[UI_CLICKED] = TEXTURE->GetTexture(sPath_clicked);
	m_eEventID = eEventID;
	m_eCurrentState = UI_IDLE;
}

void cUIButton::Update(float deltaTime)
{
	if (m_isHidden) return;

	switch (m_eCurrentState)
	{
	case UI_IDLE:
		if (MATH->IsCollided(INPUT->GetMousePosVector2(), LeftTop(), RightBottom())) m_eCurrentState = UI_MOUSEOVER;
		break;
	case UI_MOUSEOVER:
		if (!MATH->IsCollided(INPUT->GetMousePosVector2(), LeftTop(), RightBottom())) m_eCurrentState = UI_IDLE;
		else if (INPUT->IsMousePress(MOUSE_LEFT)) m_eCurrentState = UI_PRESSED;
		break;
	case UI_PRESSED:
		if (!MATH->IsCollided(INPUT->GetMousePosVector2(), LeftTop(), RightBottom())) m_eCurrentState = UI_IDLE;
		else if (INPUT->IsMouseUp(MOUSE_LEFT) && 
			MATH->IsCollided(INPUT->GetMousePosVector2(), LeftTop(), RightBottom())) m_eCurrentState = UI_CLICKED;
		break;
	case UI_CLICKED:
		m_eCurrentState = UI_IDLE;
		break;
	}

	cUIObject::Update(deltaTime);
}

void cUIButton::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	RECT rc;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);

	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	pSprite->Draw(m_mapTexture[m_eCurrentState], &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));

	pSprite->End();

	cUIObject::Render(pSprite);
}

void cUIButton::Destroy()
{
	for each(auto p in m_mapTexture)
	{
		SAFE_RELEASE(p.second);
	}

	delete this;
}