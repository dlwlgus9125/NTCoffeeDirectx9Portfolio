#include "stdafx.h"
#include "cLoginScene.h"
#include "cUIImage.h"


cLoginScene::cLoginScene()
	:	m_pImage(NULL), m_pSprite(NULL), m_pImageInfo(NULL)
{
}


cLoginScene::~cLoginScene()
{
	SAFE_DELETE(m_pImage);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pImageInfo);
}

void cLoginScene::OnEnter()
{
	m_pImage = new cUIImage();
	m_pImageInfo = new D3DXIMAGE_INFO;
	m_pImage->Setup_Image(TEXTURE->GetTexture("Image/UI/LoginScene/Login1.png", m_pImageInfo));

	RECT rc;
	m_pImage->Setup(D3DXVECTOR3(0, 0, 0.0f), UI_IMAGE);
	m_pImage->SetSize(ST_SIZEN(m_pImageInfo->Width, m_pImageInfo->Height));
	m_pImage->SetHidden(false);

	D3DXCreateSprite(D3DDevice, &m_pSprite);

	UI->Change(SCENE_LOGIN);
}

void cLoginScene::OnUpdate()
{
	m_pImage->Update(TIME->DeltaTime());

	UI->Update(TIME->DeltaTime());
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