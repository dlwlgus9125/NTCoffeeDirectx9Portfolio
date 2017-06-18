#pragma once

#include "Singleton.h"
#include "cUIImage.h"
#include "cUIText.h"
#include "cUIMiniMap.h"
#include "cUIButton.h"
#include "cUITab.h"
#include "cUISlot.h"
#include "cUIMsgBox.h"

#define UI cUIManager::Instance()

class cUIManager : public Singleton<cUIManager>
{
	vector<cUIButton*>			m_vecShownBtn;
	vector<cUIButton*>			m_vecEventBtn;
	vector<cUITab*>				m_vecTab;
	vector<cUIMsgBox*>			m_vecMsg;
	cUIMiniMap*					m_pMiniMap;

	void Setup_TitleScene();
	void Setup_TownScene();
	void Setup_LoginScene();
	void Setup_SelectScene();

public:
	void Setup();
	void Release();
	void Update(float deltaTime);
	void Render(LPD3DXSPRITE pSprite);
	void Change(int sceneID);
	void PressKey();
	void SetEvent(int uiID, int order);
	void GetEvent(OUT int& minimapIndex, OUT int& buttonIndex, OUT int& eventID, OUT int& itemID);
	void Setup_Inventory();


};

