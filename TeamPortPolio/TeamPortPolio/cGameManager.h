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


};


