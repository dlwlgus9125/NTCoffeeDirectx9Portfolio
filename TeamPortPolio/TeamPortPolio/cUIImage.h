#pragma once

#include "cUIObject.h"

class cUIImage : public cUIObject
{
	LPDIRECT3DTEXTURE9 m_pTexture;
public:
	cUIImage();
	~cUIImage();

	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	void Setup_Image(string imagePath);
};

