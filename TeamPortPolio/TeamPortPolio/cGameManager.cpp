#include "stdafx.h"
#include "cGameManager.h"
#include "cSceneManager.h"
#include "TestMap.h"
#include "cHelpScene.h"
#include "cTitleScene.h"
#include "cLoginScene.h"
#include "cLoadingScene.h"
#include "cSelectScene.h"
#include "cTownScene_Human.h"
#include "cTownScene_Orc.h"
#include "cBattleScene_Human.h"
#include "cBattleScene_Orc.h"
#include "cSceneCamera.h"
#include "cNpcDB.h"


void cGameManager::Init()
{
	DEVICE->Init();
	pGraph	  = NULL;
	pControl = NULL;
	pEvent	  = NULL;
	pPosition= NULL;
	pWindow  = NULL;
	HRESULT hr = 0;
	hr = CoInitialize(NULL);

	if (FAILED(hr))
		::MessageBox(0, "CoInitialize error", 0, 0);;
	
	hr = CoCreateInstance(
		CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder,
		(LPVOID*)&pGraph);

	if (FAILED(hr))
		::MessageBox(0, "CoCreateInstance error", 0, 0);
	
	g_pLog = new cLog();
	g_pLog->Setup();

	hr = pGraph->QueryInterface(IID_IMediaControl, (LPVOID*)&pControl);
	hr = pGraph->QueryInterface(IID_IMediaEvent, (LPVOID*)&pEvent);
	hr = pGraph->QueryInterface(IID_IMediaPosition, (LPVOID*)&pPosition);
	//pGraph->RenderFile(L"swf/013_defeating_isaac_in_the_cathedral.avi", NULL);;

	pGraph->RenderFile(L"Videos/NT_Coffee.avi", NULL); // 폴더경로 변경 및 불필요 자료 삭제 (변경자: 김윤중)

	hr = pGraph->QueryInterface(IID_IVideoWindow, (LPVOID*)&pWindow);
	
	if (SUCCEEDED(hr))
	{
		pWindow->put_Owner((OAHWND)g_hWnd);
		hr = pWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
		if (FAILED(hr))
		{
			::MessageBox(0, "WindowStyle error", 0, 0);
		}
		RECT rc;
		GetClientRect(g_hWnd, &rc);

		pWindow->SetWindowPosition(0, 0, rc.right, rc.bottom);
		pWindow->put_Visible(true);
	}

	else
		::MessageBox(0, "pWindow QueryInterface error", 0, 0);


	TIME->Init(60);
	UI->Setup();
	INPUT->Init();
	EFFECT->Init();
	OBJECTDB->Setup();
	OBJECT->Init();
	SOUND->Setup();
	ITEMDB->Setup();
	CHARACTERDB->Setup();
	NPC->FirstInit();
	SHADOW->Init();
	NPCDB->Setup();
	CAMERA->Setup();
	FRUSTUM->Setup();
	MAP->StartMain();
	ASTAR->Init();
	SCENE->Register(SCENE_LOGIN, new cLoginScene());
	SCENE->Register(SCENE_SELECT, new cSelectScene());
	SCENE->Register(SCENE_HELP, new cHelpScene());
	SCENE->Register(SCENE_TOWN_HUMAN, new cTownScene_Human());
	SCENE->Register(SCENE_TOWN_ORC, new cTownScene_Orc());
	SCENE->Register(SCENE_BATTLE_HUMAN, new cBattleScene_Human());
	SCENE->Register(SCENE_BATTLE_ORC, new cBattleScene_Orc());
	SCENE->Register(SCENE_LOADING, new cLoadingScene());
	SCENE->ChangeScene(SCENE_LOGIN);
	
	//
	srand((unsigned)time(NULL));

	
	//<<
}

void cGameManager::Update()
{

	if (!isOkView)
	{
		if (pEvent->GetEvent(&EventCode, &Param1, &Param2, 0) != E_ABORT)
		{
			if (EventCode == EC_COMPLETE)
			{
				isOkView = true;
				//pPosition->put_CurrentPosition(0);
				pControl->Release();
				pEvent->Release();
				pPosition->Release();
				pWindow->put_Visible(OAFALSE);
				// 윈도우 부모 윈도우 설정 해제.
				pWindow->put_Owner(NULL);
				pGraph->Release();
				pWindow->Release();
				CoUninitialize();
			}
		}

	}

	if (isOkView)
	{

		if (TIME->Update())
		{
			//cout << m_player->GetCharacterEntity()->Pos().x << ", " << m_player->GetCharacterEntity()->Pos().y << ", " << m_player->GetCharacterEntity()->Pos().z << endl;
		
			m_prevTime = m_currentTime;
			FRUSTUM->Update();
			INPUT->Update();

			if (INPUT->IsKeyDown(VK_V))g_showColider = true;
			if (INPUT->IsKeyDown(VK_B))g_showColider = false;

			if (SCENE->Current() == SCENE_SELECT) SCENE_CAMERA->Update();
			else CAMERA->Update();
			SCENE->Update();
			SOUND->Update();

			//if (OBJECT->GetPlayer() != NULL)ASTAR->Update();	
		}
	}
}

void cGameManager::Render()
{
	if(!isOkView)
		pControl->Run();
	else if (isOkView)
	{
		D3DDevice->Clear(NULL,
			NULL,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
			D3DCOLOR_XRGB(47, 121, 112),
			1.0f, 0);
		D3DDevice->BeginScene();
		SCENE->Render();
		D3DDevice->EndScene();
		D3DDevice->Present(NULL, NULL, NULL, NULL);
	}
}

void cGameManager::Release()
{
	ITEMDB->Destroy();
	CHARACTERDB->Destroy();
	OBJECTDB->Destroy();
	NPCDB->Destroy();
	OBJECT->Release();
	SOUND->Release();
	INPUT->Release();
	
	
	UI->Release();
	FONT->Destroy();
	EFFECT->Release();
	MAP->Destroy();
	SHADOW->Destroy();
	ASTAR->Release();
	THREAD->Destroy();
	TEXTURE->Destroy();
	g_pLog->Render();
	DEVICE->Destroy();
}

void cGameManager::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CAMERA->WndProc(hwnd, message, wParam, lParam);
	SCENE->WndProc(hwnd, message, wParam, lParam);

	if (!isOkView)
	{
		switch (message)
		{
		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				REFTIME endTime;
				pPosition->get_Duration(&endTime);
				double d_Time = endTime;
				pPosition->put_CurrentPosition(d_Time);
				break;
			}

		}
	}
}




