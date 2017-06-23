#include "stdafx.h"
#include "cUIProgressBar.h"


cUIProgressBar::cUIProgressBar()
	: m_pTexture_OutLine(NULL), m_pTexture_FillLine(NULL)
	, m_fScaleX(0.0f), m_isFinished(false), m_fScaleX_Outline(2.0f)
{
	m_vecTexture_AddedFillLine = {};
	m_vecSize_AddedFillLine = {};
	m_vecPos_AddedFillLine = {};
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

	// >> FillLine
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
	// <<

	// >> Added FillLine
	for (int i = 0; i < m_vecTexture_AddedFillLine.size(); i++)
	{		
		SetRect(&rc, 0, 0, m_vecSize_AddedFillLine[i].nWidth, m_vecSize_AddedFillLine[i].nHeight);

		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matS, m_vecScaleFillLine[i], 1.0f, 1.0f);
		D3DXMatrixTranslation(&matT, m_vecPos_AddedFillLine[i].x, m_vecPos_AddedFillLine[i].y, m_vecPos_AddedFillLine[i].z);
		matWorld = matS * matT * m_matWorld;
		pSprite->SetTransform(&matWorld);
		pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		pSprite->Draw(m_vecTexture_AddedFillLine[i], &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
		pSprite->End();
	}
	// <<

	// >> OutLine
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	SetRect(&rc, 0, 0, m_stSize_OutLine.nWidth, m_stSize_OutLine.nHeight);

	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, m_fScaleX_Outline, 1.0f, 1.0f);
	matWorld = matS * m_matWorld;
	pSprite->SetTransform(&matWorld);

	pSprite->Draw(m_pTexture_OutLine, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	pSprite->End();
	// <<

	cUIObject::Render(pSprite);
}

void cUIProgressBar::Destroy() 
{
	cUIObject::Destroy();
}

void cUIProgressBar::AddProgressBar(char* cFillLine_Path, D3DXVECTOR3 fillLine_Pos)
{
	D3DXIMAGE_INFO	pImageInfo;

	LPDIRECT3DTEXTURE9 newTex = TEXTURE->GetTexture(cFillLine_Path, pImageInfo);
	m_vecTexture_AddedFillLine.push_back(newTex);

	ST_SIZEN newSize = ST_SIZEN(pImageInfo.Width, pImageInfo.Height);
	m_vecSize_AddedFillLine.push_back(newSize);

	D3DXVECTOR3 newPos = fillLine_Pos;
	newPos += m_vPosition;
	m_vecPos_AddedFillLine.push_back(newPos);

	m_vecScaleFillLine.push_back(1.0f);
}

void cUIProgressBar::ResetBarLength(int index, float scale)
{
	m_vecScaleFillLine[index] = scale;
}