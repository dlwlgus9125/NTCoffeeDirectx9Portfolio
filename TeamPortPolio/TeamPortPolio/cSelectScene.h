#pragma once
#include "cSceneManager.h"

class cSelectScene : public cIScene
{
	cUIImage*			m_pImage;
	D3DXIMAGE_INFO*		m_pImageInfo;
	LPD3DXSPRITE		m_pSprite;

public:
	cSelectScene();
	~cSelectScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnRender();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

