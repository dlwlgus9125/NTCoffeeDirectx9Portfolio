#pragma once
#include "cSceneManager.h"

class cTownScene_Orc : public cIScene
{
	LPD3DXSPRITE			m_pSprite;

	vector<ST_SPHERE>		m_vecST_Sphere;
	LPD3DXMESH				m_pMeshSphere;
	vector<D3DMATERIAL9>	m_vecMtlSphere;
public:
	cTownScene_Orc();
	~cTownScene_Orc();

	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
	virtual void OnRender();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Setup_DirLight();
};

