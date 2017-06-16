#include "stdafx.h"
#include "cSelectScene.h"


cSelectScene::cSelectScene()
	: m_pSprite(NULL)
{
}


cSelectScene::~cSelectScene()
{
	SAFE_RELEASE(m_pSprite);
}

void cSelectScene::OnEnter()
{
	UI->Setup();
}

void cSelectScene::OnUpdate()
{
	UI->Update(TIME->DeltaTime());
}

void cSelectScene::OnExit()
{
	UI->Release();
}

void cSelectScene::OnRender()
{
	UI->Render(m_pSprite);
}

void cSelectScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}