#pragma once
#include "cSceneManager.h"

class cBattleScene_Orc : public cIScene
{
	LPD3DXSPRITE			m_pSprite;
	ST_WEATHER				m_stWeather;

public:
	cBattleScene_Orc();
	~cBattleScene_Orc();

	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
	virtual void OnRender();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Setup_DirLight();
};

