#pragma once
#include "cUIObject.h"
class cUIButton :
	public cUIObject
{
	UI_STATE m_eCurrentState;
	map<int, LPDIRECT3DTEXTURE9> m_mapTexture;
	SYNTHESIZE(int,	m_eEventID, EventID);
public:
	cUIButton();
	~cUIButton();

	void Setup_Button(string sPath_idle, string sPath_mouseover, string sPath_clicked, int eEventID);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();
	UI_STATE GetCurrentState() { return m_eCurrentState; }
};

