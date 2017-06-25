#include "stdafx.h"
#include "cLoginScene.h"
#include "cUIImage.h"


cLoginScene::cLoginScene()
	: m_pImage_Bg(NULL), m_pSprite(NULL), m_isClosed(false)
	, m_pImage_Icon_Age(NULL), m_pImage_Icon_Violence(NULL)
{
	SOUND->LoadFile("LoginBGM", "Sound/BGM/LoginScene/01. A Siege of Worlds.mp3", true);
}


cLoginScene::~cLoginScene()
{
	SAFE_DELETE(m_pImage_Bg);
	SAFE_DELETE(m_pImage_Icon_Age);
	SAFE_DELETE(m_pImage_Icon_Violence);
	SAFE_DELETE(m_pSprite);
}

void cLoginScene::OnEnter()
{
	m_pImage_Bg = new cUIImage();
	m_pImage_Bg->Setup(D3DXVECTOR3(0, 0, 0.0f), UI_IMAGE);
	m_pImage_Bg->Setup_Image("Image/UI/LoginScene/Bg/Login1.png");
	m_pImage_Bg->SetSize(ST_SIZEN(m_pImage_Bg->GetSize().nWidth, m_pImage_Bg->GetSize().nHeight + 30));
	m_pImage_Bg->SetHidden(false);

	m_pImage_Icon_Age = new cUIImage();
	m_pImage_Icon_Age->Setup(D3DXVECTOR3(1050, 10, 0.0f), UI_IMAGE);
	m_pImage_Icon_Age->Setup_Image("Image/UI/LoginScene/Icon/Age.png");
	m_pImage_Icon_Age->SetSize(ST_SIZEN(m_pImage_Icon_Age->GetSize().nWidth, m_pImage_Icon_Age->GetSize().nHeight));
	m_pImage_Icon_Age->SetHidden(false);

	m_pImage_Icon_Violence = new cUIImage();
	m_pImage_Icon_Violence->Setup(D3DXVECTOR3(1155, 10, 0.0f), UI_IMAGE);
	m_pImage_Icon_Violence->Setup_Image("Image/UI/LoginScene/Icon/Violence.png");
	m_pImage_Icon_Violence->SetSize(ST_SIZEN(m_pImage_Icon_Violence->GetSize().nWidth, m_pImage_Icon_Violence->GetSize().nHeight));
	m_pImage_Icon_Violence->SetHidden(false);

	D3DXCreateSprite(D3DDevice, &m_pSprite);

	if (!SCENE->GetIsSoundPlayed())
	{
		SOUND->Play("LoginBGM", 1.0f);
		SCENE->SetIsSoundPlayed(true);
	}

	UI->Change(SCENE_LOGIN);
}

void cLoginScene::OnUpdate()
{
	m_pImage_Bg->Update(TIME->DeltaTime());
	m_pImage_Icon_Age->Update(TIME->DeltaTime());
	m_pImage_Icon_Violence->Update(TIME->DeltaTime());

	UI->Update(TIME->DeltaTime());

	int indexInMiniMap;
	int buttonIndex;
	int eventIDTap;
	int itemID;

	if (GetKeyState('P') && 0x8000 )
	{
		SOUND->Stop("LoginBGM");
		SCENE->SetIsSoundPlayed(false);
	}

	UI->GetEvent(indexInMiniMap, buttonIndex, eventIDTap, itemID);

	switch (buttonIndex)
	{
	case LOGIN_BTN_START:
		SCENE->ChangeScene(SCENE_SELECT);
		break;
	case LOGIN_BTN_HELP:
		SCENE->ChangeScene(SCENE_HELP);
		break;
	case LOGIN_BTN_EXIT:
		m_isClosed = true;
		break;

	}  
}

void cLoginScene::OnExit()
{
	m_pImage_Bg->Destroy();
	m_pImage_Icon_Age->Destroy();
	m_pImage_Icon_Violence->Destroy();

	UI->DestroyEventButton();
	UI->Release();
}

void cLoginScene::OnRender()
{
	m_pImage_Bg->Render(m_pSprite);
	m_pImage_Icon_Age->Render(m_pSprite);
	m_pImage_Icon_Violence->Render(m_pSprite);

	UI->Render(m_pSprite);
}

void cLoginScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_isClosed == true) PostQuitMessage(0);
}