#pragma once
#include "cUIObject.h"
class cUIText :
	public cUIObject
{
	SYNTHESIZE(string, m_sText, Text);
	FONT_TAG m_eFont;
public:
	cUIText();
	~cUIText();

	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	void Setup_Text(string text, int width, int height, FONT_TAG tag = FONT_DEF);
};

