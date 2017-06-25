#pragma once

#include "Singleton.h"
#include "cUIImage.h"
#include "cUIText.h"
#include "cUIMiniMap.h"
#include "cUIButton.h"
#include "cUITab.h"
#include "cUISlot.h"
#include "cUIMsgBox.h"
#include "cUIInventory.h"
#include "cUIImage.h"
#include "cUIProgressBar.h"

#define UI cUIManager::Instance()

class cUIManager : public Singleton<cUIManager>
{
	vector<cUIButton*>			m_vecShownBtn;
	vector<cUIButton*>			m_vecEventBtn;
	vector<cUITab*>				m_vecTab;
	vector<cUIMsgBox*>			m_vecMsg;
	cUIInventory*				m_pInven;
	cUIMiniMap*					m_pMiniMap;
	cUIImage*					m_pAim;
	cUIProgressBar*				m_pStatus;
	cUIMiniMap*					m_pTrooptype;
	cUIMiniMap*					m_pResultMessage;
	cUITab*						m_pTab_TroopInfo;

	void Setup_TownScene();
	void Setup_LoginScene();
	void Setup_SelectScene();
	void Setup_BattleScene_Orc();
	void Setup_BattleScene_Human();

public:
	void Setup();
	void Release();
	void Update(float deltaTime);
	void Render(LPD3DXSPRITE pSprite);
	void Change(int sceneID);
	void PressKey();
	void Update_ConnectedUI();
	void SetEvent(int uiID, int order);
	void GetEvent(OUT int& minimapIndex, OUT int& buttonIndex, OUT int& eventID, OUT int& itemID);
	void AddItem_Tab(int tabID);
	void ResetEquipment(vector<int> vecEquipment);
	void CreateResultMessage(int resultID);

	void DrawAim(LPD3DXSPRITE pSprite);
	void Update_MinimapPos(D3DXVECTOR2 pos, D3DXVECTOR2 pos_unit, D3DXVECTOR2 pos_enemy);
	void DestroyEventButton();	//	로그인신, 셀렉신에서 사용하는 이벤트버튼 지우는 함수
};

