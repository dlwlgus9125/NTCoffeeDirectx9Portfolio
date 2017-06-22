#pragma once
#include "cSceneManager.h"

enum HELPBUTTON
{
	HELPBUTTON_PLAY,
	HELPBUTTON_TOWN1,
	HELPBUTTON_TOWN2,
	HELPBUTTON_BATTLE,
};

class cHelpScene : public cIScene
{
	cUIImage*			m_pImage;
	cUIImage*			m_pImage_Play;
	cUIImage*			m_pImage_Town1;
	cUIImage*			m_pImage_Town2;
	cUIImage*			m_pImage_Battle;

	cUIButton*			m_pExitButton;
	cUIButton*			m_pExplainButton_Play;
	cUIButton*			m_pExplainButton_Town1;
	cUIButton*			m_pExplainButton_Town2;
	cUIButton*			m_pExplainButton_Battle;

	LPD3DXSPRITE		m_pSprite;

public:
	cHelpScene();
	~cHelpScene();

	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
	virtual void OnRender();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void ChangeImage(HELPBUTTON buttonID);
};

