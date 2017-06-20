#include "stdafx.h"
#include "cPlayer.h"
#include "cGameManager.h"
#include "cLeader.h"
#include"cArrowMaker.h"
#include "cCharacterDB.h"


cPlayer::cPlayer(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed)
{
	m_camp = CAMP_PLAYER;
	m_CharacterEntity = new ISteeringEntity(pos, radius, forward, mass, maxSpeed);
	m_unitLeader = NULL;
	m_unitLeader = new cLeader(pos, radius, forward, mass, maxSpeed);

	m_unitLeader->SetID(C_C_HUMAN_BOWMAN);

	m_unitLeader->SetCamp(CAMP_PLAYER);
	m_unitLeader->Init();
	m_unitLeader->SetTargetIndex(ASTAR->GetGraph()->GetNode(16001)->Id());
	OBJECT->AddObject(m_unitLeader);
	OBJECT->AddLeader(m_unitLeader);
	m_fRotY = 0.0f;
	m_isAiming = false;
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pFsm);
}

void cPlayer::Init()
{
	m_CollideSphere.fRadius = m_CharacterEntity->Radius();
	m_CollideSphere.vCenter = m_CharacterEntity->Pos();

	m_arrangeCollideSphere.fRadius = 15.0f;
	m_arrangeCollideSphere.vCenter = m_CharacterEntity->Pos();
	cCharacter::Init();


	//m_pSkinnedMesh->FindAttackBone(m_Status->m_szColliderBoneName);
	m_rightHand = m_leftHand = m_AttackCollider = NULL;


	{
		//>>오른손 찾기
		m_rightHand = TEXTURE->GetCharacterResource(m_Status->m_szPath, m_Status->m_szFileName)->GetRightHand();

		////>>왼손 찾기
		m_leftHand = TEXTURE->GetCharacterResource(m_Status->m_szPath, m_Status->m_szFileName)->GetLeftHand();
	}


	//char* test = CHARACTERDB->GetMapCharacter(C_C_SWORD_SWORD)->m_szPath;
	//m_rightHand->pFrameFirstChild = TEXTURE->GetCharacterResource(CHARACTERDB->GetMapCharacter(C_C_SWORD_SWORD)->m_szPath, CHARACTERDB->GetMapCharacter(C_C_SWORD_SWORD)->m_szFileName)->GetFrameRoot();
	//m_leftHand->pFrameFirstChild = TEXTURE->GetCharacterResource(CHARACTERDB->GetMapCharacter(C_C_SHIELD_SHIELD)->m_szPath, CHARACTERDB->GetMapCharacter(C_C_SHIELD_SHIELD)->m_szFileName)->GetFrameRoot();

	//m_pSkinnedMesh->FindAttackBone(CHARACTERDB->GetMapCharacter(C_C_SWORD_SWORD)->m_szColliderBoneName);
	//cSkinnedMesh* test = TEXTURE->GetCharacterResource(m_Status->m_szPath, m_Status->m_szFileName);
	m_pFsm = new cStateMachine<cPlayer*>(this);
	m_pFsm->Register(PLAYER_STATE_IDLE, new Player_Idle());
	m_pFsm->Register(PLAYER_STATE_WALK, new Player_Walk());
	m_pFsm->Register(PLAYER_STATE_ATTACK, new Player_Attack());
	m_pFsm->Register(PLAYER_STATE_DEFENCE, new Player_Defence());
	m_pFsm->Play(PLAYER_STATE_IDLE);

}

void cPlayer::Update(float deltaTime)
{
	cCharacter::Update(deltaTime);
	m_CollideSphere.vCenter.y += 0.5f; // 충돌판 높이값 조절
	m_pFsm->Update(deltaTime);

	D3DXVECTOR3 movePos = m_CharacterEntity->Pos();
	MAP->GetHeight(movePos.x, movePos.y, movePos.z);
	m_CharacterEntity->SetPos(movePos);

	if (INPUT->IsKeyPress(VK_A))
	{
		m_fRotY -= 0.03;
	}
	if (INPUT->IsKeyPress(VK_D))
	{
		m_fRotY += 0.03;
	}


	//<< 화살처리
	if (INPUT->IsMouseDown(MOUSE_RIGHT) && !m_isAiming)
	{

		//	CAMERA->SetCameraDistance(0.1);
			//화살구체

	}

	if (INPUT->IsMouseDown(MOUSE_LEFT) && !m_isAiming)
	{
		//CAMERA->SetCameraDistance(5);

	//	OBJECT->AddPlayerArrow(m_CharacterEntity, SetUpAim());
		//m_isAiming = true;
	}
	//화살처리

	D3DXMATRIXA16 matR;
	D3DXVECTOR3 forward = D3DXVECTOR3(0, 0, 1);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matR, m_fRotY);

	D3DXVec3TransformCoord(&forward, &forward, &matR);
	m_CharacterEntity->SetForward(forward);

	m_pSkinnedMesh->SetPosition(m_CharacterEntity->Pos(), m_CharacterEntity->Forward());

	CAMERA->SetLookAt(m_CharacterEntity->Pos(), m_fRotY);


}

void cPlayer::Render()
{
	cCharacter::Render();
	if (FRUSTUM->IsIn(m_pSkinnedMesh->GetBoundingSphere()))
	{
		m_pSkinnedMesh->UpdateAndRender(m_isDeath);

		SetAttackColliderPos();
		D3DXMATRIXA16 matT;
		D3DXMatrixIdentity(&matT);

		D3DXMatrixTranslation(&matT, m_AttackCollideSphere.vCenter.x, m_AttackCollideSphere.vCenter.y, m_AttackCollideSphere.vCenter.z);

		D3DDevice->SetTransform(D3DTS_WORLD, &matT);
		D3DDevice->SetMaterial(&m_MeshSphere.m_stMtlSphere);

		D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_MeshSphere.m_pMeshSphere->DrawSubset(0);
		D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}




void cPlayer::SetUnitLeaderTargetIndex(int index)
{
	if (m_unitLeader)
	{

		if (ASTAR->GetGraph()->GetNode(index)->Active())
		{
			if (!THREAD->IsReCreateFindPathThread(HANDlE_ATSTAR_FINDPATH))
			{

				m_unitLeader->PathClear();
				m_unitLeader->SetTargetIndex(index);
			}
		}

	}
}
	void cPlayer::SellItem(int itemSID)
	{
		for (vector<int>::iterator it = m_vecInventory.begin(); it != m_vecInventory.end(); )
		{
			if (*it == itemSID)
			{
				it = m_vecInventory.erase(it);
				break;
			}
			else it++;
		}

		// 제대로 작동하면 버블정렬 Math꺼 사용하기.
	}

	void cPlayer::ByuItem(int itemSID)
	{
		m_vecInventory.push_back(itemSID);

		// 제대로 작동하면 버블정렬 Math꺼 사용하기.
	}

	void cPlayer::EquipRightHand(int itemSID)
	{
	}

	void cPlayer::EquipLeftHand(int itemSID)
	{
	}
