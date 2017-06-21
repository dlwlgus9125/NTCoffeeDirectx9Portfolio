#include "stdafx.h"
#include "cHelpScene.h"
#include "cUIImage.h"

cHelpScene::cHelpScene()
	: m_pImage(NULL), m_pSprite(NULL), m_pExitButton(NULL)
	, m_pExplainButton_Play(NULL), m_pExplainButton_Town1(NULL), m_pExplainButton_Town2(NULL)
{
}

cHelpScene::~cHelpScene()
{
	SAFE_DELETE(m_pImage);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pExitButton);
	SAFE_DELETE(m_pExplainButton_Play);
	SAFE_DELETE(m_pExplainButton_Town1);
	SAFE_DELETE(m_pExplainButton_Town2);
}

void cHelpScene::OnEnter()
{
	m_pImage = new cUIImage();
	m_pImage->Setup(D3DXVECTOR3(0, 0, 0.0f), UI_IMAGE);
	m_pImage->Setup_Image("Image/UI/HelpScene/Bg/BG.png");
	m_pImage->SetSize(ST_SIZEN(m_pImage->GetSize().nWidth, m_pImage->GetSize().nHeight + 30));
	m_pImage->SetHidden(false);

	m_pExitButton = new cUIButton();
	m_pExitButton->Setup(D3DXVECTOR3(1220, 3, 0), UI_BUTTON);
	m_pExitButton->Setup_Button("Image/UI/HelpScene/Icon/Idle.png",
		"Image/UI/HelpScene/Icon/MouseOver.png",
		"Image/UI/HelpScene/Icon/Down.png", NULL);
	m_pExitButton->SetHidden(false);

	m_pExplainButton_Play = new cUIButton();
	m_pExplainButton_Play->Setup(D3DXVECTOR3(70, 70, 0), UI_BUTTON);
	m_pExplainButton_Play->Setup_Button("Image/UI/HelpScene/Button/Play/Idle_Play.png",
		"Image/UI/HelpScene/Button/Play/MouseOver_Play.png",
		"Image/UI/HelpScene/Button/Play/Down_Play.png", NULL);
	m_pExplainButton_Play->SetHidden(false);

	// m_pExplainButton_Town1 = new cUIButton();
	// m_pExplainButton_Town1->Setup(D3DXVECTOR3(1220, 3, 0), UI_BUTTON);
	// m_pExplainButton_Town1->Setup_Button("Image/UI/HelpScene/Icon/Idle.png",
	// 	"Image/UI/HelpScene/Icon/MouseOver.png",
	// 	"Image/UI/HelpScene/Icon/Down.png", NULL);
	// m_pExplainButton_Town1->SetHidden(false);
	// 
	// m_pExplainButton_Town2 = new cUIButton();
	// m_pExplainButton_Town2->Setup(D3DXVECTOR3(1220, 3, 0), UI_BUTTON);
	// m_pExplainButton_Town2->Setup_Button("Image/UI/HelpScene/Icon/Idle.png",
	// 	"Image/UI/HelpScene/Icon/MouseOver.png",
	// 	"Image/UI/HelpScene/Icon/Down.png", NULL);
	// m_pExplainButton_Town2->SetHidden(false);

	D3DXCreateSprite(D3DDevice, &m_pSprite);
}

void cHelpScene::OnUpdate()
{
	m_pImage->Update(TIME->DeltaTime());
	m_pExitButton->Update(TIME->DeltaTime());
	m_pExplainButton_Play->Update(TIME->DeltaTime());

	if (m_pExitButton->GetCurrentState() == UI_CLICKED) SCENE->ChangeScene(SCENE_LOGIN);
}

void cHelpScene::OnExit()
{
	m_pImage->Destroy();
	m_pExitButton->Destroy();
	m_pExplainButton_Play->Destroy();
}

void cHelpScene::OnRender()
{
	m_pImage->Render(m_pSprite);
	m_pExitButton->Render(m_pSprite);
	m_pExplainButton_Play->Render(m_pSprite);
}

void cHelpScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}