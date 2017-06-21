#include "stdafx.h"
#include "cLoadingScene.h"
#include "cPlayer.h"
#include "cUIImage.h"
#include "cUIProgressBar.h"


cLoadingScene::cLoadingScene()
	: m_pImage(NULL), m_pSprite(NULL), m_pProgressBar(NULL)
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

	m_pProgressBar = new cUIProgressBar();
	m_pProgressBar->Setup(D3DXVECTOR3(120, 600, 0.0f), UI_PROGRESSBAR);
	m_pProgressBar->Setup_Progress("Image/UI/LoadingScene/Line/OutLine.png", "Image/UI/LoadingScene/Line/FillLine.png", D3DXVECTOR3(30, 20, 0));
	m_pProgressBar->SetHidden(false);
}

void cLoadingScene::OnUpdate()
{
	m_pImage->Update(TIME->DeltaTime());
	m_pProgressBar->Update(TIME->DeltaTime());

	if (m_pProgressBar->GetIsFinished())
	{
		cPlayer* player = OBJECT->GetPlayer();
		if (player->GetID() == C_C_HUMAN_MALE) SCENE->ChangeScene(SCENE_BATTLE_HUMAN);
		else if (player->GetID() == C_C_ORC_MALE) SCENE->ChangeScene(SCENE_BATTLE_ORC);
	}
}

void cLoadingScene::OnExit()
{
	m_pImage->Destroy();
	m_pProgressBar->Destroy();
}

void cLoadingScene::OnRender()
{
	m_pImage->Render(m_pSprite);
	m_pProgressBar->Render(m_pSprite);
}

void cLoadingScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}