#pragma once
#include "cUIObject.h"
class cUIMiniMap :
	public cUIObject
{
	LPDIRECT3DTEXTURE9 m_pTexture;
	SYNTHESIZE(int, m_nAlpha, Alpha);
	int m_nCellPerRow;

public:
	cUIMiniMap();
	~cUIMiniMap();

	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	void Setup_Image(LPDIRECT3DTEXTURE9 texture, int nCellPerRow);
	int GetIndex();
};

