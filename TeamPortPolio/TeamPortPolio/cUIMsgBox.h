#pragma once
#include "cUIObject.h"
class cUIMsgBox :
	public cUIObject
{
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_vMsgPos;
	SYNTHESIZE(string, m_sText, Text);
	FONT_TAG m_eFont;
	ST_SIZEN m_stMsgBorder;
public:
	cUIMsgBox();
	~cUIMsgBox();

	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	void Setup_MsgBox(string imagePath, D3DXVECTOR3 msgPos, ST_SIZEN msgBorder,int eEventID, FONT_TAG eFont = FONT_DEF);
	void Setup_Text(string text);
};

