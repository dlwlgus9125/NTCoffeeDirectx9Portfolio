#include "stdafx.h"
#include "cUIProgressBar.h"


cUIProgressBar::cUIProgressBar()
	: m_pTexture_OutLine(NULL), m_pTexture_FillLine(NULL)
	, m_fScaleX(0.0f), m_isFinished(false)
{
}


cUIProgressBar::~cUIProgressBar()
{
}

void cUIProgressBar::Setup_Progress(char* cOutLine_Path, char* cFillLine_Path, D3DXVECTOR3 fillLine_Pos)
{
	D3DXIMAGE_INFO	pImageInfo;
	m_pTexture_OutLine = TEXTURE->GetTexture(cOutLine_Path, pImageInfo);
	m_stSize_OutLine = ST_SIZEN(pImageInfo.Width, pImageInfo.Height);

	m_pTexture_FillLine = TEXTURE->GetTexture(cFillLine_Path, pImageInfo);
	m_stSize_FillLine = ST_SIZEN(pImageInfo.Width, pImageInfo.Height);

	m_vPos_FillLine = fillLine_Pos;
}

void cUIProgressBar::Update(float deltaTime)
{
	m_fScaleX += 0.05f;
	if (m_fScaleX > 14.5f)
	{
		m_fScaleX = 14.5f;
		m_isFinished = true;
	}

	cUIObject::Update(deltaTime);
}

void cUIProgressBar::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	RECT rc;

	// FillLine
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	SetRect(&rc, 0, 0, m_stSize_FillLine.nWidth, m_stSize_FillLine.nHeight);

	D3DXMATRIXA16 matS, matT, matWorld;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, m_fScaleX, 0.5f, 1.0f);
	D3DXMatrixTranslation(&matT, m_vPos_FillLine.x, m_vPos_FillLine.y, m_vPos_FillLine.z);
	matWorld = matS * matT * m_matWorld;
	pSprite->SetTransform(&matWorld);

	pSprite->Draw(m_pTexture_FillLine, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	pSprite->End();

	cUIObject::Render(pSprite);

	// OutLine
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	SetRect(&rc, 0, 0, m_stSize_OutLine.nWidth, m_stSize_OutLine.nHeight);

	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, 2.0f, 1.0f, 1.0f);
	matWorld = matS * m_matWorld;
	pSprite->SetTransform(&matWorld);

	pSprite->Draw(m_pTexture_OutLine, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	pSprite->End();
}

void cUIProgressBar::Destroy() 
{
	cUIObject::Destroy();
}