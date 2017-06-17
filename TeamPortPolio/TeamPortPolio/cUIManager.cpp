#include "stdafx.h"
#include "cUIManager.h"

// 타이틀씬에 대한 UI 설정
void cUIManager::Setup_TitleScene()
{
	// 미니맵
	m_pMiniMap = new cUIMiniMap;
	m_pMiniMap->Setup(D3DXVECTOR3(WND_WIDTH * 0.25f, WND_HEIGHT * 0.10f, 0), UI_MINIMAP);
	m_pMiniMap->Setup_Image("image/UI/titlescene/minimap/testmap.png", 150);
	m_pMiniMap->SetAlpha(150);

	// 미니맵버튼 1
	cUIButton* pBtn_start = new cUIButton;
	pBtn_start->Setup(D3DXVECTOR3(50, m_pMiniMap->GetSize().nHeight, 0), UI_BUTTON);
	pBtn_start->Setup_Button("Image/UI/titlescene/button/formation_rect/idle.png", 
		"Image/UI/titlescene/button/formation_rect/mouseover.png", 
		"Image/UI/titlescene/button/formation_rect/selected.png", TITLE_BTN_FMT_RECT);
	m_vecEventBtn.push_back(pBtn_start);
	m_pMiniMap->AddChild(pBtn_start);

	// 미니맵버튼 2
	cUIButton* pBtn_Help = new cUIButton;
	pBtn_Help->Setup(D3DXVECTOR3(150, m_pMiniMap->GetSize().nHeight, 0), UI_BUTTON);
	pBtn_Help->Setup_Button("Image/UI/titlescene/button/formation_tri/idle.png",
		"Image/UI/titlescene/button/formation_tri/mouseover.png",
		"Image/UI/titlescene/button/formation_tri/selected.png", TITLE_BTN_FMT_TRI);
	m_vecEventBtn.push_back(pBtn_Help);
	m_pMiniMap->AddChild(pBtn_Help);

	// 미니맵버튼 3
	cUIButton* pBtn_Exit = new cUIButton;
	pBtn_Exit->Setup(D3DXVECTOR3(300, m_pMiniMap->GetSize().nHeight, 0), UI_BUTTON);
	pBtn_Exit->Setup_Button("Image/UI/titlescene/button/state_att/idle.png",
		"Image/UI/titlescene/button/state_att/mouseover.png",
		"Image/UI/titlescene/button/state_att/selected.png", TITLE_BTN_ATTSTATE);
	m_vecEventBtn.push_back(pBtn_Exit);
	m_pMiniMap->AddChild(pBtn_Exit);

	// 미니맵버튼 4
	cUIButton* pButton4 = new cUIButton;
	pButton4->Setup(D3DXVECTOR3(400, m_pMiniMap->GetSize().nHeight, 0), UI_BUTTON);
	pButton4->Setup_Button("Image/UI/titlescene/button/state_def/idle.png",
		"Image/UI/titlescene/button/state_def/mouseover.png",
		"Image/UI/titlescene/button/state_def/selected.png", TITLE_BTN_DEFSTATE);
	m_vecEventBtn.push_back(pButton4);
	m_pMiniMap->AddChild(pButton4);
}

void cUIManager::Setup_TownScene()
{
	// >> 상점 1 탭 테스트용
	cUITab* pTab_Weapon = new cUITab();
	pTab_Weapon->Setup(D3DXVECTOR3(0, 0, 0), UI_TAB);
	pTab_Weapon->Setup_Tap("image/ui/townscene/tab_shop/idle.png", "image/ui/townscene/tab_shop/selected.png", "image/ui/townscene/tab_shop/body.png", D3DXVECTOR3(0, 0, 0));
	pTab_Weapon->AddTitle("검", D3DXVECTOR3(0, 600, 0));
	pTab_Weapon->AddTitle("도끼", D3DXVECTOR3(170, 600, 0));

	// 상점 1 슬롯 테스트용
	pTab_Weapon->Setup_Slot(D3DXVECTOR3(5, 20, 0), 2, 10, D3DXVECTOR3(0, 0, 0), ST_SIZEN(190, 70),
		D3DXVECTOR3(0, 0, 0), ST_SIZEN(50, 50), D3DXVECTOR3(55, 0, 0), ST_SIZEN(140, 50), FONT_SHOP);
	pTab_Weapon->AddSlotData(ITEMDB->GetItem(I_S_SHORTSWORD)->eSmallID, ITEMDB->GetItem(I_S_SHORTSWORD)->name, ITEMDB->GetItem(I_S_SHORTSWORD)->szImagePath, ITEMDB->GetItem(I_S_SHORTSWORD)->info);
	pTab_Weapon->AddSlotData(ITEMDB->GetItem(I_S_LONGSWORD )->eSmallID, ITEMDB->GetItem(I_S_LONGSWORD)->name,ITEMDB->GetItem(I_S_LONGSWORD)->szImagePath, ITEMDB->GetItem(I_S_LONGSWORD)->info);
	pTab_Weapon->AddSlotData(ITEMDB->GetItem(I_S_BASTARDSWORD)->eSmallID, ITEMDB->GetItem(I_S_BASTARDSWORD)->name, ITEMDB->GetItem(I_S_BASTARDSWORD)->szImagePath, ITEMDB->GetItem(I_S_BASTARDSWORD)->info);
	pTab_Weapon->SetShownData(0);

	pTab_Weapon->SetEventID(TOWN_TAB_SHOP_ATT);
	m_vecTab.push_back(pTab_Weapon);
	// <<
}

void cUIManager::Setup_LoginScene()
{
	// 시작버튼
	cUIButton* pBtn_start = new cUIButton;
	pBtn_start->Setup(D3DXVECTOR3(550, 320, 0), UI_BUTTON);
	pBtn_start->Setup_Button("Image/UI/loginscene/StartButton/BT_STAND.png",
		"Image/UI/loginscene/StartButton/BT_MOUSE_OVER.png",
		"Image/UI/loginscene/StartButton/BT_SELECT.png", LOGIN_BTN_START);
	m_vecShownBtn.push_back(pBtn_start);
	m_vecEventBtn.push_back(pBtn_start);
	pBtn_start->SetHidden(false);

	// 도움말버튼
	cUIButton* pBtn_Help = new cUIButton;
	pBtn_Help->Setup(D3DXVECTOR3(550, 400, 0), UI_BUTTON);
	pBtn_Help->Setup_Button("Image/UI/loginscene/HelpButton/BT_STAND.png",
		"Image/UI/loginscene/HelpButton/BT_MOUSE_OVER.png",
		"Image/UI/loginscene/HelpButton/BT_SELECT.png", LOGIN_BTN_HELP);
	m_vecShownBtn.push_back(pBtn_Help);
	m_vecEventBtn.push_back(pBtn_Help);
	pBtn_Help->SetHidden(false);

	// 종료버튼
	cUIButton* pBtn_Exit = new cUIButton;
	pBtn_Exit->Setup(D3DXVECTOR3(550, 480, 0), UI_BUTTON);
	pBtn_Exit->Setup_Button("Image/UI/loginscene/ExitButton/BT_STAND.png",
		"Image/UI/loginscene/ExitButton/BT_MOUSE_OVER.png",
		"Image/UI/loginscene/ExitButton/BT_SELECT.png", LOGIN_BTN_EXIT);
	m_vecShownBtn.push_back(pBtn_Exit);
	m_vecEventBtn.push_back(pBtn_Exit);
	pBtn_Exit->SetHidden(false);
}

void cUIManager::Setup_SelectScene()
{

}

void cUIManager::Setup()
{
	m_pMiniMap = NULL;
}

void cUIManager::Release()
{
	for each(auto p in m_vecImage)
	{
		p->Destroy();
	}
	m_vecImage.clear();
	for each(auto p in m_vecText)
	{
		p->Destroy();
	}
	m_vecText.clear();
	for each(auto p in m_vecShownBtn)
	{
		p->Destroy();
	}	
	m_vecShownBtn.clear();
	for each(auto p in m_vecTab)
	{
		p->Destroy();
	}
	m_vecTab.clear();
	
	SAFE_DELETE(m_pMiniMap);
}

void cUIManager::Update(float deltaTime)
{
	PressKey();

	if(m_pMiniMap) m_pMiniMap->Update(deltaTime);

	for (int i = 0; i < m_vecTab.size(); i++)
	{
		m_vecTab[i]->Update(deltaTime);
	}

	for (int i = 0; i < m_vecShownBtn.size(); i++)
	{
		m_vecShownBtn[i]->Update(deltaTime);
	}
}

void cUIManager::Render(LPD3DXSPRITE pSprite)
{
	if (m_pMiniMap) m_pMiniMap->Render(pSprite);

	for (int i = 0; i < m_vecTab.size(); i++)
	{
		m_vecTab[i]->Render(pSprite);
	}

	for (int i = 0; i < m_vecShownBtn.size(); i++)
	{
		m_vecShownBtn[i]->Render(pSprite);
	}
}

// 씬 변경에 따른 UI 전체 변경시키는 함수
void cUIManager::Change(int sceneID)
{
	Release();

	switch (sceneID)
	{
	case SCENE_TITLE:
		Setup_TitleScene();
		break;
	case SCENE_TOWN:
		Setup_TownScene();
		break;
	case SCENE_LOGIN:
		Setup_LoginScene();
		break;
	}
}

void cUIManager::PressKey()
{
	if (INPUT->IsKeyDown(VK_CONTROL) && m_pMiniMap) m_pMiniMap->SetHiddenAll(!(m_pMiniMap->GetHidden()));

	if (INPUT->IsKeyDown(VK_F3)) m_vecTab[0]->SetHiddenAll(!(m_vecTab[0]->GetHidden()));
}

void cUIManager::SetEvent(int order)
{
	switch (order)
	{
	case 0:
		m_vecTab[0]->SetHidden(false);
		break;
	}

}

void cUIManager::GetEvent(OUT int& minimapIndex, OUT int& buttonIndex, OUT int& eventID, OUT int& itemID)
{
	// 미니맵 우클릭 시 노드의 인덱스 반환해주는 부분
	if(m_pMiniMap) minimapIndex = m_pMiniMap->GetIndex();

	// 버튼 중 클릭된 녀석의 인덱스 반환해주는 부분
	buttonIndex = -1;
	for (int i = 0; i < m_vecEventBtn.size(); i++)
	{
		if (m_vecEventBtn[i]->GetCurrentState() == UI_CLICKED)
		{
			buttonIndex = m_vecEventBtn[i]->GetEventID();
			break;
		}		
	}

	// 탭 중 클릭된 놈의 아이템 아이디를 반환하는 부분
	eventID = -1;
	itemID = -1;
	for (int i = 0; i < m_vecTab.size(); i++)
	{
		m_vecTab[i]->GetClickedItemID(eventID, itemID);
	}
}