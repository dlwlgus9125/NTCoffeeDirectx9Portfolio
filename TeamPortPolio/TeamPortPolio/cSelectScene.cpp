#include "stdafx.h"
#include "cSelectScene.h"
#include "cPlayer.h"


cSelectScene::cSelectScene()
	: m_pImage(NULL), m_pSprite(NULL), m_nCurrentPlayer(SELECT_NONE)
{
}


cSelectScene::~cSelectScene()
{
	SAFE_DELETE(m_pImage);
	SAFE_DELETE(m_pSprite);
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

	m_mapPlayer[SELECT_HUMAN] = new cPlayer(D3DXVECTOR3(-5, 10.0f, 10.0f), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 5000);
	m_mapPlayer[SELECT_HUMAN]->SetID(C_C_HUMAN_MELEE);
	m_mapPlayer[SELECT_HUMAN]->Init();

	m_mapPlayer[SELECT_ORC] = new cPlayer(D3DXVECTOR3(-5, 10.0f, 10.0f), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 5000);
	m_mapPlayer[SELECT_ORC]->SetID(C_C_ORC_MELEE);
	m_mapPlayer[SELECT_ORC]->Init();

	D3DXCreateSprite(D3DDevice, &m_pSprite);

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

	if(m_nCurrentPlayer != SELECT_NONE) MovePosition();

	switch (buttonIndex)
	{
	case SELECT_BTN_ORC:
		m_nCurrentPlayer = SELECT_ORC;

		UI->SetEvent(SELECT_MSGBOX_ORC, true);
		UI->SetEvent(SELECT_MSGBOX_HUMAN, false);
		break;
	case SELECT_BTN_HUMAN:
		m_nCurrentPlayer = SELECT_HUMAN;
		
		UI->SetEvent(SELECT_MSGBOX_ORC, false);
		UI->SetEvent(SELECT_MSGBOX_HUMAN, true);
		break;
	case SELECT_BTN_CREATE:
		if (m_nCurrentPlayer != SELECT_NONE)
		{
			OBJECT->AddCharacter(m_mapPlayer[m_nCurrentPlayer]);
			OBJECT->AddObject(m_mapPlayer[m_nCurrentPlayer]);
			OBJECT->SetPlayer(m_mapPlayer[m_nCurrentPlayer]);

			SCENE->ChangeScene(SCENE_TOWN);
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

	UI->Release();
}

void cSelectScene::OnRender()
{
	m_pImage->Render(m_pSprite);
	if(m_nCurrentPlayer != SELECT_NONE) m_mapPlayer[m_nCurrentPlayer]->Render();
	UI->Render(m_pSprite);
}

void cSelectScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void cSelectScene::MovePosition()
{
	float fDeltaY = 0.05f;
	float fDeltaZ = 0.01f;
	D3DXVECTOR3 currentPos = m_mapPlayer[m_nCurrentPlayer]->GetCharacterEntity()->Pos();	

	if (currentPos.z > 0 || currentPos.y > 5.0f)
	{
		m_mapPlayer[m_nCurrentPlayer]->GetMesh()->SetAnimationIndexBlend(P_WALK);
		m_mapPlayer[m_nCurrentPlayer]->GetCharacterEntity()->SetPos(D3DXVECTOR3(currentPos.x, currentPos.y - fDeltaY, currentPos.z - fDeltaZ));
		CAMERA->SetLookAt(currentPos, D3DX_PI);
	}
	else
	{
		m_mapPlayer[m_nCurrentPlayer]->GetMesh()->SetAnimationIndexBlend(P_STAND);
	}
}