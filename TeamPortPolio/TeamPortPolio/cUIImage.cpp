#include "stdafx.h"
#include "cUIImage.h"


cUIImage::cUIImage() : m_pTexture(NULL)
{
	SetSize(ST_SIZEN(200, 200));
}


cUIImage::~cUIImage()
{
}

void cUIImage::Update(float deltaTime)
{
	cUIObject::Update(deltaTime);
}

void cUIImage::Render(LPD3DXSPRITE pSprite)
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

void cUIImage::Destroy()
{
	SAFE_RELEASE(m_pTexture);

	cUIObject::Destroy();
}

void cUIImage::Setup_Image(LPDIRECT3DTEXTURE9 texture)
{
	m_pTexture = texture;
}