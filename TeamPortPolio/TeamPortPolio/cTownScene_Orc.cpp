#include "stdafx.h"
#include "cTownScene_Orc.h"
#include "cPlayer.h"


cTownScene_Orc::cTownScene_Orc()
{
	SOUND->LoadFile("Town_Orc_BGM", "Sound/BGM/TownScene_Orc/Orgrimmar.mp3", true);
}


cTownScene_Orc::~cTownScene_Orc()
{
}

void cTownScene_Orc::OnEnter()
{
	D3DXCreateSprite(D3DDevice, &m_pSprite);
	MAP->Init(SCENE_TOWN_ORC);
	UI->Change(SCENE_TOWN_ORC);
	ConnectSpere();
	m_stWeather = MAP->GetWeather();
	EFFECT->Init(m_stWeather);

	Setup_DirLight();

	
	OBJECT->GetPlayer()->GetCharacterEntity()->SetPos(D3DXVECTOR3(5.5f, 0, -5.6f));
	OBJECT->GetPlayer()->SetRotY(MATH->GetRotY(D3DXVECTOR3(-0.5f, 0, -0.87f)));
	SOUND->Play("Town_Orc_BGM", 1.0f);
}

void cTownScene_Orc::OnUpdate()
{
	MAP->Update();
	OBJECT->Update(TIME->DeltaTime());
	EFFECT->Update();
	UI->Update(TIME->DeltaTime());

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
		cout << "병종 : " << trooptype << endl;
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

void cTownScene_Orc::OnExit()
{
	SAFE_RELEASE(m_pSprite);
	MAP->Destroy();
	OBJECT->Release();
	EFFECT->Release();
	UI->Release();
	SOUND->Stop("Town_Orc_BGM");
}

void cTownScene_Orc::OnRender()
{
	EFFECT->Render_Begin();
	MAP->Render();
	EFFECT->Render_End();
	OBJECT->Render();

	UI->Render(m_pSprite);
}

void cTownScene_Orc::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void cTownScene_Orc::Setup_DirLight()
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

void cTownScene_Orc::ConnectSpere()
{
	//	무기0
	// 방어구1
	// 전장가는애3
	// 징집관4
	m_vecST_Sphere = NPC->GetSphere();
}