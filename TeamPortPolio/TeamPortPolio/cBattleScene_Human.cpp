#include "stdafx.h"
#include "cBattleScene_Human.h"
#include "cPlayer.h"


cBattleScene_Human::cBattleScene_Human()
	: m_pSprite(NULL)
{
	SOUND->LoadFile("Battle_Human_BGM", "Sound/BGM/BattleScene_Human/Joust.mp3", true);
}


cBattleScene_Human::~cBattleScene_Human()
{
}

void cBattleScene_Human::OnEnter()
{
	SOUND->Play("Battle_Human_BGM");

	D3DXCreateSprite(D3DDevice, &m_pSprite);
	MAP->Init(SCENE_BATTLE_HUMAN);
	UI->Change(SCENE_BATTLE_HUMAN);

	m_stWeather = MAP->GetWeather();
	EFFECT->OnEnter(m_stWeather);
	Setup_DirLight();

	ASTAR->Setup(MAP->GetVecPosOfNode());


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


	/*cLeader* pLeader = new cLeader(D3DXVECTOR3(50, 0, -50), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pLeader->SetID(C_C_ORC_MELEE);
	pLeader->Init();
	pLeader->SetCamp(CAMP_ENEMY1);
	pLeader->SetTargetIndex(11581);
	OBJECT->AddObject(pLeader);
	OBJECT->AddLeader(pLeader);*/





	//OBJECT->GetPlayer()->GetCharacterEntity()->SetPos(D3DXVECTOR3(-50, 0, -5));
	//OBJECT->GetPlayer()->GetCharacterEntity()->SetForward(D3DXVECTOR3(0, 0, 1));
}

void cBattleScene_Human::OnUpdate()
{
	MAP->Update();
	UI->Update(TIME->DeltaTime());
	EFFECT->OnUpdate();

	// >> UI의 이벤트 정보 
	int indexInMiniMap;
	int buttonIndex;
	int eventIDTap;
	int itemID;

	UI->GetEvent(indexInMiniMap, buttonIndex, eventIDTap, itemID);
	if (indexInMiniMap > 0)
	{
		OBJECT->GetPlayer()->SetUnitLeaderTargetIndex(indexInMiniMap);
		cout << "UI Index : " << indexInMiniMap << endl;
	}
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
	case BATTLE_MINIMAP_RESULT:
		UI->Update(0);
		SCENE->ChangeScene((OBJECT->GetPlayerID() == C_C_HUMAN_MALE) ? SCENE_TOWN_HUMAN : SCENE_TOWN_ORC);
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
					UI->CreateResultMessage(BATTLE_MINIMAP_VICTORY);
				}
				else if (L->GetCamp() == CAMP_PLAYER&&OBJECT->GetPlayer()->IsDeath() == true)
				{
					UI->CreateResultMessage(BATTLE_MINIMAP_DEFEAT);
				}
			}
		}
	}
}

void cBattleScene_Human::OnExit()
{
	SOUND->Stop("Battle_Scene_Human");

	OBJECT->ClearToChangeScene();
	OBJECT->GetPlayer()->GetUnitLeader()->DeleteDeathUnitInExitScene();
	ASTAR->Release();
	SAFE_RELEASE(m_pSprite);
	UI->Release();
	MAP->Destroy();
	EFFECT->Release();
}

void cBattleScene_Human::OnRender()
{
	EFFECT->Render_Begin();
	MAP->Render();
	EFFECT->Render_End();
	OBJECT->Render();

	UI->Render(m_pSprite);
}
void cBattleScene_Human::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void cBattleScene_Human::Setup_DirLight()
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