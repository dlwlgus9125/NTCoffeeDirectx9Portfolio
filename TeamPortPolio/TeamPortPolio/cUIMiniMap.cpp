#include "stdafx.h"
#include "cUIMiniMap.h"

#include "cUIButton.h"

cUIMiniMap::cUIMiniMap() : m_pTexture(NULL), m_nCellPerRow(0), m_nAlpha(255), m_pBtn_Exit(NULL), m_pTex_BG(NULL), m_pTex_Location(NULL), m_pTex_Location_unit(NULL), m_pTex_Location_enemy(NULL)
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

	// 미니맵 배경
	if (m_pTex_BG)
	{
		pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matWorld, m_vBGPos.x, m_vBGPos.y, m_vBGPos.z);
		SetRect(&rc, 0, 0, m_stBGSize.nWidth, m_stBGSize.nHeight);
		pSprite->SetTransform(&matWorld);
		pSprite->Draw(m_pTex_BG, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
		pSprite->End();
	}
	
	// 실제 미니맵
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	pSprite->End();

	// 종료 버튼
	if(m_pBtn_Exit) m_pBtn_Exit->Render(pSprite);
	
	// 위치 나타내는 그림
	if (m_pTex_Location)
	{
		pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		pSprite->SetTransform(&m_matWorld);
		SetRect(&rc, 0, 0, m_stLocationSize.nWidth, m_stLocationSize.nHeight);
		pSprite->Draw(m_pTex_Location, &rc, &D3DXVECTOR3(m_stLocationSize.nWidth * 0.5f, m_stLocationSize.nHeight * 0.5f, 0),
			&m_vLocationPos, D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
		pSprite->End();
	}
	if (m_pTex_Location_unit)
	{
		pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		pSprite->SetTransform(&m_matWorld);
		SetRect(&rc, 0, 0, m_stLocationSize_unit.nWidth, m_stLocationSize_unit.nHeight);
		pSprite->Draw(m_pTex_Location_unit, &rc, &D3DXVECTOR3(m_stLocationSize_unit.nWidth * 0.5f, m_stLocationSize_unit.nHeight * 0.5f, 0),
			&m_vLocationPos_unit, D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
		pSprite->End();
	}
	if (m_pTex_Location_enemy)
	{
		pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		pSprite->SetTransform(&m_matWorld);
		SetRect(&rc, 0, 0, m_stLocationSize_enemy.nWidth, m_stLocationSize_enemy.nHeight);
		pSprite->Draw(m_pTex_Location_enemy, &rc, &D3DXVECTOR3(m_stLocationSize_enemy.nWidth * 0.5f, m_stLocationSize_enemy.nHeight * 0.5f, 0),
			&m_vLocationPos_enemy, D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
		pSprite->End();
	}

	cUIObject::Render(pSprite);
}

void cUIMiniMap::Destroy()
{
	if(m_pBtn_Exit) m_pBtn_Exit->Destroy();
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

void cUIMiniMap::Setup_Location(string sPath, string sPath_unit, string sPath_enemy)
{
	D3DXIMAGE_INFO info;
	m_pTex_Location = TEXTURE->GetTexture(sPath, info);
	m_stLocationSize = ST_SIZEN(info.Width, info.Height);

	m_pTex_Location_unit = TEXTURE->GetTexture(sPath_unit, info);
	m_stLocationSize_unit = ST_SIZEN(info.Width, info.Height);

	m_pTex_Location_enemy = TEXTURE->GetTexture(sPath_enemy, info);
	m_stLocationSize_enemy = ST_SIZEN(info.Width, info.Height);
}

void cUIMiniMap::Update_Location(D3DXVECTOR2 pos_uv, D3DXVECTOR2 pos_uv_unit, D3DXVECTOR2 pos_uv_eneny)
{
	if (m_isHidden) return;

	float u = pos_uv.x;
	float v = 1 - pos_uv.y;

	float x = m_stSize.nWidth * u;
	float y = m_stSize.nHeight * v;

	m_vLocationPos = D3DXVECTOR3(x, y, 0);

	u = pos_uv_unit.x;
	v = 1 - pos_uv_unit.y;

	x = m_stSize.nWidth * u;
	y = m_stSize.nHeight * v;

	m_vLocationPos_unit = D3DXVECTOR3(x, y, 0);

	u = pos_uv_eneny.x;
	v = 1 - pos_uv_eneny.y;

	x = m_stSize.nWidth * u;
	y = m_stSize.nHeight * v;

	m_vLocationPos_enemy = D3DXVECTOR3(x, y, 0);
}