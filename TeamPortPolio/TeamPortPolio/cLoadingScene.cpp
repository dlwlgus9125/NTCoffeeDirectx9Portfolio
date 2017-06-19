#include "stdafx.h"
#include "cLoadingScene.h"


cLoadingScene::cLoadingScene()
	: m_pImage(NULL), m_pSprite(NULL)
{
}


cLoadingScene::~cLoadingScene()
{
	SAFE_DELETE(m_pImage);
	SAFE_DELETE(m_pSprite);
}

void cLoadingScene::OnEnter()
{
	m_pImage = new cUIImage();
	m_pImage->Setup(D3DXVECTOR3(0, 0, 0.0f), UI_IMAGE);
	m_pImage->Setup_Image("Image/UI/LoadingScene/Bg/LoadingSceneBG.png");
	m_pImage->SetSize(ST_SIZEN(m_pImage->GetSize().nWidth, m_pImage->GetSize().nHeight + 30));
	m_pImage->SetHidden(false);

	D3DXCreateSprite(D3DDevice, &m_pSprite);

	UI->Change(SCENE_LOGIN);
}
void cLoadingScene::OnUpdate()
{

}
void cLoadingScene::OnExit()
{

}
void cLoadingScene::OnRender()
{

}
void cLoadingScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}