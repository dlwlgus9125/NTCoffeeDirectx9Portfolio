#include "stdafx.h"
#include "cTownScene_Orc.h"
#include "cPlayer.h"


cTownScene_Orc::cTownScene_Orc()
{
	SOUND->LoadFile("Town_Orc_BGM", "Sound/BGM/TownScene_Orc/Orgrimmar.mp3", true);
	SOUND->LoadFile("coin", "Sound/effect/coins_dropped_1.wav", false);
	SOUND->LoadFile("putonoff", "Sound/effect/putonoff.mp3", false);
	m_nNextSceneID = -1;
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
	EFFECT->OnEnter(m_stWeather);

	Setup_DirLight();

	
	OBJECT->GetPlayer()->GetCharacterEntity()->SetPos(D3DXVECTOR3(5.5f, 0, -5.6f));
	OBJECT->GetPlayer()->SetRotY(MATH->GetRotY(D3DXVECTOR3(-0.5f, 0, -0.87f)));
	OBJECT->GetPlayer()->SetSceneEnter();
	
	SOUND->Play("Town_Orc_BGM", 0.5f);
	OBJECT->AddCharacter(OBJECT->GetPlayer());
	OBJECT->AddObject(OBJECT->GetPlayer());
}

void cTownScene_Orc::OnUpdate()
{
	MAP->Update();
	OBJECT->Update(TIME->DeltaTime());
	EFFECT->OnUpdate();
	UI->Update(TIME->DeltaTime());

	int indexInMiniMap;
	int buttonIndex;
	int eventIDTap;
	int itemID;

	UI->GetEvent(indexInMiniMap, buttonIndex, eventIDTap, itemID);

	switch (buttonIndex)
	{
	case TOWN_BTN_BATTLE_ORC:
		m_nNextSceneID = SCENE_BATTLE_ORC;
		UI->SetEvent(TOWN_MINIMAP_TROOPTYPE, false);
		break;
	case TOWN_BTN_BATTLE_HUMAN:
		m_nNextSceneID = SCENE_BATTLE_HUMAN;
		UI->SetEvent(TOWN_MINIMAP_TROOPTYPE, false);
		break;
	case TOWN_BTN_MELEE:
		OBJECT->SetCurrentLeader(LEADER_MELEE);
		if (SOUND->FindChannel("OrcInitBattleScene") == NULL)SOUND->Play("OrcInitBattleScene");
		SCENE->ChangeScene(m_nNextSceneID);
		break;
	case TOWN_BTN_BOW:
		OBJECT->SetCurrentLeader(LEADER_BOW);
		if (SOUND->FindChannel("OrcInitBattleScene") == NULL)SOUND->Play("OrcInitBattleScene");
		SCENE->ChangeScene(m_nNextSceneID);
		break;
	case TOWN_BTN_CAVALRY:
		OBJECT->SetCurrentLeader(LEADER_CAVALRY);
		if (SOUND->FindChannel("OrcInitBattleScene") == NULL)SOUND->Play("OrcInitBattleScene");
		SCENE->ChangeScene(m_nNextSceneID);
		break;
	}
	switch (eventIDTap)
	{
	case TOWN_TAB_INVENTORY:
		OBJECT->SellItem(itemID);
		SOUND->Play("coin");
		UI->AddItem_Tab(TOWN_TAB_INVENTORY);
		break;
	case TOWN_TAB_SHOP_ATT:
		OBJECT->BuyItem(itemID);
		SOUND->Play("coin");
		UI->AddItem_Tab(TOWN_TAB_INVENTORY);
		break;
	case TOWN_TAB_SHOP_DEF:
		OBJECT->BuyItem(itemID);
		SOUND->Play("coin");
		UI->AddItem_Tab(TOWN_TAB_INVENTORY);
		break;
	case TOWN_TAB_INVENTORY_EQUIP:
		OBJECT->PutOnItem(itemID);
		SOUND->Play("putonoff", 3.0f);
		UI->ResetEquipment(OBJECT->GetEquipment());
		break;
	case TOWN_INVENTORY:
		OBJECT->PutOffItem(itemID);
		SOUND->Play("putonoff", 3.0f);
		UI->ResetEquipment(OBJECT->GetEquipment());
		break;
	case TOWN_TAB_RECRUIT:
		int trooptype = itemID;
		if (OBJECT->GetPlayer()->AddUnitInTown((C_C_ID)trooptype))
		{
			SOUND->Play("coin");
			int unitSize = OBJECT->GetPlayer()->GetAllUnitSize();
			UI->SetEvent(TOWN_TAB_TROOPINFO, unitSize);
			cout << "삼!" << endl;
		}
		else
		{
			cout << "못삼!" << endl;
		}
		cout << "병사수 : " << OBJECT->GetPlayer()->GetUnitLeader()->GetUnits().size() << endl;
		break;
	}
	if (INPUT->IsMouseUp(MOUSE_LEFT))
	{
		for (int i = 0; i < m_vecST_Sphere.size(); i++)
		{
			m_vecST_Sphere[i].isPicked = (cRay::IsPicked(INPUT->GetMousePosVector2(), &m_vecST_Sphere[i]) &&
				MATH->SqrDistance(OBJECT->GetPlayer()->GetCharacterEntity()->Pos(), m_vecST_Sphere[i].vCenter) <= DIST_LIMITS);
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
	OBJECT->ClearToChangeScene();
	SAFE_RELEASE(m_pSprite);
	MAP->Destroy();
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
	if ((P_STATE)OBJECT->GetPlayer()->GetMesh()->GetIndex() == P_BOWATTACK1)
	{
		UI->DrawAim(m_pSprite);
	}
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