#pragma once
#include "cSceneManager.h"

class cHelpScene : public cIScene
{
	cUIImage*			m_pImage;
	cUIButton*			m_pExitButton;
	cUIButton*			m_pExplainButton_Play;
	cUIButton*			m_pExplainButton_Town1;
	cUIButton*			m_pExplainButton_Town2;

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

