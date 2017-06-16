#pragma once
#include "cSceneManager.h"

class cUIImage;

class cLoginScene : public cIScene
{  
	cUIImage*			m_pImage;
	LPD3DXSPRITE		m_pSprite;

public:
	cLoginScene();
	~cLoginScene();

	void OnEnter();
	void OnUpdate(); 
	void OnExit();
	void OnRender();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

