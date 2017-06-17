#include "stdafx.h"
#include "cUIMsgBox.h"


cUIMsgBox::cUIMsgBox()
{
}


cUIMsgBox::~cUIMsgBox()
{
}

void cUIMsgBox::Update(float deltaTime)
{
	cUIObject::Update(deltaTime);
}

void cUIMsgBox::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	RECT rc;

	// >> 배경 그리는 부분
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
	// << 

	// >> 글씨 쓰는 부분
	LPD3DXFONT pFont = FONT->GetFont(m_eFont);

	SetRect(&rc, m_vMsgPos.x, m_vMsgPos.y, m_vMsgPos.x + m_stMsgBorder.nWidth, m_vMsgPos.y + m_stMsgBorder.nHeight);
	pFont->DrawText(NULL, m_sText.c_str(), m_sText.length(), &rc, DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(0, 0, 0));
	// <<


	cUIObject::Render(pSprite);
}

void cUIMsgBox::Destroy()
{
	cUIObject::Destroy();
}

void cUIMsgBox::Setup_MsgBox(string imagePath, D3DXVECTOR3 msgPos, ST_SIZEN msgBorder, int eEventID, FONT_TAG eFont)
{
	D3DXIMAGE_INFO info;

	m_pTexture = TEXTURE->GetTexture(imagePath, info);
	SetSize(ST_SIZEN(info.Width, info.Height));

	m_vMsgPos = msgPos + m_vPosition;

	m_stMsgBorder = msgBorder;
	m_eEventID = eEventID;
	m_eFont = eFont;
}
void cUIMsgBox::Setup_Text(string text)
{
	m_sText = text;
}
