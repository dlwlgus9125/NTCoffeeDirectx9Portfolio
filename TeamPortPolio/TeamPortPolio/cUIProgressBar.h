#pragma once

#include "cUIObject.h"

class cUIProgressBar : public cUIObject
{
	LPDIRECT3DTEXTURE9	m_pTexture_OutLine;
	ST_SIZEN			m_stSize_OutLine;

	LPDIRECT3DTEXTURE9	m_pTexture_FillLine;
	ST_SIZEN			m_stSize_FillLine;
	D3DXVECTOR3			m_vPos_FillLine;

	float				m_fScaleX;
	SYNTHESIZE(float, m_fScaleX_Outline, ScaleOutline);
	SYNTHESIZE(bool, m_isFinished, IsFinished);

	vector<LPDIRECT3DTEXTURE9>			m_vecTexture_AddedFillLine;
	vector<ST_SIZEN>					m_vecSize_AddedFillLine;
	vector<D3DXVECTOR3>					m_vecPos_AddedFillLine;
	vector<float>						m_vecScaleFillLine;

public:
	cUIProgressBar();
	~cUIProgressBar();

	virtual void Setup_Progress(char* cOutLine_Path, char* cFillLine_Path, D3DXVECTOR3 fillLine_Pos);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();
	void AddProgressBar(char* cFillLine_Path, D3DXVECTOR3 fillLine_Pos);
	void ResetBarLength(int index, float scale);
};

