#pragma once

#include "cUIObject.h"

class cUIProgressBar : public cUIObject
{
	LPDIRECT3DTEXTURE9 m_pTexture;

public:
	cUIProgressBar();
	~cUIProgressBar();

	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();
};

