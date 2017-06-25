#include "stdafx.h"
#include "cUIManager.h"

void cUIManager::Setup_TownScene()
{
	// >> 인벤토리 셋팅 : 상점 구매용
	cUITab* pTab_Inven = new cUITab();
	pTab_Inven->Setup(D3DXVECTOR3(WND_WIDTH - 300, 0, 0), UI_TAB);
	pTab_Inven->Setup_Tap("image/ui/townscene/tab_shop_inventory/idle.png", "image/ui/townscene/tab_shop_inventory/selected.png", "image/ui/townscene/tab_shop_inventory/body.png", D3DXVECTOR3(0, 0, 0));
	pTab_Inven->AddTitle("인벤토리", D3DXVECTOR3(25, 475, 0));
	/// 인벤토리 슬롯
	pTab_Inven->Setup_Slot(D3DXVECTOR3(22, 90, 0), 1, 7, D3DXVECTOR3(0, 0, 0), ST_SIZEN(190, 55),
		D3DXVECTOR3(0, 0, 0), ST_SIZEN(50, 50), D3DXVECTOR3(55, 0, 0), ST_SIZEN(140, 50), FONT_SHOP);
	vector<int> vecInven = OBJECT->GetInventory();
	for (int i = 0; i < vecInven.size(); i++)
	{
		ST_ITEM* item = ITEMDB->GetItem(vecInven[i]);
		pTab_Inven->AddSlotData(I_M_INVENTORY, item->eSmallID, item->name, item->szImagePath, item->info, item->cost);
	}
	pTab_Inven->SetDef();
	/// 인벤토리 종료버튼
	pTab_Inven->Setup_exitbtn(D3DXVECTOR3(244, 17, 0),
		"image/ui/townscene/tab_shop_inventory/btn_idle.png", "image/ui/townscene/tab_shop_inventory/btn_mouseover.png", "image/ui/townscene/tab_shop_inventory/btn_select.png");
	pTab_Inven->SetEventID(TOWN_TAB_INVENTORY);
	m_vecTab.push_back(pTab_Inven);
	// << 

	// >> 상점 1 탭 무기상인
	cUITab* pTab_Weapon = new cUITab();
	pTab_Weapon->Setup(D3DXVECTOR3(0, 0, 0), UI_TAB);
	pTab_Weapon->Setup_Tap("image/ui/townscene/tab_shop_atk/idle.png", "image/ui/townscene/tab_shop_atk/selected.png", "image/ui/townscene/tab_shop_atk/body.png", D3DXVECTOR3(0, 0, 0));
	pTab_Weapon->AddTitle("검", D3DXVECTOR3(25, 475, 0));
	pTab_Weapon->AddTitle("도끼", D3DXVECTOR3(150, 475, 0));
	pTab_Weapon->AddTitle("활", D3DXVECTOR3(275, 475, 0));
	/// 상점 1 슬롯 테스트용
	pTab_Weapon->Setup_Slot(D3DXVECTOR3(22, 90, 0), 2, 14, D3DXVECTOR3(0, 0, 0), ST_SIZEN(190, 55),
		D3DXVECTOR3(0, 0, 0), ST_SIZEN(50, 50), D3DXVECTOR3(55, 0, 0), ST_SIZEN(140, 50), FONT_SHOP);
	for (int i = I_S_SWORD_SHORT_NOR; i <= I_S_SWORD_MITHRIL_GLZ; i++)
	{
		ST_ITEM* newItem = ITEMDB->GetItem(i);
		pTab_Weapon->AddSlotData(I_M_SWORD, newItem->eSmallID, newItem->name, newItem->szImagePath, newItem->info, newItem->cost);
	}
	for (int i = I_S_AXE_STONE; i <= I_S_AXE_HONORABLE; i++)
	{
		ST_ITEM* newItem = ITEMDB->GetItem(i);
		pTab_Weapon->AddSlotData(I_M_AXE, newItem->eSmallID, newItem->name, newItem->szImagePath, newItem->info, newItem->cost);
	}
	for (int i = I_S_BOW_WOODEN_NOR; i <= I_S_BOW_ELF_GLZ; i++)
	{
		ST_ITEM* newItem = ITEMDB->GetItem(i);
		pTab_Weapon->AddSlotData(I_M_BOW, newItem->eSmallID, newItem->name, newItem->szImagePath, newItem->info, newItem->cost);
	}
	pTab_Weapon->SetDef();
	/// 상점 1 종료버튼
	pTab_Weapon->Setup_exitbtn(D3DXVECTOR3(382, 17, 0), 
		"image/ui/townscene/tab_shop_atk/btn_idle.png", "image/ui/townscene/tab_shop_atk/btn_mouseover.png", "image/ui/townscene/tab_shop_atk/btn_select.png");
	pTab_Weapon->SetEventID(TOWN_TAB_SHOP_ATT);
	m_vecTab.push_back(pTab_Weapon);
	// <<

	// >> 상점 2 탭 방어구 상인
	cUITab* pTab_Armor = new cUITab();
	pTab_Armor->Setup(D3DXVECTOR3(0, 0, 0), UI_TAB);
	pTab_Armor->Setup_Tap("image/ui/townscene/tab_shop_def/idle.png", "image/ui/townscene/tab_shop_def/selected.png", "image/ui/townscene/tab_shop_def/body.png", D3DXVECTOR3(0, 0, 0));
	pTab_Armor->AddTitle("갑옷", D3DXVECTOR3(25, 475, 0));
	pTab_Armor->AddTitle("방패", D3DXVECTOR3(150, 475, 0));
	/// 상점 2 슬롯 테스트용
	pTab_Armor->Setup_Slot(D3DXVECTOR3(22, 90, 0), 2, 14, D3DXVECTOR3(0, 0, 0), ST_SIZEN(190, 55),
		D3DXVECTOR3(0, 0, 0), ST_SIZEN(50, 50), D3DXVECTOR3(55, 0, 0), ST_SIZEN(140, 50), FONT_SHOP);
	for (int i = I_S_ARMOR_OLD; i <= I_S_ARMOR_GENERAL_GLZ; i++)
	{
		ST_ITEM* newItem = ITEMDB->GetItem(i);
		pTab_Armor->AddSlotData(I_M_ARMOR, newItem->eSmallID, newItem->name, newItem->szImagePath, newItem->info, newItem->cost), newItem->cost;
	}
	for (int i = I_S_SHIELD_WOODEN_NOR; i <= I_S_SHIELD_HONORABLE; i++)
	{
		ST_ITEM* newItem = ITEMDB->GetItem(i);
		pTab_Armor->AddSlotData(I_M_SHIELD, newItem->eSmallID, newItem->name, newItem->szImagePath, newItem->info, newItem->cost);
	}
	pTab_Armor->SetDef();
	/// 상점 2 종료버튼
	pTab_Armor->Setup_exitbtn(D3DXVECTOR3(382, 17, 0),
		"image/ui/townscene/tab_shop_def/btn_idle.png", "image/ui/townscene/tab_shop_def/btn_mouseover.png", "image/ui/townscene/tab_shop_def/btn_select.png");
	pTab_Armor->SetEventID(TOWN_TAB_SHOP_DEF);
	m_vecTab.push_back(pTab_Armor);
	// <<

	// >> 인벤토리 셋팅 : 아이템 착용용
	cUITab* pTab_Inven_Equip = new cUITab();
	pTab_Inven_Equip->Setup(D3DXVECTOR3(WND_WIDTH - 285, 0, 0), UI_TAB);
	pTab_Inven_Equip->Setup_Tap("image/ui/townscene/tab_shop_inventory/idle.png", "image/ui/townscene/tab_shop_inventory/selected.png", "image/ui/townscene/tab_shop_inventory/body.png", D3DXVECTOR3(0, 0, 0));
	pTab_Inven_Equip->AddTitle("인벤토리", D3DXVECTOR3(25, 475, 0));
	/// 인벤토리 슬롯
	pTab_Inven_Equip->Setup_Slot(D3DXVECTOR3(22, 90, 0), 1, 7, D3DXVECTOR3(0, 0, 0), ST_SIZEN(190, 55),
		D3DXVECTOR3(0, 0, 0), ST_SIZEN(50, 50), D3DXVECTOR3(55, 0, 0), ST_SIZEN(140, 50), FONT_SHOP);
	vector<int> vecInven_Equip = OBJECT->GetInventory();
	for (int i = 0; i < vecInven_Equip.size(); i++)
	{
		ST_ITEM* item = ITEMDB->GetItem(vecInven_Equip[i]);
		pTab_Inven_Equip->AddSlotData(I_M_INVENTORY, item->eSmallID, item->name, item->szImagePath, item->info, item->cost);
	}
	pTab_Inven_Equip->SetDef();
	/// 인벤토리 종료버튼
	pTab_Inven_Equip->Setup_exitbtn(D3DXVECTOR3(244, 17, 0),
		"image/ui/townscene/tab_shop_inventory/btn_idle.png", "image/ui/townscene/tab_shop_inventory/btn_mouseover.png", "image/ui/townscene/tab_shop_inventory/btn_select.png");
	pTab_Inven_Equip->SetEventID(TOWN_TAB_INVENTORY_EQUIP);
	m_vecTab.push_back(pTab_Inven_Equip);
	// << 

	// >> 징집관
	cUITab* pTab_Recruit = new cUITab();
	pTab_Recruit->Setup(D3DXVECTOR3(0, 0, 0), UI_TAB);
	pTab_Recruit->Setup_Tap("image/ui/townscene/tab_recruit/idle.png", "image/ui/townscene/tab_recruit/selected.png", "image/ui/townscene/tab_recruit/body.png", D3DXVECTOR3(0, 0, 0));
	pTab_Recruit->AddTitle("병과 목록", D3DXVECTOR3(25, 475, 0));
	/// 징집관 슬롯 테스트용
	pTab_Recruit->Setup_Slot(D3DXVECTOR3(22, 90, 0), 1, 5, D3DXVECTOR3(0, 0, 0), ST_SIZEN(190, 55),
		D3DXVECTOR3(0, 0, 0), ST_SIZEN(50, 50), D3DXVECTOR3(55, 0, 0), ST_SIZEN(140, 50), FONT_SHOP);

	///휴먼일 경우
	if (OBJECT->GetPlayerID() == C_C_HUMAN_MALE)
	{
		for (int i = C_C_HUMAN_MELEE; i <= C_C_HUMAN_CAVALRY; i++)
		{
			if (i == C_C_HUMAN_MELEE)
				pTab_Recruit->AddSlotData(C_C_HUMAN_MALE, i, "인간 보병", "", "칼과 방패로 기본적인 병과", 2000);
			if (i == C_C_HUMAN_BOWMAN)
				pTab_Recruit->AddSlotData(C_C_HUMAN_MALE, i, "인간 궁병", "", "원거리 공격을 이용한 전술적인 병과", 2000);
			if (i == C_C_HUMAN_CAVALRY)
				pTab_Recruit->AddSlotData(C_C_HUMAN_MALE, i, "인간 기병", "", "높은 공격력으로 순간적으로 강한 병과", 3000);
		}
	}
	/// 오크일 경우
	else if (OBJECT->GetPlayerID() == C_C_ORC_MALE)
	{
		for (int i = C_C_ORC_MELEE; i <= C_C_ORC_CAVALRY; i++)
		{
			if (i == C_C_ORC_MELEE)
				pTab_Recruit->AddSlotData(C_C_ORC_MALE, i, "오크 보병", "", "자신의 어깨만을 믿는 힘꾼", 2000);
			if (i == C_C_ORC_BOWMAN)
				pTab_Recruit->AddSlotData(C_C_ORC_MALE, i, "오크 궁병", "", "숨어서 적의 매복을 잘하는 힘꾼", 2000);
			if (i == C_C_ORC_CAVALRY)
				pTab_Recruit->AddSlotData(C_C_ORC_MALE, i, "그론", "", "자신의 체중을 무기로 쓸 줄 아는 힘꾼", 3000);
		}
	}

	pTab_Recruit->SetDef();
	/// 징집관 종료버튼
	pTab_Recruit->Setup_exitbtn(D3DXVECTOR3(382, 17, 0),
		"image/ui/townscene/tab_recruit/btn_idle.png", "image/ui/townscene/tab_recruit/btn_mouseover.png", "image/ui/townscene/tab_recruit/btn_select.png");
	pTab_Recruit->SetEventID(TOWN_TAB_RECRUIT);
	m_vecTab.push_back(pTab_Recruit);;
	// <<


	// >> 병사 정보
	m_pTab_TroopInfo = new cUITab();
	m_pTab_TroopInfo->Setup(D3DXVECTOR3(960,  0, 0), UI_TAB);
	m_pTab_TroopInfo->Setup_Tap("image/ui/townscene/troopinfo/troopinfo.png", "image/ui/townscene/troopinfo/troopinfo.png", "image/ui/townscene/troopinfo/troopinfo.png", D3DXVECTOR3(0, 0, 0));
	m_pTab_TroopInfo->AddTitle("병사 목록", D3DXVECTOR3(0, 0, 0));
	/// 병사 정보
	m_pTab_TroopInfo->Setup_Slot(D3DXVECTOR3(22, 6, 0), 3, 3, D3DXVECTOR3(0, 0, 0), ST_SIZEN(97, 68),
		D3DXVECTOR3(0, 0, 0), ST_SIZEN(68, 68), D3DXVECTOR3(48, 38, 0), ST_SIZEN(25, 25), FONT_SHOP, false);
	m_pTab_TroopInfo->AddSlotData(0,0, "0", "image/dump.png", "", 0);
	m_pTab_TroopInfo->AddSlotData(0,1, "0", "image/dump.png", "", 0);
	m_pTab_TroopInfo->AddSlotData(0,2, "0", "image/dump.png", "", 0);
	m_pTab_TroopInfo->SetDef();
	m_pTab_TroopInfo->SetHidden(false);
	m_pTab_TroopInfo->SetShownData(0, 0);
	m_pTab_TroopInfo->SetEventID(TOWN_TAB_TROOPINFO);
	// <<

	// >> 장비창
	m_pInven = new cUIInventory;
	m_pInven->Setup(D3DXVECTOR3(0, 0, 0), UI_INVENTORY);
	m_pInven->Setup_Tap("image/ui/townscene/inventory/body.png", D3DXVECTOR3(0, 0, 0));
	m_pInven->Setup_Slot(D3DXVECTOR3(236, 258, 0), ST_SIZEN(55, 55), D3DXVECTOR3(0,0,0), ST_SIZEN(50, 50));
	m_pInven->Setup_Slot(D3DXVECTOR3(38, 258, 0), ST_SIZEN(55, 55), D3DXVECTOR3(0, 0, 0), ST_SIZEN(50, 50));
	m_pInven->Setup_Slot(D3DXVECTOR3(137, 153, 0), ST_SIZEN(55, 55), D3DXVECTOR3(0, 0, 0), ST_SIZEN(50, 50));
	m_pInven->Setup_exitbtn(D3DXVECTOR3(205, 467, 0),
		"image/ui/townscene/inventory/btn_idle.png", "image/ui/townscene/inventory/btn_mouseover.png", "image/ui/townscene/inventory/btn_select.png");
	m_pInven->SetEventID(TOWN_INVENTORY);
	// <<

	// 미니맵
	m_pMiniMap = new cUIMiniMap;
	m_pMiniMap->Setup(D3DXVECTOR3(WND_WIDTH * 0.25f, WND_HEIGHT * 0.10f, 0), UI_MINIMAP);
	if(OBJECT->GetPlayerID() == C_C_HUMAN_MALE) m_pMiniMap->Setup_Image("image/UI/townscene/minimap/minimap_human.png", 150);
	else if (OBJECT->GetPlayerID() == C_C_ORC_MALE)  m_pMiniMap->Setup_Image("image/UI/townscene/minimap/minimap_orc.png", 150);
	m_pMiniMap->Setup_exitbtn(D3DXVECTOR3(674, 0, 0),
		"image/ui/townscene/minimap/btn_idle.png", "image/ui/townscene/minimap/btn_mouseover.png", "image/ui/townscene/minimap/btn_select.png");
	m_pMiniMap->SetEventID(TOWN_MINIMAP);

	// 미니맵 오크전장 버튼
	cUIButton* pBtn_Battle_Orc = new cUIButton;
	pBtn_Battle_Orc->Setup(D3DXVECTOR3(205, 55, 0), UI_BUTTON);
	pBtn_Battle_Orc->Setup_Button("Image/UI/townscene/minimap/idle.png",
		"Image/UI/townscene/minimap/mouseover.png",
		"Image/UI/townscene/minimap/selected.png", TOWN_BTN_BATTLE_ORC);
	m_vecEventBtn.push_back(pBtn_Battle_Orc);
	m_pMiniMap->AddChild(pBtn_Battle_Orc);

	// 미니맵 휴먼전장 버튼
	cUIButton* pBtn_Battle_Human = new cUIButton;
	pBtn_Battle_Human->Setup(D3DXVECTOR3(370, 215, 0), UI_BUTTON);
	pBtn_Battle_Human->Setup_Button("Image/UI/townscene/minimap/idle.png",
		"Image/UI/townscene/minimap/mouseover.png",
		"Image/UI/townscene/minimap/selected.png", TOWN_BTN_BATTLE_HUMAN);
	m_vecEventBtn.push_back(pBtn_Battle_Human);
	m_pMiniMap->AddChild(pBtn_Battle_Human);

	// >> 체력 상태 표시 막대
	m_pStatus = new cUIProgressBar;
	m_pStatus->Setup(D3DXVECTOR3(0, 0, 0.0f), UI_PROGRESSBAR);
	if (OBJECT->GetPlayerID() == C_C_HUMAN_MALE) m_pStatus->Setup_Progress("Image/UI/townscene/bar_status/status_human.png", "", D3DXVECTOR3(30, 20, 0));
	else if (OBJECT->GetPlayerID() == C_C_ORC_MALE) m_pStatus->Setup_Progress("Image/UI/townscene/bar_status/status_orc.png", "", D3DXVECTOR3(30, 20, 0));
	m_pStatus->AddProgressBar("Image/UI/townscene/bar_status/life.png", D3DXVECTOR3(148, 33, 0));
	m_pStatus->AddProgressBar("Image/UI/townscene/bar_status/mana.png", D3DXVECTOR3(148, 61, 0));
	m_pStatus->AddProgressBar("Image/UI/townscene/bar_status/exp.png", D3DXVECTOR3(153, 76, 0));
	m_pStatus->SetScaleOutline(1.0f);
	m_pStatus->SetHidden(false);
	// << 

	// >> 병종 상태 창
	m_pTrooptype = new cUIMiniMap();
	m_pTrooptype->Setup(D3DXVECTOR3(WND_WIDTH * 0.2f, WND_HEIGHT * 0.05f, 0), UI_MINIMAP);
	m_pTrooptype->Setup_Image("image/UI/townscene/trooptype/bg.png", 150);
	m_pTrooptype->Setup_exitbtn(D3DXVECTOR3(740, 0, 0),
		"image/ui/townscene/trooptype/btn_idle.png", "image/ui/townscene/trooptype/btn_mouseover.png", "image/ui/townscene/trooptype/btn_select.png");
	m_pTrooptype->SetEventID(TOWN_MINIMAP_TROOPTYPE);

	/// 병종 선택 버튼 : 밀리
	cUIButton* pBtn_Battle_Melee = new cUIButton;
	pBtn_Battle_Melee->Setup(D3DXVECTOR3(52, 93, 0), UI_BUTTON);
	pBtn_Battle_Melee->Setup_Button("Image/UI/townscene/trooptype/btn_melee_idle.png",
		"Image/UI/townscene/trooptype/btn_melee_mouseover.png",
		"Image/UI/townscene/trooptype/btn_melee_selected.png", TOWN_BTN_MELEE);
	m_vecEventBtn.push_back(pBtn_Battle_Melee);
	m_pTrooptype->AddChild(pBtn_Battle_Melee);
	
	/// 병종 선택 버튼 : 보우
	cUIButton* pBtn_Battle_Bow = new cUIButton;
	pBtn_Battle_Bow->Setup(D3DXVECTOR3(280, 93, 0), UI_BUTTON);
	pBtn_Battle_Bow->Setup_Button("Image/UI/townscene/trooptype/btn_bow_idle.png",
		"Image/UI/townscene/trooptype/btn_bow_mouseover.png",
		"Image/UI/townscene/trooptype/btn_bow_selected.png", TOWN_BTN_BOW);
	m_vecEventBtn.push_back(pBtn_Battle_Bow);
	m_pTrooptype->AddChild(pBtn_Battle_Bow);
	
	/// 병종 선택 버튼 : 카발리
	cUIButton* pBtn_Battle_Cavalry = new cUIButton;
	pBtn_Battle_Cavalry->Setup(D3DXVECTOR3(508, 93, 0), UI_BUTTON);
	pBtn_Battle_Cavalry->Setup_Button("Image/UI/townscene/trooptype/btn_Cavalry_idle.png",
		"Image/UI/townscene/trooptype/btn_Cavalry_mouseover.png",
		"Image/UI/townscene/trooptype/btn_Cavalry_selected.png", TOWN_BTN_CAVALRY);
	m_vecEventBtn.push_back(pBtn_Battle_Cavalry);
	m_pTrooptype->AddChild(pBtn_Battle_Cavalry);

	// <<
	m_pAim = new cUIImage();
	m_pAim->Setup(D3DXVECTOR3(WND_WIDTH * 0.5f-35, WND_HEIGHT * 0.5f-37.5, 0), UI_IMAGE);
	m_pAim->Setup_Image("image/UI/aim/aim.png");
	m_pAim->SetHidden(false);

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
	// 각 종족 아이콘 선택시 선택 후 이미지가 셀렉트상태이미지만 출력해줘야함.
	// 오크
	cUIButton* pBtn_Orc = new cUIButton;
	pBtn_Orc->Setup(D3DXVECTOR3(650, 545, 0), UI_BUTTON);
	pBtn_Orc->Setup_Button("Image/UI/SelectScene/Icon/Horde.png",
		"Image/UI/SelectScene/Icon/Horde_Over.png",
		"Image/UI/SelectScene/Icon/Horde_Select.png", SELECT_BTN_ORC);
	m_vecShownBtn.push_back(pBtn_Orc);
	m_vecEventBtn.push_back(pBtn_Orc);
	pBtn_Orc->SetHidden(false);

	// 휴먼
	cUIButton* pBtn_Human = new cUIButton;
	pBtn_Human->Setup(D3DXVECTOR3(500, 545, 0), UI_BUTTON);
	pBtn_Human->Setup_Button("Image/UI/SelectScene/Icon/Alliance.png",
		"Image/UI/SelectScene/Icon/Alliance_Over.png",
		"Image/UI/SelectScene/Icon/Alliance_Select.png", SELECT_BTN_HUMAN);
	m_vecShownBtn.push_back(pBtn_Human);
	m_vecEventBtn.push_back(pBtn_Human);
	pBtn_Human->SetHidden(false);

	// 게임 시작
	cUIButton* pBtn_Start = new cUIButton;
	pBtn_Start->Setup(D3DXVECTOR3(950, 630, 0), UI_BUTTON);
	pBtn_Start->Setup_Button("Image/UI/SelectScene/Button/Character_BT/BT_STAND.png",
		"Image/UI/SelectScene/Button/Character_BT/BT_MOUSE_OVER.png",
		"Image/UI/SelectScene/Button/Character_BT/BT_SELECT.png", SELECT_BTN_CREATE);
	m_vecShownBtn.push_back(pBtn_Start);
	m_vecEventBtn.push_back(pBtn_Start);
	pBtn_Start->SetHidden(false);

	// 돌아가기
	cUIButton* pBtn_Back = new cUIButton;
	pBtn_Back->Setup(D3DXVECTOR3(1100, 630, 0), UI_BUTTON);
	pBtn_Back->Setup_Button("Image/UI/SelectScene/Button/SCENE_BACK/BT_STAND.png",
		"Image/UI/SelectScene/Button/SCENE_BACK/BT_MOUSE_OVER.png",
		"Image/UI/SelectScene/Button/SCENE_BACK/BT_SELECT.png", SELECT_BTN_BACK);
	m_vecShownBtn.push_back(pBtn_Back);
	m_vecEventBtn.push_back(pBtn_Back);
	pBtn_Back->SetHidden(false);

	// 오크 설명 창
	cUIMsgBox* pMsgBox_Human = new cUIMsgBox;
	pMsgBox_Human->Setup(D3DXVECTOR3(930, 50, 0), UI_MSGBOX);
	pMsgBox_Human->Setup_MsgBox("image/ui/selectscene/msgbox_orc/msgbox_human_bg.png", D3DXVECTOR3(50, 50, 0), ST_SIZEN(250, 500), SELECT_MSGBOX_ORC, FONT_SHOP);
	m_vecMsg.push_back(pMsgBox_Human);

	// 휴먼 설명 창
	cUIMsgBox* pMsgBox_Orc = new cUIMsgBox;
	pMsgBox_Orc->Setup(D3DXVECTOR3(930, 50, 0), UI_MSGBOX);
	pMsgBox_Orc->Setup_MsgBox("image/ui/selectscene/msgbox_orc/msgbox_orc_bg.png", D3DXVECTOR3(50, 50, 0), ST_SIZEN(250, 500), SELECT_MSGBOX_HUMAN, FONT_SHOP);
	m_vecMsg.push_back(pMsgBox_Orc);
}

void cUIManager::Setup_BattleScene_Orc()
{
	// >> 체력 상태 표시 막대
	m_pStatus = new cUIProgressBar;
	m_pStatus->Setup(D3DXVECTOR3(0, 0, 0.0f), UI_PROGRESSBAR);
	if (OBJECT->GetPlayerID() == C_C_HUMAN_MALE) m_pStatus->Setup_Progress("Image/UI/townscene/bar_status/status_human.png", "", D3DXVECTOR3(30, 20, 0));
	else if (OBJECT->GetPlayerID() == C_C_ORC_MALE) m_pStatus->Setup_Progress("Image/UI/townscene/bar_status/status_orc.png", "", D3DXVECTOR3(30, 20, 0));
	m_pStatus->AddProgressBar("Image/UI/townscene/bar_status/life.png", D3DXVECTOR3(148, 33, 0));
	m_pStatus->AddProgressBar("Image/UI/townscene/bar_status/mana.png", D3DXVECTOR3(148, 61, 0));
	m_pStatus->AddProgressBar("Image/UI/townscene/bar_status/exp.png", D3DXVECTOR3(153, 76, 0));
	m_pStatus->SetScaleOutline(1.0f);
	m_pStatus->SetHidden(false);
	// << 

	// 미니맵
	m_pMiniMap = new cUIMiniMap;
	m_pMiniMap->Setup(D3DXVECTOR3(415, 132, 0), UI_MINIMAP);
	m_pMiniMap->Setup_Image("image/UI/BattleScene_Orc/minimap/minimap.png", 150);
	m_pMiniMap->Setup_exitbtn(D3DXVECTOR3(575, -25, 0),
		"image/ui/BattleScene_Orc/minimap/btn_idle.png", "image/ui/BattleScene_Orc/minimap/btn_mouseover.png", "image/ui/BattleScene_Orc/minimap/btn_select.png");
	m_pMiniMap->Setup_BG(D3DXVECTOR3(265, 110, 0), "image/ui/BattleScene_Orc/minimap/img_bg.png");
	switch (OBJECT->GetPlayerID())
	{
	case C_C_ORC_MALE:
		m_pMiniMap->Setup_Location("image/ui/BattleScene_Orc/minimap/position.png", "image/ui/BattleScene_Orc/minimap/unit.png", "image/ui/BattleScene_Orc/minimap/enemy.png");
		break;
	case C_C_HUMAN_MALE:
		m_pMiniMap->Setup_Location("image/ui/BattleScene_Human/minimap/position.png", "image/ui/BattleScene_Human/minimap/unit.png", "image/ui/BattleScene_Human/minimap/enemy.png");
		break;
	}	
	m_pMiniMap->SetAlpha(200);

	// 미니맵버튼 1
	cUIButton* pBtn_rect = new cUIButton;
	pBtn_rect->Setup(D3DXVECTOR3(-95, 140, 0), UI_BUTTON);
	pBtn_rect->Setup_Button("Image/UI/BattleScene_Orc/minimap/formation_rect/idle.png",
		"Image/UI/BattleScene_Orc/minimap/formation_rect/mouseover.png",
		"Image/UI/BattleScene_Orc/minimap/formation_rect/selected.png", TITLE_BTN_FMT_RECT);
	m_vecEventBtn.push_back(pBtn_rect);
	m_pMiniMap->AddChild(pBtn_rect);

	// 미니맵버튼 2
	cUIButton* pBtn_Tri = new cUIButton;
	pBtn_Tri->Setup(D3DXVECTOR3(-95, 250, 0), UI_BUTTON);
	pBtn_Tri->Setup_Button("Image/UI/BattleScene_Orc/minimap/formation_tri/idle.png",
		"Image/UI/BattleScene_Orc/minimap/formation_tri/mouseover.png",
		"Image/UI/BattleScene_Orc/minimap/formation_tri/selected.png", TITLE_BTN_FMT_TRI);
	m_vecEventBtn.push_back(pBtn_Tri);
	m_pMiniMap->AddChild(pBtn_Tri);

	// 미니맵버튼 3
	cUIButton* pBtn_Atk = new cUIButton;
	pBtn_Atk->Setup(D3DXVECTOR3(495, 140, 0), UI_BUTTON);
	switch (OBJECT->GetCurrentLeaderType())
	{
	case LEADER_MELEE:
		pBtn_Atk->Setup_Button("Image/UI/BattleScene_Orc/minimap/state_att/idle_melee.png",
			"Image/UI/BattleScene_Orc/minimap/state_att/mouseover_melee.png",
			"Image/UI/BattleScene_Orc/minimap/state_att/selected_melee.png", TITLE_BTN_ATTSTATE);
		break;
	case LEADER_BOW:
		pBtn_Atk->Setup_Button("Image/UI/BattleScene_Orc/minimap/state_att/idle_bow.png",
			"Image/UI/BattleScene_Orc/minimap/state_att/mouseover_bow.png",
			"Image/UI/BattleScene_Orc/minimap/state_att/selected_bow.png", TITLE_BTN_ATTSTATE);
		break;
	case LEADER_CAVALRY:
		pBtn_Atk->Setup_Button("Image/UI/BattleScene_Orc/minimap/state_att/idle_cavalry.png",
			"Image/UI/BattleScene_Orc/minimap/state_att/mouseover_cavalry.png",
			"Image/UI/BattleScene_Orc/minimap/state_att/selected_cavalry.png", TITLE_BTN_ATTSTATE);
		break;
	}
	m_vecEventBtn.push_back(pBtn_Atk);
	m_pMiniMap->AddChild(pBtn_Atk);

	// 미니맵버튼 4
	cUIButton* pBtn_Def = new cUIButton;
	pBtn_Def->Setup(D3DXVECTOR3(495, 250, 0), UI_BUTTON);
	switch (OBJECT->GetCurrentLeaderType())
	{
	case LEADER_MELEE:
		pBtn_Def->Setup_Button("Image/UI/BattleScene_Orc/minimap/state_def/idle_melee.png",
			"Image/UI/BattleScene_Orc/minimap/state_def/mouseover_melee.png",
			"Image/UI/BattleScene_Orc/minimap/state_def/selected_melee.png", TITLE_BTN_DEFSTATE);
		break;
	case LEADER_BOW:
		pBtn_Def->Setup_Button("Image/UI/BattleScene_Orc/minimap/state_def/idle_bow.png",
			"Image/UI/BattleScene_Orc/minimap/state_def/mouseover_bow.png",
			"Image/UI/BattleScene_Orc/minimap/state_def/selected_bow.png", TITLE_BTN_DEFSTATE);
		break;
	case LEADER_CAVALRY:
		pBtn_Def->Setup_Button("Image/UI/BattleScene_Orc/minimap/state_def/idle_cavalry.png",
			"Image/UI/BattleScene_Orc/minimap/state_def/mouseover_cavalry.png",
			"Image/UI/BattleScene_Orc/minimap/state_def/selected_cavalry.png", TITLE_BTN_DEFSTATE);
		break;
	}
	m_vecEventBtn.push_back(pBtn_Def);
	m_pMiniMap->AddChild(pBtn_Def);

	// >> 활 쏠 때 쓰는 목표점
	m_pAim = new cUIImage();
	m_pAim->Setup(D3DXVECTOR3(WND_WIDTH * 0.5f-35, WND_HEIGHT * 0.5f-37.5, 0), UI_IMAGE);
	m_pAim->Setup_Image("image/UI/aim/aim.png");
	m_pAim->SetHidden(false);
	// <<
}

void cUIManager::Setup_BattleScene_Human()
{
	// >> 체력 상태 표시 막대
	m_pStatus = new cUIProgressBar;
	m_pStatus->Setup(D3DXVECTOR3(0, 0, 0.0f), UI_PROGRESSBAR);
	if (OBJECT->GetPlayerID() == C_C_HUMAN_MALE) m_pStatus->Setup_Progress("Image/UI/townscene/bar_status/status_human.png", "", D3DXVECTOR3(30, 20, 0));
	else if (OBJECT->GetPlayerID() == C_C_ORC_MALE) m_pStatus->Setup_Progress("Image/UI/townscene/bar_status/status_orc.png", "", D3DXVECTOR3(30, 20, 0));
	m_pStatus->AddProgressBar("Image/UI/townscene/bar_status/life.png", D3DXVECTOR3(148, 33, 0));
	m_pStatus->AddProgressBar("Image/UI/townscene/bar_status/mana.png", D3DXVECTOR3(148, 61, 0));
	m_pStatus->AddProgressBar("Image/UI/townscene/bar_status/exp.png", D3DXVECTOR3(153, 76, 0));
	m_pStatus->SetScaleOutline(1.0f);
	m_pStatus->SetHidden(false);

	// << 전장 미니맵 생성
	// 미니맵
	m_pMiniMap = new cUIMiniMap;
	m_pMiniMap->Setup(D3DXVECTOR3(415, 132, 0), UI_MINIMAP);
	m_pMiniMap->Setup_Image("image/UI/BattleScene_Human/minimap/minimap.png", 150);
	m_pMiniMap->Setup_exitbtn(D3DXVECTOR3(575, -25, 0),
		"image/ui/BattleScene_Human/minimap/btn_idle.png", "image/ui/BattleScene_Human/minimap/btn_mouseover.png", "image/ui/BattleScene_Human/minimap/btn_select.png");
	m_pMiniMap->Setup_BG(D3DXVECTOR3(265, 110, 0), "image/ui/BattleScene_Human/minimap/img_bg.png");
	switch (OBJECT->GetPlayerID())
	{
	case C_C_ORC_MALE:
		m_pMiniMap->Setup_Location("image/ui/BattleScene_Orc/minimap/position.png", "image/ui/BattleScene_Orc/minimap/unit.png", "image/ui/BattleScene_Orc/minimap/enemy.png");
		break;
	case C_C_HUMAN_MALE:
		m_pMiniMap->Setup_Location("image/ui/BattleScene_Human/minimap/position.png", "image/ui/BattleScene_Human/minimap/unit.png", "image/ui/BattleScene_Human/minimap/enemy.png");
		break;
	}
	m_pMiniMap->SetAlpha(200);

	// 미니맵버튼 1
	cUIButton* pBtn_rect = new cUIButton;
	pBtn_rect->Setup(D3DXVECTOR3(-95, 140, 0), UI_BUTTON);
	pBtn_rect->Setup_Button("Image/UI/BattleScene_Human/minimap/formation_rect/idle.png",
		"Image/UI/BattleScene_Human/minimap/formation_rect/mouseover.png",
		"Image/UI/BattleScene_Human/minimap/formation_rect/selected.png", TITLE_BTN_FMT_RECT);
	m_vecEventBtn.push_back(pBtn_rect);
	m_pMiniMap->AddChild(pBtn_rect);

	// 미니맵버튼 2
	cUIButton* pBtn_Tri = new cUIButton;
	pBtn_Tri->Setup(D3DXVECTOR3(-95, 250, 0), UI_BUTTON);
	pBtn_Tri->Setup_Button("Image/UI/BattleScene_Human/minimap/formation_tri/idle.png",
		"Image/UI/BattleScene_Human/minimap/formation_tri/mouseover.png",
		"Image/UI/BattleScene_Human/minimap/formation_tri/selected.png", TITLE_BTN_FMT_TRI);
	m_vecEventBtn.push_back(pBtn_Tri);
	m_pMiniMap->AddChild(pBtn_Tri);

	// 미니맵버튼 3
	cUIButton* pBtn_Atk = new cUIButton;
	pBtn_Atk->Setup(D3DXVECTOR3(495, 140, 0), UI_BUTTON);
	switch (OBJECT->GetCurrentLeaderType())
	{
	case LEADER_MELEE:
		pBtn_Atk->Setup_Button("Image/UI/BattleScene_Human/minimap/state_att/idle_melee.png",
			"Image/UI/BattleScene_Human/minimap/state_att/mouseover_melee.png",
			"Image/UI/BattleScene_Human/minimap/state_att/selected_melee.png", TITLE_BTN_ATTSTATE);
		break;
	case LEADER_BOW:
		pBtn_Atk->Setup_Button("Image/UI/BattleScene_Human/minimap/state_att/idle_bow.png",
			"Image/UI/BattleScene_Human/minimap/state_att/mouseover_bow.png",
			"Image/UI/BattleScene_Human/minimap/state_att/selected_bow.png", TITLE_BTN_ATTSTATE);
		break;
	case LEADER_CAVALRY:
		pBtn_Atk->Setup_Button("Image/UI/BattleScene_Human/minimap/state_att/idle_cavalry.png",
			"Image/UI/BattleScene_Human/minimap/state_att/mouseover_cavalry.png",
			"Image/UI/BattleScene_Human/minimap/state_att/selected_cavalry.png", TITLE_BTN_ATTSTATE);
		break;
	}
	m_vecEventBtn.push_back(pBtn_Atk);
	m_pMiniMap->AddChild(pBtn_Atk);

	// 미니맵버튼 4
	cUIButton* pBtn_Def = new cUIButton;
	pBtn_Def->Setup(D3DXVECTOR3(495, 250, 0), UI_BUTTON);
	switch (OBJECT->GetCurrentLeaderType())
	{
	case LEADER_MELEE:
		pBtn_Def->Setup_Button("Image/UI/BattleScene_Human/minimap/state_def/idle_melee.png",
			"Image/UI/BattleScene_Human/minimap/state_def/mouseover_melee.png",
			"Image/UI/BattleScene_Human/minimap/state_def/selected_melee.png", TITLE_BTN_DEFSTATE);
		break;
	case LEADER_BOW:
		pBtn_Def->Setup_Button("Image/UI/BattleScene_Human/minimap/state_def/idle_bow.png",
			"Image/UI/BattleScene_Human/minimap/state_def/mouseover_bow.png",
			"Image/UI/BattleScene_Human/minimap/state_def/selected_bow.png", TITLE_BTN_DEFSTATE);
		break;
	case LEADER_CAVALRY:
		pBtn_Def->Setup_Button("Image/UI/BattleScene_Human/minimap/state_def/idle_cavalry.png",
			"Image/UI/BattleScene_Human/minimap/state_def/mouseover_cavalry.png",
			"Image/UI/BattleScene_Human/minimap/state_def/selected_cavalry.png", TITLE_BTN_DEFSTATE);
		break;
	}
	m_vecEventBtn.push_back(pBtn_Def);
	m_pMiniMap->AddChild(pBtn_Def);

	// >> 활 쏠 때 쓰는 목표점
	m_pAim = new cUIImage();
	 m_pAim->Setup(D3DXVECTOR3(WND_WIDTH * 0.5f-35, WND_HEIGHT * 0.5f-37.5, 0), UI_IMAGE);
	m_pAim->Setup_Image("image/UI/aim/aim.png");
	m_pAim->SetHidden(false);
	// <<
}

void cUIManager::Setup()
{
	m_pMiniMap = NULL;
	m_pInven = NULL;
	m_pStatus = NULL;
	m_pTrooptype = NULL;
	m_pResultMessage = NULL;
	m_pAim = NULL;
	m_pTab_TroopInfo = NULL;
}

			

void cUIManager::Release()
{	
	m_vecShownBtn.clear();	//	m_vecEventBtn의 일부분이므로 비우기만.
	m_vecEventBtn.clear();	//	AddChild된 버튼은 각자 부모의 Destroy에서 지워주므로 비우기만,
							//  또한, 로그인씬, 셀렉씬에서의 버튼은 다른 함수를 통해 미리 삭제하므로 비우기만.

	for each(auto p in m_vecTab)
	{
		p->Destroy();
	}
	m_vecTab.clear();
	for each(auto p in m_vecMsg)
	{
		p->Destroy();
	}
	m_vecMsg.clear();
	
	if (m_pInven) m_pInven->Destroy();
	
	if (m_pMiniMap)m_pMiniMap->Destroy();
	
	if (m_pAim)m_pAim->Destroy();
	
	if (m_pStatus)m_pStatus->Destroy();
	
	if (m_pTrooptype)m_pTrooptype->Destroy();
	
	if (m_pResultMessage)m_pResultMessage->Destroy();

	if (m_pTab_TroopInfo) m_pTab_TroopInfo->Destroy();
}

void cUIManager::Update(float deltaTime)
{
	if (m_pResultMessage) m_pResultMessage->Update(deltaTime);

	if (m_pStatus) m_pStatus->ResetBarLength(0, OBJECT->GetPlayerHPRate());

	PressKey();
	Update_ConnectedUI();

	if (m_pTrooptype) m_pTrooptype->Update(deltaTime);

	if(m_pMiniMap) m_pMiniMap->Update(deltaTime);

	for (int i = 0; i < m_vecTab.size(); i++)
	{
		m_vecTab[i]->Update(deltaTime);
	}

	for (int i = 0; i < m_vecShownBtn.size(); i++)
	{
		m_vecShownBtn[i]->Update(deltaTime);
	}

	for (int i = 0; i < m_vecMsg.size(); i++)
	{
		m_vecMsg[i]->Update(deltaTime);
	}

	if (m_pInven) m_pInven->Update(deltaTime);

	if (m_pTab_TroopInfo) m_pTab_TroopInfo->Update(deltaTime);
}

void cUIManager::Render(LPD3DXSPRITE pSprite)
{
	if(m_pStatus) m_pStatus->Render(pSprite);

	if (m_pTab_TroopInfo) m_pTab_TroopInfo->Render(pSprite);

	for (int i = 0; i < m_vecTab.size(); i++)
	{
		m_vecTab[i]->Render(pSprite);
	}

	for (int i = 0; i < m_vecMsg.size(); i++)
	{
		m_vecMsg[i]->Render(pSprite);
	}

	if (m_pInven) m_pInven->Render(pSprite);

	if (m_pMiniMap) m_pMiniMap->Render(pSprite);

	if (m_pTrooptype) m_pTrooptype->Render(pSprite);

	for (int i = 0; i < m_vecShownBtn.size(); i++)
	{
		m_vecShownBtn[i]->Render(pSprite);
	}

	if (m_pResultMessage) m_pResultMessage->Render(pSprite);
}

// 씬 변경에 따른 UI 전체 변경시키는 함수
void cUIManager::Change(int sceneID)
{
	Setup();

	switch (sceneID)
	{
	case SCENE_LOGIN:
		Setup_LoginScene();
		break;
	case SCENE_SELECT:
		Setup_SelectScene();
		break;
	case SCENE_TOWN_HUMAN:
		Setup_TownScene();
		break;
	case SCENE_TOWN_ORC:
		Setup_TownScene();
		break;
	case SCENE_BATTLE_HUMAN:
		Setup_BattleScene_Human();
		break;
	case SCENE_BATTLE_ORC:
		Setup_BattleScene_Orc();
		break;
	}
}

void cUIManager::PressKey()
{
	// 전장에서 미니맵 띄우기
	if (INPUT->IsKeyDown(VK_TAB) && m_pMiniMap)
	{
		int sceneTag = SCENE->GetCurrentSceneTag();
		if (sceneTag < SCENE_BATTLE_HUMAN || sceneTag > SCENE_BATTLE_ORC) return;		// 전장 씬 아니면 미니맵 안켜지도록 예외처리
		m_pMiniMap->SetHiddenAll(!(m_pMiniMap->GetHidden()));
	}

	// 아이템창 띄우기
	if (INPUT->IsKeyDown(VK_I))
	{
		if (m_vecTab.size() < 4) return;	// 아이템창 구현 안되어있을 경우 예외처리
		if (!m_vecTab[0]->GetHidden()) return;	// 상점창 켜있으면 인벤토리 안뜨도록 예외처리

		bool hidden = !m_vecTab[3]->GetHidden();
		m_vecTab[3]->SetHidden(hidden);
		AddItem_Tab(TOWN_TAB_INVENTORY_EQUIP);
		m_vecTab[3]->SetDef();

		m_pInven->SetHiddenAll(hidden);
	}
}

void cUIManager::Update_ConnectedUI()
{
	// >> 상점에서 상점창을 끄거나 아이템창을 끄면 상점창과 아이템창을 모두 꺼버리는 부분
	if (m_vecTab.size() >= 3 && m_vecTab[1]->GetHidden() && m_vecTab[2]->GetHidden()) m_vecTab[0]->SetHiddenAll(true);
	if (m_vecTab.size() >= 3 && m_vecTab[0]->GetHidden())
	{
		m_vecTab[1]->SetHiddenAll(true);
		m_vecTab[2]->SetHiddenAll(true);
	}
	// << 

	// >> 인벤토리 끄면 아이템창 끄는 부분
	if (m_vecTab.size() >= 4 && m_vecTab[3]->GetHidden()) m_pInven->SetHiddenAll(true);
	if (m_vecTab.size() >= 4 && m_pInven->GetHidden()) m_vecTab[3]->SetHiddenAll(true);
	// << 
}

void cUIManager::SetEvent(int uiID, int order)
{
	// 0 : 내 아이템 구매판매창,
	// 1 : 무기상점 창
	// 2 : 방어구상점 창
	// 3 : 내 아이템 창
	// 4 : 징집관 창
	switch (uiID)
	{
	case TOWN_TAB_SHOP_ATT:
	{
		bool bOrder = order;
		m_vecTab[2]->SetHidden(!bOrder);
		m_vecTab[4]->SetHidden(!bOrder);
		m_vecTab[0]->SetHidden(bOrder);
		m_vecTab[0]->SetDef();
		m_vecTab[1]->SetHidden(bOrder);
		m_vecTab[1]->SetDef();
	}
		break;
	case TOWN_TAB_SHOP_DEF:
	{
		bool bOrder = order;
		m_vecTab[1]->SetHidden(!bOrder);
		m_vecTab[4]->SetHidden(!bOrder);
		m_vecTab[0]->SetHidden(bOrder);
		m_vecTab[0]->SetDef();
		m_vecTab[2]->SetHidden(bOrder);
		m_vecTab[2]->SetDef();
	}
		break;
	case TOWN_TAB_RECRUIT:
	{
		bool bOrder = order;
		m_vecTab[1]->SetHidden(!bOrder);
		m_vecTab[2]->SetHidden(!bOrder);
		m_vecTab[0]->SetHidden(!bOrder);
		m_vecTab[4]->SetHidden(bOrder);
		m_vecTab[4]->SetDef();
	}
	break;
	case TOWN_MINIMAP:
	{
		bool bOrder = order;
		if (m_pMiniMap) m_pMiniMap->SetHiddenAll(bOrder);
		for (int i = 0; i < m_vecTab.size(); i++)
		{
			m_vecTab[i]->SetHidden(!bOrder);
		}
	}
		break;
	case SELECT_MSGBOX_ORC:
		m_vecMsg[0]->SetHidden(order);
		break;
	case SELECT_MSGBOX_HUMAN:
		m_vecMsg[1]->SetHidden(order);
		break;
	case TOWN_MINIMAP_TROOPTYPE:
		if(m_pTrooptype) m_pTrooptype->SetHiddenAll(order);
		if (m_pMiniMap)
		{
			m_pMiniMap->Update(0);
			m_pMiniMap->SetHiddenAll(!order);
		}
		break;
	case TOWN_TAB_TROOPINFO:
	{
		int melee = order / 10000;
		int bow = (order - melee * 10000) / 100;
		int cavalry = (order - melee * 10000 - bow * 100);
		m_pTab_TroopInfo->UpdateTroopCount(melee, bow, cavalry);
	}
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
		if(m_vecTab[i]->GetClickedItemID(eventID, itemID)) break;
	}

	// 장비창에서 클릭된 놈의 아이템 아이디 반환하는 부분
	if(m_pInven && itemID == -1) m_pInven->GetClickedItemID(eventID, itemID);
}

void cUIManager::AddItem_Tab(int tabID)
{
	int index = -1;
	switch (tabID)
	{
	case TOWN_TAB_INVENTORY:
		index = 0;
		break;
	case TOWN_TAB_INVENTORY_EQUIP:
		index = 3;
		break;
	}

	// 해당 인벤토리가 없을 경우 예외처리
	if (index == -1) return;			

	// 탭_인벤토리 초기화
	m_vecTab[index]->ClearShownData();
	// 탭_인벤토리 슬롯 재삽입
	vector<int> vecInven = OBJECT->GetInventory();
	for (int i = 0; i < vecInven.size(); i++)
	{
		ST_ITEM* item = ITEMDB->GetItem(vecInven[i]);
		m_vecTab[index]->AddSlotData(I_M_INVENTORY, item->eSmallID, item->name, item->szImagePath, item->info, item->cost);
	}
	m_vecTab[index]->SetDef();
}

void cUIManager::ResetEquipment(vector<int> vecEquipment)
{
	m_pInven->ResetItems(vecEquipment);
}

void cUIManager::DrawAim(LPD3DXSPRITE pSprite)
{
	m_pAim->Update(0);
	m_pAim->Render(pSprite);
}

void cUIManager::CreateResultMessage(int resultID)
{
	m_pResultMessage = new cUIMiniMap;
	m_pResultMessage->Setup(D3DXVECTOR3(0,0, 0), UI_MINIMAP);
	
	if (resultID == BATTLE_MINIMAP_VICTORY)
		m_pResultMessage->Setup_Image("Image/UI/battlescene_human/resultmessage/victory.png", 150);
	else if (resultID == BATTLE_MINIMAP_DEFEAT)
		m_pResultMessage->Setup_Image("Image/UI/battlescene_human/resultmessage/defeat.png", 150);

	// 미니맵버튼 1
	cUIButton* pBnt_Exit = new cUIButton;
	pBnt_Exit->Setup(D3DXVECTOR3(500, 355, 0), UI_BUTTON);
	pBnt_Exit->Setup_Button("Image/UI/battlescene_human/resultmessage/btn_idle.png",
		"Image/UI/battlescene_human/resultmessage/btn_mouseover.png",
		"Image/UI/battlescene_human/resultmessage/btn_select.png", BATTLE_MINIMAP_RESULT);
	m_vecEventBtn.push_back(pBnt_Exit);
	m_pResultMessage->AddChild(pBnt_Exit);
	m_pResultMessage->SetHiddenAll(false);
}

void cUIManager::Update_MinimapPos(D3DXVECTOR2 pos, D3DXVECTOR2 pos_unit, D3DXVECTOR2 pos_enemy)
{
	if (!m_pMiniMap) return;

	D3DXVECTOR2 uv = MAP->GetPlayerPos_RateBased(pos.x, pos.y);
	D3DXVECTOR2 uv_unit = MAP->GetPlayerPos_RateBased(pos_unit.x, pos_unit.y);
	D3DXVECTOR2 uv_enemy = MAP->GetPlayerPos_RateBased(pos_enemy.x, pos_enemy.y);
	m_pMiniMap->Update_Location(uv, uv_unit, uv_enemy);
}

void cUIManager::DestroyEventButton()
{
	for each(auto p in m_vecEventBtn)
	{
		p->Destroy();
	}
}