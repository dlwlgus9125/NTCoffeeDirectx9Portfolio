#pragma once
#include "cSceneManager.h"
 
class cUIImage;

class cLoginScene : public cIScene
{  
	cUIImage*			m_pImage_Bg;
	cUIImage*			m_pImage_Icon_Age;
	cUIImage*			m_pImage_Icon_Violence;
	LPD3DXSPRITE		m_pSprite;

	SYNTHESIZE(bool, m_isClosed, IsClosed);

public:
	cLoginScene();
	~cLoginScene();

	void OnEnter();
	void OnUpdate(); 
	void OnExit();
	void OnRender();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

