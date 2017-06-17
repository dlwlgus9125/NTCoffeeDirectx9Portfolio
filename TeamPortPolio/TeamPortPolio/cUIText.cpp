#include "stdafx.h"
#include "cUIText.h"


cUIText::cUIText()
{
}


cUIText::~cUIText()
{

}

void cUIText::Update(float deltaTime)
{
	cUIObject::Update(deltaTime);
}

void cUIText::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	RECT rc;

	LPD3DXFONT pFont = FONT->GetFont(m_eFont);

	SetRect(&rc, LeftTop().x, LeftTop().y, RightBottom().x, RightBottom().y);
	pFont->DrawText(NULL, m_sText.c_str(), m_sText.length(), &rc, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));

	cUIObject::Render(pSprite);
}

void cUIText::Destroy()
{
	cUIObject::Destroy();
}


void cUIText::Setup_Text(string text, int width, int height, FONT_TAG tag)
{
	m_sText = text;
	m_eFont = tag;
	m_stSize = ST_SIZEN(width, height);
}
