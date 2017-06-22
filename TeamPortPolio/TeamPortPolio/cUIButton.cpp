#include "stdafx.h"
#include "cUIButton.h"


cUIButton::cUIButton()
{
	SOUND->LoadFile("Button_Clicked", "Sound/Effect/Click_Button.mp3", false);
}


cUIButton::~cUIButton()
{
}

void cUIButton::Setup_Button(string sPath_idle, string sPath_mouseover, string sPath_clicked, int eEventID)
{
	D3DXIMAGE_INFO info;
	m_mapTexture[UI_IDLE] = TEXTURE->GetTexture(sPath_idle, info);
	SetSize(ST_SIZEN(info.Width, info.Height));
	m_mapTexture[UI_MOUSEOVER] = TEXTURE->GetTexture(sPath_mouseover, info);
	m_mapTexture[UI_PRESSED] = TEXTURE->GetTexture(sPath_clicked, info);
	m_mapTexture[UI_CLICKED] = TEXTURE->GetTexture(sPath_clicked, info);
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
			MATH->IsCollided(INPUT->GetMousePosVector2(), LeftTop(), RightBottom()))
		{
			m_eCurrentState = UI_CLICKED;
			SOUND->Play("Button_Clicked");
		}
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

	LPDIRECT3DTEXTURE9 tex = m_mapTexture[m_eCurrentState];
	pSprite->Draw(tex, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));

	pSprite->End();

	cUIObject::Render(pSprite);
}

void cUIButton::Destroy()
{
	cUIObject::Destroy();
}