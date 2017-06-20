#include "stdafx.h"
#include "cLoginScene.h"
#include "cUIImage.h"


cLoginScene::cLoginScene()
	: m_pImage_Bg(NULL), m_pSprite(NULL), m_isClosed(false)
{
	SOUND->LoadFile("LoginBGM", "Sound/BGM/LoginScene/01. A Siege of Worlds.mp3", true);
}


cLoginScene::~cLoginScene()
{
	SAFE_DELETE(m_pImage_Bg);
	SAFE_DELETE(m_pSprite);
}

void cLoginScene::OnEnter()
{
	m_pImage_Bg = new cUIImage();
	m_pImage_Bg->Setup(D3DXVECTOR3(0, 0, 0.0f), UI_IMAGE);
	m_pImage_Bg->Setup_Image("Image/UI/LoginScene/Bg/Login1.png");
	m_pImage_Bg->SetSize(ST_SIZEN(m_pImage_Bg->GetSize().nWidth, m_pImage_Bg->GetSize().nHeight + 30));
	m_pImage_Bg->SetHidden(false);

	D3DXCreateSprite(D3DDevice, &m_pSprite);

	SOUND->Play("LoginBGM", 1.0f);

	UI->Change(SCENE_LOGIN);
}

void cLoginScene::OnUpdate()
{
	m_pImage_Bg->Update(TIME->DeltaTime());

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
	m_pImage_Bg->Destroy();

	UI->Release();
}

void cLoginScene::OnRender()
{
	m_pImage_Bg->Render(m_pSprite);

	UI->Render(m_pSprite);
}

void cLoginScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_isClosed == true) PostQuitMessage(0);
}