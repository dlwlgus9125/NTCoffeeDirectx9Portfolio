#pragma once
#include "cSceneManager.h"

// >> 
#include "cSkyBox.h"
#include "cHeightMap.h"
#include "cObjLoader.h"
#include "cConstruct.h"
// << 

class cTitleScene : public cIScene
{
private:
	LPD3DXSPRITE       m_pSprite;	

public:
	cTitleScene();
	~cTitleScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnRender();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Setup_DirLight();
};

