#include "stdafx.h"
#include "cUIMiniMap.h"

#include "cUIButton.h"

cUIMiniMap::cUIMiniMap() : m_pTexture(NULL), m_nCellPerRow(0), m_nAlpha(255), m_pBtn_Exit(NULL), m_pTex_BG(NULL)
{
	SetSize(ST_SIZEN(500, 500));
	m_isHidden = true;
}


cUIMiniMap::~cUIMiniMap()
{
}

void cUIMiniMap::Update(float deltaTime)
{
	if (m_pBtn_Exit) m_pBtn_Exit->SetHidden(m_isHidden);
	if (m_isHidden) return;
	// >> 종료버튼 업데이트 및 클릭 시 hidden되도록
	if (m_pBtn_Exit)
	{
		m_pBtn_Exit->Update(deltaTime);
		if (m_pBtn_Exit->GetCurrentState() == UI_CLICKED)
		{
			m_isHidden = true;
		}
	}	
	// << 

	cUIObject::Update(deltaTime);
}

void cUIMiniMap::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	RECT rc;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	
	if (m_pTex_BG)
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matWorld, m_vBGPos.x, m_vBGPos.y, m_vBGPos.z);
		SetRect(&rc, 0, 0, m_stBGSize.nWidth, m_stBGSize.nHeight);
		pSprite->SetTransform(&matWorld);
		pSprite->Draw(m_pTex_BG, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	}

	pSprite->SetTransform(&m_matWorld);
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));

	pSprite->End();

	if(m_pBtn_Exit) m_pBtn_Exit->Render(pSprite);

	cUIObject::Render(pSprite);
}

void cUIMiniMap::Destroy()
{
	m_pBtn_Exit->Destroy();
	cUIObject::Destroy();
}

void cUIMiniMap::Setup_Image(string imagePath, int nCellPerRow)
{
	D3DXIMAGE_INFO info;
	m_pTexture = TEXTURE->GetTexture(imagePath, info);
	SetSize(ST_SIZEN(info.Width, info.Height));
	m_nCellPerRow = nCellPerRow;
}

int cUIMiniMap::GetIndex()
{
	D3DXVECTOR2 cursorPos = INPUT->GetMousePosVector2();
	if (!m_isHidden &&
		INPUT->IsMouseDown(MOUSE_RIGHT) &&
		MATH->IsCollided(cursorPos, LeftTop(), RightBottom()))
	{
		D3DXVECTOR2 pos = cursorPos - LeftTop();
		int col = (int)(pos.x * m_nCellPerRow / m_stSize.nWidth) % m_nCellPerRow;
		int row = (int)(pos.y * m_nCellPerRow / m_stSize.nHeight) % m_nCellPerRow;

		row = (m_nCellPerRow - 1) - row;	// 맵이 -x, -z쪽부터 좌측으로 그려지기 때문에 row를 거꾸로 함.

		return row * m_nCellPerRow + col;
	}
	
	return -1;
}

void cUIMiniMap::Setup_exitbtn(D3DXVECTOR3 btnPos, string sPath_idle, string sPath_mouseover, string sPath_clicked)
{
	m_pBtn_Exit = new cUIButton;
	m_vBtnPos = m_vPosition + btnPos;
	m_pBtn_Exit->Setup(m_vBtnPos, UI_BUTTON);
	m_pBtn_Exit->Setup_Button(sPath_idle, sPath_mouseover, sPath_clicked, TOWN_BTN_SHOPEXIT);
}

void cUIMiniMap::Setup_BG(D3DXVECTOR3 bgPos, string sPath)
{
	m_vBGPos = bgPos;
	D3DXIMAGE_INFO info;
	m_pTex_BG = TEXTURE->GetTexture(sPath, info);
	m_stBGSize  = ST_SIZEN(info.Width, info.Height);
}