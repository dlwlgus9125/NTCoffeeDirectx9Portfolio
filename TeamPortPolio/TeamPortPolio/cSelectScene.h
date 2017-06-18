#pragma once
#include "cSceneManager.h"

class cPlayer;
class cCamera;

enum SELECTPLAYER
{
	SELECT_NONE,
	SELECT_HUMAN,
	SELECT_ORC,
};

class cSelectScene : public cIScene
{
	cUIImage*			m_pImage;
	LPD3DXSPRITE		m_pSprite;
	
	map<int, cPlayer*>	m_mapPlayer;
	int					m_nCurrentPlayer;

public:
	cSelectScene();
	~cSelectScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnRender();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void MovePosition();
};

