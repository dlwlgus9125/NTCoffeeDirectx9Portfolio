#include "stdafx.h"
#include "cTownScene_Human.h"
#include "cPlayer.h"


cTownScene_Human::cTownScene_Human()
{
	SOUND->LoadFile("Town_Human_BGM", "Sound/BGM/TownScene_Human/Stormwind.mp3", true);
}


cTownScene_Human::~cTownScene_Human()
{
}

void cTownScene_Human::OnEnter()
{
	D3DXCreateSprite(D3DDevice, &m_pSprite);

	MAP->Init(SCENE_TOWN_HUMAN);

	UI->Change(SCENE_TOWN_HUMAN);
	ConnectSpere();
	m_stWeather = MAP->GetWeather();
	EFFECT->Init(m_stWeather);

	Setup_DirLight();

	//NPC SCENE 별로 세팅
	//NPC->Change(SCENE_TOWN_HUMAN);
	//NPC->Setup(MAP->GetVecNPC());
	OBJECT->GetPlayer()->GetCharacterEntity()->SetPos(D3DXVECTOR3(-6, 0, 0));
	OBJECT->GetPlayer()->SetRotY(MATH->GetRotY(D3DXVECTOR3(-1,0,-0.03)));
	//OBJECT->GetPlayer()->GetCharacterEntity()->SetForward(D3DXVECTOR3(0, 0, 1));

	SOUND->Play("LoginBGM", 1.0f);
}

void cTownScene_Human::OnUpdate()
{
	MAP->Update();
	UI->Update(TIME->DeltaTime());
	OBJECT->Update(TIME->DeltaTime());
	EFFECT->Update();

	int indexInMiniMap;
	int buttonIndex;
	int eventIDTap;
	int itemID;

	UI->GetEvent(indexInMiniMap, buttonIndex, eventIDTap, itemID);

	switch (buttonIndex)
	{
	case TOWN_BTN_BATTLE_ORC:
		SCENE->ChangeScene(SCENE_BATTLE_ORC);
		break;
	case TOWN_BTN_BATTLE_HUMAN:
		SCENE->ChangeScene(SCENE_BATTLE_HUMAN);
		break;
	}
	switch (eventIDTap)
	{
	case TOWN_TAB_INVENTORY:
		OBJECT->SellItem(itemID);
		UI->AddItem_Tab(TOWN_TAB_INVENTORY);
		break;
	case TOWN_TAB_SHOP_ATT:
		OBJECT->BuyItem(itemID);
		UI->AddItem_Tab(TOWN_TAB_INVENTORY);
		break;
	case TOWN_TAB_SHOP_DEF:
		OBJECT->BuyItem(itemID);
		UI->AddItem_Tab(TOWN_TAB_INVENTORY);
		break;
	case TOWN_TAB_INVENTORY_EQUIP:
		OBJECT->PutOnItem(itemID);
		UI->ResetEquipment(OBJECT->GetEquipment());
		break;
	case TOWN_INVENTORY:
		OBJECT->PutOffItem(itemID);
		UI->ResetEquipment(OBJECT->GetEquipment());
		break;
	case TOWN_TAB_RECRUIT:
		int trooptype = itemID;
		break;
	}
	if (INPUT->IsMouseDown(MOUSE_LEFT))
	{
		for (int i = 0; i < m_vecST_Sphere.size(); i++)
		{
			m_vecST_Sphere[i].isPicked = cRay::IsPicked(INPUT->GetMousePosVector2(), &m_vecST_Sphere[i]);
		}
	}

	if (m_vecST_Sphere[0].isPicked)
	{
		UI->SetEvent(TOWN_TAB_SHOP_ATT, false);
		m_vecST_Sphere[0].isPicked = false;;;
	}
	if (m_vecST_Sphere[1].isPicked)
	{
		UI->SetEvent(TOWN_TAB_SHOP_DEF, false);
		m_vecST_Sphere[1].isPicked = false;;;
	}
	if (m_vecST_Sphere[3].isPicked)
	{
		UI->SetEvent(TOWN_MINIMAP, false);
		m_vecST_Sphere[3].isPicked = false;;;
	}
	if (m_vecST_Sphere[4].isPicked)
	{
		UI->SetEvent(TOWN_TAB_RECRUIT, false);
		m_vecST_Sphere[4].isPicked = false;;;
	}
}

void cTownScene_Human::OnExit()
{
	SAFE_RELEASE(m_pSprite);
	MAP->Destroy();
	UI->Release();
	EFFECT->Release();
	SOUND->Stop("Town_Human_BGM");
	m_vecST_Sphere.clear();
}

void cTownScene_Human::OnRender()
{
	EFFECT->Render_Begin();
	MAP->Render();
	EFFECT->Render_End();
	OBJECT->Render();

	UI->Render(m_pSprite);
}

void cTownScene_Human::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void cTownScene_Human::Setup_DirLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);            // 주변에 영향을 받는 것들은 색을 띄게 만듬
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3   vDir(1.0f, 1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	SHADOW->SetLightDir(stLight.Direction);
	D3DDevice->SetLight(0, &stLight);
	D3DDevice->LightEnable(0, true);
}

void cTownScene_Human::ConnectSpere()
{
	//	무기0
	// 방어구1
	// 전장가는애3
	// 징집관4
	m_vecST_Sphere = NPC->GetSphere();
}