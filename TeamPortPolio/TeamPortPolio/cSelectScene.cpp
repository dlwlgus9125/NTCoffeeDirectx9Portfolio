#include "stdafx.h"
#include "cSelectScene.h"


cSelectScene::cSelectScene()
	: m_pImage(NULL), m_pSprite(NULL), m_pImageInfo(NULL)
{
}


cSelectScene::~cSelectScene()
{
	SAFE_DELETE(m_pImage);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pImageInfo);
}

void cSelectScene::OnEnter()
{
	m_pImage = new cUIImage();
	m_pImageInfo = new D3DXIMAGE_INFO;
	m_pImage->Setup_Image(TEXTURE->GetTexture("Image/UI/SelectScene/Select1.png", m_pImageInfo));

	RECT rc;
	m_pImage->Setup(D3DXVECTOR3(0, 0, 0.0f), UI_IMAGE);
	m_pImage->SetSize(ST_SIZEN(m_pImageInfo->Width, m_pImageInfo->Height + 30));
	m_pImage->SetHidden(false);

	D3DXCreateSprite(D3DDevice, &m_pSprite);

	UI->Change(SCENE_LOGIN);
}

void cSelectScene::OnUpdate()
{
	m_pImage->Update(TIME->DeltaTime());

	UI->Update(TIME->DeltaTime());
}

void cSelectScene::OnExit()
{
	m_pImage->Destroy();

	UI->Release();
}

void cSelectScene::OnRender()
{
	m_pImage->Render(m_pSprite);

	UI->Render(m_pSprite);
}

void cSelectScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}