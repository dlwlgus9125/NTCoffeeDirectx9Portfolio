#include "stdafx.h"
#include "cHelpScene.h"
#include "cUIImage.h"

cHelpScene::cHelpScene()
	: m_pImage(NULL), m_pSprite(NULL), m_pExitButton(NULL)
	, m_pExplainButton_Play(NULL), m_pExplainButton_Town1(NULL), m_pExplainButton_Town2(NULL), m_pExplainButton_Battle(NULL)
	, m_pImage_Play(NULL), m_pImage_Town1(NULL), m_pImage_Town2(NULL), m_pImage_Battle(NULL)
{
}

cHelpScene::~cHelpScene()
{
	SAFE_DELETE(m_pImage);
	SAFE_DELETE(m_pImage_Play);
	SAFE_DELETE(m_pImage_Town1);
	SAFE_DELETE(m_pImage_Town2);
	SAFE_DELETE(m_pImage_Battle);

	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pExitButton);
	SAFE_DELETE(m_pExplainButton_Play);
	SAFE_DELETE(m_pExplainButton_Town1);
	SAFE_DELETE(m_pExplainButton_Town2);
	SAFE_DELETE(m_pExplainButton_Battle);
}

void cHelpScene::OnEnter()
{
	m_pImage = new cUIImage();
	m_pImage->Setup(D3DXVECTOR3(0, 0, 0.0f), UI_IMAGE);
	m_pImage->Setup_Image("Image/UI/HelpScene/Bg/BG.png");
	m_pImage->SetSize(ST_SIZEN(m_pImage->GetSize().nWidth, m_pImage->GetSize().nHeight + 30));
	m_pImage->SetHidden(false);

	m_pImage_Play = new cUIImage();
	m_pImage_Play->Setup(D3DXVECTOR3(380, 65, 0.0f), UI_IMAGE);
	m_pImage_Play->Setup_Image("Image/UI/HelpScene/Image/TextBox_Play.png");
	m_pImage_Play->SetSize(ST_SIZEN(m_pImage->GetSize().nWidth, m_pImage->GetSize().nHeight));

	m_pImage_Town1 = new cUIImage();
	m_pImage_Town1->Setup(D3DXVECTOR3(380, 65, 0.0f), UI_IMAGE);
	m_pImage_Town1->Setup_Image("Image/UI/HelpScene/Image/TextBox_Human.png");
	m_pImage_Town1->SetSize(ST_SIZEN(m_pImage->GetSize().nWidth, m_pImage->GetSize().nHeight));

	m_pImage_Town2 = new cUIImage();
	m_pImage_Town2->Setup(D3DXVECTOR3(380, 65, 0.0f), UI_IMAGE);
	m_pImage_Town2->Setup_Image("Image/UI/HelpScene/Image/TextBox_Orc.png");
	m_pImage_Town2->SetSize(ST_SIZEN(m_pImage->GetSize().nWidth, m_pImage->GetSize().nHeight));

	m_pImage_Battle = new cUIImage();
	m_pImage_Battle->Setup(D3DXVECTOR3(380,65, 0.0f), UI_IMAGE);
	m_pImage_Battle->Setup_Image("Image/UI/HelpScene/Image/TextBox_Battle.png");
	m_pImage_Battle->SetSize(ST_SIZEN(m_pImage->GetSize().nWidth, m_pImage->GetSize().nHeight));


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

	m_pExplainButton_Town1 = new cUIButton();
	m_pExplainButton_Town1->Setup(D3DXVECTOR3(70, 180, 0), UI_BUTTON);
	m_pExplainButton_Town1->Setup_Button("Image/UI/HelpScene/Button/Town_Human/Idle_Town_Human.png",
		"Image/UI/HelpScene/Button/Town_Human/MouseOver_Town_Human.png",
		"Image/UI/HelpScene/Button/Town_Human/Down_Town_Human.png", NULL);
	m_pExplainButton_Town1->SetHidden(false);

	m_pExplainButton_Town2 = new cUIButton();
	m_pExplainButton_Town2->Setup(D3DXVECTOR3(70, 290, 0), UI_BUTTON);
	m_pExplainButton_Town2->Setup_Button("Image/UI/HelpScene/Button/Town_Orc/Idle_Town_Orc.png",
		"Image/UI/HelpScene/Button/Town_Orc/MouseOver_Town_Orc.png",
		"Image/UI/HelpScene/Button/Town_Orc/Down_Town_Orc.png", NULL);
	m_pExplainButton_Town2->SetHidden(false);

	m_pExplainButton_Battle = new cUIButton();
	m_pExplainButton_Battle->Setup(D3DXVECTOR3(70, 400, 0), UI_BUTTON);
	m_pExplainButton_Battle->Setup_Button("Image/UI/HelpScene/Button/Battle/Idle_Battle.png",
		"Image/UI/HelpScene/Button/Battle/MouseOver_Battle.png",
		"Image/UI/HelpScene/Button/Battle/Down_Battle.png", NULL);
	m_pExplainButton_Battle->SetHidden(false);

	D3DXCreateSprite(D3DDevice, &m_pSprite);
}

void cHelpScene::OnUpdate()
{
	m_pImage->Update(TIME->DeltaTime());
	m_pImage_Play->Update(TIME->DeltaTime());
	m_pImage_Town1->Update(TIME->DeltaTime());
	m_pImage_Town2->Update(TIME->DeltaTime());
	m_pImage_Battle->Update(TIME->DeltaTime());
	
	m_pExitButton->Update(TIME->DeltaTime());
	m_pExplainButton_Play->Update(TIME->DeltaTime());
	m_pExplainButton_Town1->Update(TIME->DeltaTime());
	m_pExplainButton_Town2->Update(TIME->DeltaTime());
	m_pExplainButton_Battle->Update(TIME->DeltaTime());

	if (m_pExplainButton_Play->GetCurrentState() == UI_CLICKED) ChangeImage(HELPBUTTON_PLAY);
	if (m_pExplainButton_Town1->GetCurrentState() == UI_CLICKED) ChangeImage(HELPBUTTON_TOWN1);
	if (m_pExplainButton_Town2->GetCurrentState() == UI_CLICKED) ChangeImage(HELPBUTTON_TOWN2);
	if (m_pExplainButton_Battle->GetCurrentState() == UI_CLICKED) ChangeImage(HELPBUTTON_BATTLE);

	if (m_pExitButton->GetCurrentState() == UI_CLICKED) 	SCENE->ChangeScene(SCENE_LOGIN);
}

void cHelpScene::OnExit()
{
	m_pImage->Destroy();
	m_pImage_Play->Destroy();
	m_pImage_Town1->Destroy();
	m_pImage_Town2->Destroy();
	m_pImage_Battle->Destroy();

	m_pExitButton->Destroy();
	m_pExplainButton_Play->Destroy();
	m_pExplainButton_Town1->Destroy();
	m_pExplainButton_Town2->Destroy();
	m_pExplainButton_Battle->Destroy();
}

void cHelpScene::OnRender()
{
	m_pImage->Render(m_pSprite);
	m_pImage_Play->Render(m_pSprite);
	m_pImage_Town1->Render(m_pSprite);
	m_pImage_Town2->Render(m_pSprite);
	m_pImage_Battle->Render(m_pSprite);
	
	m_pExitButton->Render(m_pSprite);
	m_pExplainButton_Play->Render(m_pSprite);
	m_pExplainButton_Town1->Render(m_pSprite);
	m_pExplainButton_Town2->Render(m_pSprite);
	m_pExplainButton_Battle->Render(m_pSprite);
}

void cHelpScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void cHelpScene::ChangeImage(HELPBUTTON buttonID)
{
	m_pImage_Play->SetHidden(true);
	m_pImage_Town1->SetHidden(true);
	m_pImage_Town2->SetHidden(true);
	m_pImage_Battle->SetHidden(true);

	switch (buttonID)
	{
	case HELPBUTTON_PLAY:
		m_pImage_Play->SetHidden(false);
		break;

	case HELPBUTTON_TOWN1:
		m_pImage_Town1->SetHidden(false);
		break;

	case HELPBUTTON_TOWN2:
		m_pImage_Town2->SetHidden(false);
		break;

	case HELPBUTTON_BATTLE:
		m_pImage_Battle->SetHidden(false);
		break;
	}
}