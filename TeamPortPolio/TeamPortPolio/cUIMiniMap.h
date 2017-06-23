#pragma once
#include "cUIObject.h"

class cUIButton;

class cUIMiniMap :
	public cUIObject
{
	LPDIRECT3DTEXTURE9 m_pTexture;
	SYNTHESIZE(int, m_nAlpha, Alpha);
	int m_nCellPerRow;

	// >>  끄는 버튼					버튼 수정해야 함
	D3DXVECTOR3					m_vBtnPos;
	cUIButton*					m_pBtn_Exit;
	// <<

	ST_SIZEN m_stBGSize;
	D3DXVECTOR3 m_vBGPos;
	LPDIRECT3DTEXTURE9 m_pTex_BG;
public:
	cUIMiniMap();
	~cUIMiniMap();

	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	void Setup_Image(string imagePath, int nCellPerRow);
	int GetIndex();

	void Setup_exitbtn(D3DXVECTOR3 btnPos, string sPath_idle, string sPath_mouseover, string sPath_clicked);
	void Setup_BG(D3DXVECTOR3 bgPos, string sPath);
};

