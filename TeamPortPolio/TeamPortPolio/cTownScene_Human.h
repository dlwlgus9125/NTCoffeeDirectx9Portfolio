#pragma once
#include "cSceneManager.h"

class cTownScene_Human : public cIScene
{
	LPD3DXSPRITE			m_pSprite;

	vector<ST_SPHERE>		m_vecST_Sphere;

	ST_WEATHER				m_stWeather;

	int						m_nNextSceneID;
public:
	cTownScene_Human();
	~cTownScene_Human();

	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
	virtual void OnRender();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Setup_DirLight();
	void ConnectSpere();
};

