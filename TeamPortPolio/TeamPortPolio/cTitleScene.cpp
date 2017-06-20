#include "stdafx.h"
#include "cTitleScene.h"
#include "cObject.h"
#include "cPlayer.h"
#include "cLeader.h"
#include "cUnit.h"


cTitleScene::cTitleScene() :
	m_pSprite(NULL)
{	
}


cTitleScene::~cTitleScene()
{
	SAFE_RELEASE(m_pSprite);
}

void cTitleScene::OnEnter()
{
	D3DXCreateSprite(D3DDevice, &m_pSprite);
	MAP->Init(SCENE_TITLE);
	UI->Change(SCENE_TITLE);
	cPlayer* pPlayer = new cPlayer(D3DXVECTOR3(-8,0,30), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pPlayer->SetID(C_C_ORC_MALE);
	pPlayer->Init();
	OBJECT->AddCharacter(pPlayer);



	OBJECT->AddObject(pPlayer);
	OBJECT->SetPlayer(pPlayer);


	cLeader* pLeader = new cLeader(ASTAR->GetGraph()->GetNode(11581)->Pos(), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pLeader->SetID(C_C_ORC_MELEE);
	pLeader->SetCamp(CAMP_ENEMY1);
	pLeader->Init();
	int index=0;
	MAP->GetMap()->GetIndex(pLeader->GetCharacterEntity()->Pos().x, pLeader->GetCharacterEntity()->Pos().z, index);
	pLeader->SetTargetIndex(index);
		;
	OBJECT->AddObject(pLeader);
	OBJECT->AddLeader(pLeader);
	Setup_DirLight();


	ASTAR->SetMapLoadingComplete(true);
}

void cTitleScene::OnUpdate()
{
	MAP->Update();
	UI->Update(TIME->DeltaTime());

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
		cout << "Node ID : " << ASTAR->GetGraph()->GetNode(indexInMiniMap)->Id() << endl;
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
	}
	// <<

	OBJECT->Update(TIME->DeltaTime());	
}

void cTitleScene::OnExit()
{
	ASTAR->SetMapLoadingComplete(false);
	SAFE_RELEASE(m_pSprite);
	MAP->Destroy();
	UI->Release();
}

void cTitleScene::OnRender()
{
	MAP->Render();
	OBJECT->Render();
	UI->Render(m_pSprite);	
}

void cTitleScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}


void cTitleScene::Setup_DirLight()
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