#pragma once
#include "cCamera.h"
#include "cPlayer.h"

#define GAMEMAIN cGameManager::Instance()
class cGameManager : public Singleton<cGameManager>
{ 
private:
	float m_frameTime;
	float m_currentTime;
	float m_prevTime;

	bool  m_isSelectScene;

public:
	void Init();
	void Update();
	void Render();
	void Release();

	void WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool isOkView = false;
	bool isOkSetup = false;
	IGraphBuilder*  pGraph;
	IMediaControl*  pControl;
	IMediaEvent*    pEvent;
	IMediaPosition* pPosition;
	IVideoWindow*   pWindow;
	long EventCode, Param1, Param2;
	
	void SealMouse()
	{
		POINT pt;
		GetCursorPos(&pt);
		if (INPUT->GetMousePos().x<0)SetCursorPos(pt.x - INPUT->GetMousePos().x + 1, pt.y);
		if (INPUT->GetMousePos().y<0)SetCursorPos(pt.x, pt.y - INPUT->GetMousePos().y + 1);
		if (pt.x>WND_WIDTH - 0.5 * (pt.x - INPUT->GetMousePos().x))SetCursorPos(WND_WIDTH - 0.5*(pt.x - INPUT->GetMousePos().x), pt.y);
		if (pt.y>WND_HEIGHT -0.5*( pt.y - INPUT->GetMousePos().y))SetCursorPos(pt.x, WND_HEIGHT - 0.5 * (pt.y - INPUT->GetMousePos().y));
	}

};


