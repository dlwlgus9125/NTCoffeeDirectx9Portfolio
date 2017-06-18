#include "stdafx.h"
#include "cLoginScene.h"
#include "cUIImage.h"


cLoginScene::cLoginScene()
	:	m_pImage(NULL), m_pSprite(NULL), m_isClosed(false)
{
	SOUND->LoadFile("LoginBGM", "Sound/BGM/LoginScene/01. A Siege of Worlds.mp3", true);
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
	m_pImage->Setup_Image("Image/UI/LoginScene/Bg/Login1.png");
	m_pImage->SetSize(ST_SIZEN(m_pImage->GetSize().nWidth, m_pImage->GetSize().nHeight + 30));
	m_pImage->SetHidden(false);

	D3DXCreateSprite(D3DDevice, &m_pSprite);

	SOUND->Play("LoginBGM", 1.0f);

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
		SCENE->ChangeScene(SCENE_SELECT);
		break;
	case LOGIN_BTN_HELP:
		
		break;
	case LOGIN_BTN_EXIT:
		m_isClosed = true;
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
	if (m_isClosed == true) PostQuitMessage(0);
}