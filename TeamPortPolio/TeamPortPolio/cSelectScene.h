#pragma once
#include "cSceneManager.h"

class cSelectScene : public cIScene
{
public:
	cSelectScene();
	~cSelectScene();

	void OnEnter();
	void OnUpdate();
	void OnExit();
	void OnRender();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

