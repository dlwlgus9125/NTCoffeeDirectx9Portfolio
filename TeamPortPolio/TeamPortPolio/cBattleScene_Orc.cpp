#include "stdafx.h"
#include "cBattleScene_Orc.h"
#include "cPlayer.h"


cBattleScene_Orc::cBattleScene_Orc()
	: m_pSprite(NULL)
{
}


cBattleScene_Orc::~cBattleScene_Orc()
{
}

void cBattleScene_Orc::OnEnter()
{
	D3DXCreateSprite(D3DDevice, &m_pSprite);
	MAP->Init(SCENE_BATTLE_ORC);
	UI->Change(SCENE_BATTLE_ORC);
	ASTAR->Setup(MAP->GetVecPosOfNode());
	cout << "size : " << MAP->GetVecPosOfNode().size() << endl;
	m_stWeather = MAP->GetWeather();
	EFFECT->Init(m_stWeather);
	Setup_DirLight();

	OBJECT->GetPlayer()->GetCharacterEntity()->SetPos(D3DXVECTOR3(40, 0, -50));
	OBJECT->GetPlayer()->SetRotY(MATH->GetRotY(D3DXVECTOR3(0.7, 0, -0.7)));
	OBJECT->GetPlayer()->SetCurrentLeader();
	OBJECT->GetPlayer()->GetUnitLeader()->GetCharacterEntity()->SetPos(D3DXVECTOR3(30, 0, -50));
	OBJECT->GetPlayer()->GetUnitLeader()->GetCharacterEntity()->SetForward(D3DXVECTOR3(0.35, 0, 0.9));

	OBJECT->AddCharacter(OBJECT->GetPlayer());
	OBJECT->AddObject(OBJECT->GetPlayer());
	OBJECT->AddObject(OBJECT->GetPlayer()->GetUnitLeader());
	OBJECT->AddLeader(OBJECT->GetPlayer()->GetUnitLeader());


	OBJECT->GetPlayer()->GetUnitLeader()->AddUnitInManager();


	cLeader* pLeader = new cLeader(D3DXVECTOR3(-33.5f, 0, 23.5f), 1.0f, D3DXVECTOR3(0.35f, 0,0.94f), 0.5f, 200);
	pLeader->SetID(C_C_ORC_MELEE);
	pLeader->Init();
	pLeader->SetCamp(CAMP_ENEMY1);
	pLeader->SetTargetIndex(11581);
	for (int i = 0; i < 20; i++)pLeader->AddUnitInTown(C_C_ORC_MELEE);
	pLeader->AddUnitInManager();
	pLeader->SetRectOffset();
	OBJECT->AddObject(pLeader);
	OBJECT->AddLeader(pLeader);

	vector<cObject*> vecObject = OBJECT->GetObjects();

	//OBJECT->GetPlayer()->GetCharacterEntity()->SetPos(D3DXVECTOR3(50, 0, -50));
	//OBJECT->GetPlayer()->GetCharacterEntity()->SetForward(D3DXVECTOR3(0, 0, 1));
}

void cBattleScene_Orc::OnUpdate()
{
	MAP->Update();
	UI->Update(TIME->DeltaTime());
	EFFECT->Update();


	
	// >> UI의 이벤트 정보 
	int indexInMiniMap;
	int buttonIndex;
	int eventIDTap;
	int itemID;
	OBJECT->Update(TIME->DeltaTime());
	UI->GetEvent(indexInMiniMap, buttonIndex, eventIDTap, itemID);
	if (indexInMiniMap > 0)
	{
		OBJECT->GetPlayer()->SetUnitLeaderTargetIndex(indexInMiniMap);
		cout << "UI Index : " << indexInMiniMap << endl;
	}
	cout << "player index : " <<OBJECT->GetPlayer()->GetIndex()<< endl;
	switch (buttonIndex)
	{
	case TITLE_BTN_FMT_RECT:
		OBJECT->GetPlayer()->GetUnitLeader()->SetRectOffset();
		break;
	case TITLE_BTN_FMT_TRI:
		OBJECT->GetPlayer()->GetUnitLeader()->SetTriOffset();
		break;
	case TITLE_BTN_ATTSTATE:
		OBJECT->GetPlayer()->GetUnitLeader()->ClickedButtonOne();
		break;
	case TITLE_BTN_DEFSTATE:
		OBJECT->GetPlayer()->GetUnitLeader()->ClickedButtonTwo();
		break;
	}
	// <<
	
	if (TIME->UpdateOneSecond())
	{
		for each(auto L in OBJECT->GetLeader())
		{
			if (L->IsDeath() == true)
			{
				if (L->GetCamp() == CAMP_ENEMY1)
				{
					if (CHARACTERDB->GetMapCharacter(OBJECT->GetPlayer()->GetID())->m_raceID == C_R_HUMAN) SCENE->ChangeScene(SCENE_TOWN_HUMAN);
					else if (CHARACTERDB->GetMapCharacter(OBJECT->GetPlayer()->GetID())->m_raceID == C_R_ORC) SCENE->ChangeScene(SCENE_TOWN_ORC);
				}
				else if (L->GetCamp() == CAMP_PLAYER&&OBJECT->GetPlayer()->IsDeath()==true)
				{
					if (CHARACTERDB->GetMapCharacter(OBJECT->GetPlayer()->GetID())->m_raceID == C_R_HUMAN) SCENE->ChangeScene(SCENE_TOWN_HUMAN);
					else if (CHARACTERDB->GetMapCharacter(OBJECT->GetPlayer()->GetID())->m_raceID == C_R_ORC) SCENE->ChangeScene(SCENE_TOWN_ORC);
				}
			}
		}

	}
}

void cBattleScene_Orc::OnExit()
{
	OBJECT->ClearToChangeScene();
	OBJECT->GetPlayer()->GetUnitLeader()->DeleteDeathUnitInExitScene();
	ASTAR->Release();
	SAFE_RELEASE(m_pSprite);
	UI->Release();
	MAP->Destroy();
	EFFECT->Release();
}

void cBattleScene_Orc::OnRender()
{
	//EFFECT->Render_Begin();
	MAP->Render();
	//EFFECT->Render_End();
	OBJECT->Render();
	UI->Render(m_pSprite);
}

void cBattleScene_Orc::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void cBattleScene_Orc::Setup_DirLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3   vDir(1.0f, 1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	D3DDevice->SetLight(0, &stLight);
	D3DDevice->LightEnable(0, true);
}