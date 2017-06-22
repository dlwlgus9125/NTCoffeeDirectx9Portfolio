#pragma once
#include "cSceneManager.h"

class cTownScene_Orc : public cIScene
{
	LPD3DXSPRITE			m_pSprite;

	vector<ST_SPHERE>		m_vecST_Sphere;

	ST_WEATHER				m_stWeather;

	int						m_nNextSceneID;
public:
	cTownScene_Orc();
	~cTownScene_Orc();

	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
	virtual void OnRender();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Setup_DirLight();
	void ConnectSpere();
};

