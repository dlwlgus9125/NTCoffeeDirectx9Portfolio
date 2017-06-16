#pragma once
#include "cUIObject.h"

class cUITab :
	public cUIObject
{
	vector<ST_TAB>	m_vecTabInfo;
	ST_SIZEN m_stTitleSize;
	ST_SIZEN m_stBodySize;
	D3DXVECTOR3 m_vPos_Body;
	map<int, LPDIRECT3DTEXTURE9> m_mapTexture_Title;
	LPDIRECT3DTEXTURE9 m_pTexture_Body;
	FONT_TAG m_eFont;
public:
	cUITab();
	~cUITab();

	void Setup_Tap(string sPath_idle_title, string sPath_selected_title, ST_SIZEN titleSize, string sPath_body, D3DXVECTOR3 pos_body, ST_SIZEN bodySize, FONT_TAG eFont = FONT_DEF);
	void AddTitle(string title, D3DXVECTOR3 pos_title);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();
};

