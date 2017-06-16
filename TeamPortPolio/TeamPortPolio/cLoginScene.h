#pragma once
#include "cSceneManager.h"

class cLoginScene : public cIScene
{
public:
	cLoginScene();
	~cLoginScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnRender();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

