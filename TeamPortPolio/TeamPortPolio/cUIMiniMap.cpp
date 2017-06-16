#include "stdafx.h"
#include "cUIMiniMap.h"


cUIMiniMap::cUIMiniMap() : m_pTexture(NULL), m_nCellPerRow(0), m_nAlpha(NULL)
{
	SetSize(ST_SIZEN(500, 500));
	m_isHidden = true;
}


cUIMiniMap::~cUIMiniMap()
{
}

void cUIMiniMap::Update(float deltaTime)
{
	cUIObject::Update(deltaTime);
}

void cUIMiniMap::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	RECT rc;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);

	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));

	pSprite->End();

	cUIObject::Render(pSprite);
}

void cUIMiniMap::Destroy()
{
	SAFE_RELEASE(m_pTexture);

	cUIObject::Destroy();
}

void cUIMiniMap::Setup_Image(LPDIRECT3DTEXTURE9 texture, int nCellPerRow)
{
	m_pTexture = texture;
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