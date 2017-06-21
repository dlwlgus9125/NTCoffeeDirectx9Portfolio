#include "stdafx.h"
#include "cTownScene_Orc.h"
#include "cPlayer.h"


cTownScene_Orc::cTownScene_Orc()
{
}


cTownScene_Orc::~cTownScene_Orc()
{
}

void cTownScene_Orc::OnEnter()
{
	D3DXCreateSprite(D3DDevice, &m_pSprite);
	MAP->Init(SCENE_TOWN_ORC);
	UI->Change(SCENE_TOWN_ORC);

	m_stWeather = MAP->GetWeather();
	EFFECT->Init(m_stWeather);

	Setup_DirLight();

	// OBJECT->GetPlayer()->GetCharacterEntity()->SetPos(D3DXVECTOR3(-8, 0, 30));
	// OBJECT->GetPlayer()->GetCharacterEntity()->SetForward(D3DXVECTOR3(0, 0, 1));

	cLeader* pLeader = new cLeader(D3DXVECTOR3(50, 0, -50), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pLeader->SetID(C_C_ORC_MELEE);
	pLeader->Init();
	pLeader->SetCamp(CAMP_ENEMY1);
	pLeader->SetTargetIndex(11581);
	OBJECT->AddObject(pLeader);
	OBJECT->AddLeader(pLeader);
}

void cTownScene_Orc::OnUpdate()
{
	MAP->Update();
	OBJECT->Update(TIME->DeltaTime());
	EFFECT->Update();
	UI->Update(TIME->DeltaTime());
}

void cTownScene_Orc::OnExit()
{
	SAFE_RELEASE(m_pSprite);
	MAP->Destroy();
	OBJECT->Release();
	EFFECT->Release();
	UI->Release();
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
	D3DDevice->SetLight(0, &stLight);
	D3DDevice->LightEnable(0, true);
}
