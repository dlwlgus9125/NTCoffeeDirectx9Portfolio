#include "stdafx.h"
#include "cSelectScene.h"
#include "cSceneCamera.h"
#include "cPlayer.h"


cSelectScene::cSelectScene()
	: m_pImage(NULL), m_pSprite(NULL), m_nCurrentPlayer(SELECT_NONE), m_vPosition(0, 0, 0)
	, m_vCameraDist(0), m_vCameraStartDist(20.0f)
{
}


cSelectScene::~cSelectScene()
{
}

void cSelectScene::OnEnter()
{
	m_nCurrentPlayer = SELECT_NONE;

	m_pImage = new cUIImage();
	m_pImage->Setup_Image("Image/UI/SelectScene/Bg/Select1.png");

	RECT rc;
	m_pImage->Setup(D3DXVECTOR3(0, 0, 1.0f), UI_IMAGE);
	m_pImage->SetSize(ST_SIZEN(m_pImage->GetSize().nWidth, m_pImage->GetSize().nHeight + 30));
	m_pImage->SetHidden(false);

	m_mapPlayer[SELECT_HUMAN] = new cPlayer(m_vPosition, 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 5000);
	m_mapPlayer[SELECT_HUMAN]->SetID(C_C_HUMAN_MALE);
	m_mapPlayer[SELECT_HUMAN]->Init();

	m_mapPlayer[SELECT_ORC] = new cPlayer(m_vPosition, 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 5000);
	m_mapPlayer[SELECT_ORC]->SetID(C_C_ORC_MALE);
	m_mapPlayer[SELECT_ORC]->Init();

	D3DXCreateSprite(D3DDevice, &m_pSprite);

	SCENE_CAMERA->Setup(-0.25f, 7.0f, 18.0f, m_vCameraStartDist);
	UI->Change(SCENE_SELECT);
}

void cSelectScene::OnUpdate()
{
	m_pImage->Update(TIME->DeltaTime());
	UI->Update(TIME->DeltaTime());

	int indexInMiniMap;
	int buttonIndex;
	int eventIDTap;
	int itemID;

	UI->GetEvent(indexInMiniMap, buttonIndex, eventIDTap, itemID);

	if (m_nCurrentPlayer != SELECT_NONE) MovePosition();

	switch (buttonIndex)
	{
	case SELECT_BTN_ORC:
		if (m_nCurrentPlayer == SELECT_ORC)	break;
		m_nCurrentPlayer = SELECT_ORC;
		SCENE_CAMERA->SetDistance(m_vCameraStartDist);

		UI->SetEvent(SELECT_MSGBOX_ORC, true);
		UI->SetEvent(SELECT_MSGBOX_HUMAN, false);
		break;
	case SELECT_BTN_HUMAN:
		if (m_nCurrentPlayer == SELECT_HUMAN) break;
		m_nCurrentPlayer = SELECT_HUMAN;
		SCENE_CAMERA->SetDistance(m_vCameraStartDist);

		UI->SetEvent(SELECT_MSGBOX_ORC, false);
		UI->SetEvent(SELECT_MSGBOX_HUMAN, true);
		break;
	case SELECT_BTN_CREATE:
		if (m_nCurrentPlayer != SELECT_NONE)
		{
			/*OBJECT->AddCharacter(m_mapPlayer[m_nCurrentPlayer]);
			OBJECT->AddObject(m_mapPlayer[m_nCurrentPlayer]);*/
			OBJECT->SetPlayer(m_mapPlayer[m_nCurrentPlayer]);

			SOUND->Stop("LoginBGM");
			SCENE->SetIsSoundPlayed(false);

			// SCENE->ChangeScene(SCENE_BATTLE_HUMAN);
			if(m_nCurrentPlayer == SELECT_HUMAN) SCENE->ChangeScene(SCENE_TOWN_HUMAN);
			else if (m_nCurrentPlayer == SELECT_ORC) SCENE->ChangeScene(SCENE_TOWN_ORC);
		}
		break;

	case SELECT_BTN_BACK:
		SCENE->ChangeScene(SCENE_LOGIN);
		break;
	}
}

void cSelectScene::OnExit()
{
	m_pImage->Destroy();

	switch (m_nCurrentPlayer)
	{
	case SELECT_HUMAN:
		m_mapPlayer[SELECT_ORC]->Release();
		break;

	case SELECT_ORC:
		m_mapPlayer[SELECT_HUMAN]->Release();
		break;
	}

	UI->DestroyEventButton();
	UI->Release();
}

void cSelectScene::OnRender()
{
	m_pImage->Render(m_pSprite);
	if (m_nCurrentPlayer != SELECT_NONE) m_mapPlayer[m_nCurrentPlayer]->Render();
	UI->Render(m_pSprite);
}

void cSelectScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void cSelectScene::MovePosition()
{
	m_vCameraDist = SCENE_CAMERA->GetDistance();

	if (m_vCameraDist > 10.0f)
	{
		m_mapPlayer[m_nCurrentPlayer]->GetMesh()->SetAnimationIndexBlend(P_WALK);

		m_vCameraDist -= 0.1f;
		SCENE_CAMERA->SetDistance(m_vCameraDist);
	}
	else
	{
		if (m_mapPlayer[m_nCurrentPlayer]->GetMesh()->GetPassedTime() > m_mapPlayer[m_nCurrentPlayer]->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.3f)
		{
			if (m_mapPlayer[m_nCurrentPlayer]->GetMesh()->GetIndex() != P_STAND&&m_mapPlayer[m_nCurrentPlayer]->GetMesh()->GetIndex() != P_BATTLECRY)
			{
				m_mapPlayer[m_nCurrentPlayer]->GetMesh()->SetAnimationIndexBlend(P_BATTLECRY);
			}
			else
			{
				m_mapPlayer[m_nCurrentPlayer]->GetMesh()->SetAnimationIndexBlend(P_STAND);
			}
		}
	}
}

void cSelectScene::Setup_DirLight()
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
