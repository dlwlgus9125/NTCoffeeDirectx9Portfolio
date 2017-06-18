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
	Setup_DirLight();


	cPlayer* pPlayer = new cPlayer(D3DXVECTOR3(50, 0, -50), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pPlayer->SetID(C_C_HUMAN_MALE);
	pPlayer->Init();
	OBJECT->AddCharacter(pPlayer);



	OBJECT->AddObject(pPlayer);
	OBJECT->SetPlayer(pPlayer);


	cLeader* pLeader = new cLeader(D3DXVECTOR3(50, 0, -50), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pLeader->SetID(C_C_ORC_MELEE);
	pLeader->Init();
	pLeader->SetCamp(CAMP_ENEMY1);
	pLeader->SetTargetIndex(11581);
	OBJECT->AddObject(pLeader);
	OBJECT->AddLeader(pLeader);


	OBJECT->GetPlayer()->GetCharacterEntity()->SetPos(D3DXVECTOR3(50, 0, -50));
	OBJECT->GetPlayer()->GetCharacterEntity()->SetForward(D3DXVECTOR3(0, 0, 1));
}

void cBattleScene_Orc::OnUpdate()
{
	MAP->Update();
	OBJECT->Update(TIME->DeltaTime());
}

void cBattleScene_Orc::OnExit()
{
	SAFE_RELEASE(m_pSprite);
	MAP->Destroy();
}

void cBattleScene_Orc::OnRender()
{
	MAP->Render();
	OBJECT->Render();
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