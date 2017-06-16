#pragma once
#include "cSceneManager.h"
class cTownScene :
	public cIScene
{
	LPD3DXSPRITE			m_pSprite;

	// >> 테스트용
	vector<ST_SPHERE>		m_vecST_Sphere;
	LPD3DXMESH				m_pMeshSphere;
	vector<D3DMATERIAL9>	m_vecMtlSphere;
	// << 
public:
	cTownScene();
	~cTownScene();

	virtual void OnEnter();
	virtual void OnUpdate();
	virtual void OnExit();
	virtual void OnRender();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Setup_DirLight();
};

