#pragma once
#include "cSceneManager.h"

class cBattleScene_Human : public cIScene
{
	LPD3DXSPRITE			m_pSprite;
	ST_WEATHER				m_stWeather;

public:
	cBattleScene_Human();
	~cBattleScene_Human();

	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
	virtual void OnRender();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Setup_DirLight();
};

