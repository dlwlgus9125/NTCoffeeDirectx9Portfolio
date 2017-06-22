#pragma once
#include "cSceneManager.h"

class cUIImage;
class cUIProgressBar;

class cLoadingScene : public cIScene
{
	cUIImage*			m_pImage;
	cUIProgressBar*		m_pProgressBar;
	LPD3DXSPRITE		m_pSprite;

public:
	cLoadingScene();
	~cLoadingScene();

	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
	virtual void OnRender();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

