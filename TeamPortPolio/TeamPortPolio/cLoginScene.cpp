#include "stdafx.h"
#include "cLoginScene.h"
#include "cUIImage.h"


cLoginScene::cLoginScene()
	:	m_pImage(NULL), m_pSprite(NULL)
{
}


cLoginScene::~cLoginScene()
{
	SAFE_DELETE(m_pImage);
	SAFE_DELETE(m_pSprite);
}

void cLoginScene::OnEnter()
{
	m_pImage = new cUIImage();
	m_pImage->Setup(D3DXVECTOR3(0, 0, 0.0f), UI_IMAGE);
	m_pImage->Setup_Image("Image/UI/LoginScene/Login1.png");
	m_pImage->SetHidden(false);

	D3DXCreateSprite(D3DDevice, &m_pSprite);

	UI->Change(SCENE_LOGIN);
}

void cLoginScene::OnUpdate()
{
	m_pImage->Update(TIME->DeltaTime());

	UI->Update(TIME->DeltaTime());


	int indexInMiniMap;
	int buttonIndex;
	int eventIDTap;
	int itemID;

	UI->GetEvent(indexInMiniMap, buttonIndex, eventIDTap, itemID);

	switch (buttonIndex)
	{
	case LOGIN_BTN_START:
	
		break;
	case LOGIN_BTN_HELP:
		
		break;
	case LOGIN_BTN_EXIT:

		break;

	}
}

void cLoginScene::OnExit()
{
	m_pImage->Destroy();

	UI->Release();
}

void cLoginScene::OnRender()
{
	m_pImage->Render(m_pSprite);

	UI->Render(m_pSprite);
}

void cLoginScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}