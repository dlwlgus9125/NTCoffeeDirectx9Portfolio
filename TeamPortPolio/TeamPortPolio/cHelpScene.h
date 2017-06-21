#pragma once
#include "cSceneManager.h"

class cHelpScene : public cIScene
{
	cUIImage*			m_pImage;
	LPD3DXSPRITE		m_pSprite;

public:
	cHelpScene();
	~cHelpScene();

	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
	virtual void OnRender();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

