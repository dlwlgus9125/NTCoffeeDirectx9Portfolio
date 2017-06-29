#include "stdafx.h"
#include "cPlayer.h"
#include "cGameManager.h"
#include "cLeader.h"
#include "cCharacterDB.h"


cPlayer::cPlayer(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed)
{
	m_camp = CAMP_PLAYER;
	m_CharacterEntity = new ISteeringEntity(pos, radius, forward, mass, maxSpeed);
	/*m_unitLeader = NULL;
	m_unitLeader = new cLeader(pos, radius, forward, mass, maxSpeed);

	m_unitLeader->SetID(C_C_HUMAN_BOWMAN);

	m_unitLeader->SetCamp(CAMP_PLAYER);
	m_unitLeader->Init();
	m_unitLeader->SetTargetIndex(ASTAR->GetGraph()->GetNode(16001)->Id());*/




	FLYPos = D3DXVECTOR3(0, 2.0f, 0);
	m_fRotY = 0.0f;
	m_isAiming = false;
	m_AttackType = ATTACK_MELEE;
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pFsm);
	for each(auto c in m_mapLeader)
	{
		SAFE_DELETE(c.second);
	}
	m_mapLeader.clear();
	SAFE_DELETE(m_pSkinnedMesh);
}



void cPlayer::Init()
{
	m_mapLeader[LEADER_MELEE] = new cLeader(D3DXVECTOR3(0, 0, 0), m_CharacterEntity->Radius(), m_CharacterEntity->Forward(), m_CharacterEntity->Mass(), m_CharacterEntity->MaxSpeed());
	if (CHARACTERDB->GetMapCharacter(m_ID)->m_raceID == C_R_HUMAN)m_mapLeader[LEADER_MELEE]->SetID(C_C_HUMAN_MELEE);
	else if (CHARACTERDB->GetMapCharacter(m_ID)->m_raceID == C_R_ORC)m_mapLeader[LEADER_MELEE]->SetID(C_C_ORC_MELEE);
	m_mapLeader[LEADER_MELEE]->SetCamp(CAMP_PLAYER);
	m_mapLeader[LEADER_MELEE]->Init();

	m_mapLeader[LEADER_BOW] = new cLeader(D3DXVECTOR3(0, 0, 0), m_CharacterEntity->Radius(), m_CharacterEntity->Forward(), m_CharacterEntity->Mass(), m_CharacterEntity->MaxSpeed());
	if (CHARACTERDB->GetMapCharacter(m_ID)->m_raceID == C_R_HUMAN)m_mapLeader[LEADER_BOW]->SetID(C_C_HUMAN_BOWMAN);
	else if (CHARACTERDB->GetMapCharacter(m_ID)->m_raceID == C_R_ORC)m_mapLeader[LEADER_BOW]->SetID(C_C_ORC_BOWMAN);
	m_mapLeader[LEADER_BOW]->SetCamp(CAMP_PLAYER);
	m_mapLeader[LEADER_BOW]->Init();

	m_mapLeader[LEADER_CAVALRY] = new cLeader(D3DXVECTOR3(0, 0, 0), m_CharacterEntity->Radius(), m_CharacterEntity->Forward(), m_CharacterEntity->Mass(), m_CharacterEntity->MaxSpeed());
	if (CHARACTERDB->GetMapCharacter(m_ID)->m_raceID == C_R_HUMAN)m_mapLeader[LEADER_CAVALRY]->SetID(C_C_HUMAN_CAVALRY);
	else if (CHARACTERDB->GetMapCharacter(m_ID)->m_raceID == C_R_ORC)m_mapLeader[LEADER_CAVALRY]->SetID(C_C_ORC_CAVALRY);
	m_mapLeader[LEADER_CAVALRY]->SetCamp(CAMP_PLAYER);
	m_mapLeader[LEADER_CAVALRY]->Init();

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

	m_RightWeaponMesh = NULL;
	m_LeftWeaponMesh = NULL;


	TEXTURE->GetCharacterResource(CHARACTERDB->GetMapCharacter(C_C_SWORD_SWORD)->m_szPath, CHARACTERDB->GetMapCharacter(C_C_SWORD_SWORD)->m_szFileName)->FindAttackBone("Sword_2H_Broadsword_A_03_Bone08");
	TEXTURE->GetCharacterResource(CHARACTERDB->GetMapCharacter(C_C_SHIELD_SHIELD)->m_szPath, CHARACTERDB->GetMapCharacter(C_C_SHIELD_SHIELD)->m_szFileName)->FindAttackBone("Weapon_Attack_Bone_Col_root");
	TEXTURE->GetCharacterResource(CHARACTERDB->GetMapCharacter(C_C_BOW_BOW)->m_szPath, CHARACTERDB->GetMapCharacter(C_C_BOW_BOW)->m_szFileName)->FindAttackBone("Bow_1H_Standard_C_01_Bone00");


	/*CHARACTERDB->GetMapCharacter(C_C_BOW_BOW)->
	(CHARACTERDB->GetMapCharacter(C_C_SWORD_SWORD)->m
		CHARACTERDB->GetMapCharacter(C_C_SHIELD_SHIELD)->*/


	m_pFsm = new cStateMachine<cPlayer*>(this);
	m_pFsm->Register(PLAYER_STATE_IDLE, new Player_Idle());
	m_pFsm->Register(PLAYER_STATE_WALK, new Player_Walk());
	m_pFsm->Register(PLAYER_STATE_ATTACK, new Player_Attack());
	m_pFsm->Register(PLAYER_STATE_BOWATTACK, new Player_BowAttack());
	m_pFsm->Register(PLAYER_STATE_DEFENCE, new Player_Defence());
	m_pFsm->Register(PLAYER_STATE_DEFEAT, new Player_Death());
	m_pFsm->Play(PLAYER_STATE_IDLE);
	m_isPull = false;
	m_MeleeCollider.fRadius = 0.2f;
	m_currentLeaderType = LEADER_MELEE;
	SetCurrentLeader();

	m_AttackType = ATTACK_MELEE;
	//
	FLY = false;
}

void cPlayer::Update(float deltaTime)
{
	if (INPUT->IsKeyDown(VK_0))
	{
		FLYPos=	m_CharacterEntity->Pos();
		FLY = true;
	}
	if (INPUT->IsKeyDown(VK_9))FLY = false;


	if (INPUT->IsKeyDown(VK_SPACE))
	{
		cout << "pos : " << m_CharacterEntity->Pos().x << " " << m_CharacterEntity->Pos().y << " " << m_CharacterEntity->Pos().z << endl;
		cout << "RotY : " << MATH->GetRotY(OBJECT->GetPlayer()->GetCharacterEntity()->Forward()) << endl;
		cout << "Forward : " << m_CharacterEntity->Forward().x << " " << m_CharacterEntity->Forward().y << " " << m_CharacterEntity->Forward().z << endl;
		cout << "getindex : " << GetIndex() << endl;
	
	}

	if (m_isDeath == true && m_isPull == false)m_isPull = true;
	if (m_isDeath == false)
	{
		cCharacter::Update(deltaTime);

		m_CollideSphere.vCenter.y += 0.5f; // 충돌판 높이값 조절
		m_pFsm->Update(deltaTime);


		m_MeleeCollider.vCenter = m_CharacterEntity->Pos() + (m_CharacterEntity->Forward()*0.8f);
		m_MeleeCollider.vCenter.y += 0.5f;
		
		if (!FLY)
		{
			if (INPUT->IsKeyPress(VK_A))
			{
				m_fRotY -= 0.06;
			}
			if (INPUT->IsKeyPress(VK_D))
			{
				m_fRotY += 0.06;
			}
	
			D3DXMATRIXA16 matR;
			D3DXVECTOR3 forward = D3DXVECTOR3(0, 0, 1);
			D3DXMatrixIdentity(&matR);
			D3DXMatrixRotationY(&matR, m_fRotY);

			D3DXVec3TransformCoord(&forward, &forward, &matR);
			m_CharacterEntity->SetForward(forward);
	
			m_pSkinnedMesh->SetPosition(m_CharacterEntity->Pos(), m_CharacterEntity->Forward());


		}
		if (GetMesh()->GetIndex() == P_BOWATTACK1)
		{
			CAMERA->SetLookAt(m_CharacterEntity->Pos() + D3DXVECTOR3(0, 1.5, 0), m_fRotY);
			m_fRotY = CAMERA->GetCamRotAngle().y;
		}
		else
		{
				CAMERA->SetLookAt(m_CharacterEntity->Pos() + D3DXVECTOR3(0, 0.5, 0), m_fRotY);
		}
		if (INPUT->IsKeyDown(VK_F))
		{
			m_fRotY += D3DX_PI;
		}
	}

	if (FLY)
	{
		float shift = 1.0f;
		D3DXVECTOR3 forWard(0, 0, 1);
		D3DXVECTOR3 left(-1, 0, 0);
		D3DXVECTOR3 right(1, 0, 0);

		D3DXMATRIXA16 matR,matLEFT,matRIGHT;
		D3DXMatrixIdentity(&matR);
		D3DXMatrixRotationYawPitchRoll(&matR, CAMERA->GetCamRotAngle().y, CAMERA->GetCamRotAngle().x, CAMERA->GetCamRotAngle().z);
		D3DXMatrixRotationYawPitchRoll(&matRIGHT, CAMERA->GetCamRotAngle().y+ D3DX_PI, CAMERA->GetCamRotAngle().x, CAMERA->GetCamRotAngle().z);
		D3DXMatrixRotationYawPitchRoll(&matLEFT, CAMERA->GetCamRotAngle().y-D3DX_PI, CAMERA->GetCamRotAngle().x, CAMERA->GetCamRotAngle().z);

		D3DXVec3TransformCoord(&forWard, &forWard, &matR);
		D3DXVec3TransformCoord(&left, &left, &matR);
		D3DXVec3TransformCoord(&right, &right, &matR);

		if (INPUT->IsKeyPress(VK_SHIFT))shift = 5.0f;
		if (INPUT->IsKeyPress(VK_W)) FLYPos += forWard*0.2*shift;
		if (INPUT->IsKeyPress(VK_S)) FLYPos -= forWard*0.2*shift;
		if (INPUT->IsKeyPress(VK_A))FLYPos+= left*0.2*shift;
		if (INPUT->IsKeyPress(VK_D))FLYPos += right*0.2*shift;
		float rot = MATH->GetRotY(FLYPos);
		m_fRotY = CAMERA->GetCamRotAngle().y;
		CAMERA->SetLookAt(FLYPos, CAMERA->GetCamRotAngle().y);
	}
	
}

void cPlayer::Render()
{
	cCharacter::Render();

	m_pSkinnedMesh->UpdateAndRender(m_isPull);

	//>>아이템착용 출력단
	if (m_RightWeaponMesh != NULL)m_RightWeaponMesh->UpdateAndRenderForItem(m_isDeath, m_rightHand->CombinedTransformationMatrix);
	if (m_LeftWeaponMesh != NULL)m_LeftWeaponMesh->UpdateAndRenderForItem(m_isPull, m_leftHand->CombinedTransformationMatrix);
	//<<

	//SetAttackColliderPos();
	D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);

	D3DXMatrixTranslation(&matT, m_MeleeCollider.vCenter.x, m_MeleeCollider.vCenter.y, m_MeleeCollider.vCenter.z);

	D3DDevice->SetTransform(D3DTS_WORLD, &matT);
	D3DDevice->SetMaterial(&m_MeshSphere.m_stMtlSphere);

	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//m_MeshSphere.m_pMeshSphere->DrawSubset(0);
	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}




void cPlayer::SetUnitLeaderTargetIndex(int index)
{
	if (m_currentLeader && 0 <= index&&index <= MAP->GetVecPosOfNode().size())
	{

		if (ASTAR->GetGraph()->GetNode(index)->Active())
		{
			cout << "here" << endl;
			THREAD->TerminateThreadByKey(HANDLE_ATSTAR_FINDPATH);
			if (!THREAD->IsReCreateFindPathThread(HANDLE_ATSTAR_FINDPATH))
			{
				m_currentLeader->PathClear();
				m_currentLeader->SetTargetIndex(index);
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

void cPlayer::BuyItem(int itemSID)
{
	m_vecInventory.push_back(itemSID);

	// 제대로 작동하면 버블정렬 Math꺼 사용하기.
}

void cPlayer::PutOnItem(int itemSID)
{
	int itemMID = ITEMDB->GetItem(itemSID)->eMiddleID;

	switch (itemMID)
	{
	case I_M_SWORD:
	case I_M_AXE:
	{
		// 먼저 오른손 아이템 빼는 부분
		for (vector<int>::iterator it = m_vecEquipment.begin(); it != m_vecEquipment.end(); )
		{
			if (ITEMDB->GetItem((*it))->eMiddleID == I_M_SWORD ||
				ITEMDB->GetItem((*it))->eMiddleID == I_M_AXE ||
				ITEMDB->GetItem((*it))->eMiddleID == I_M_BOW)
			{
				it = m_vecEquipment.erase(it);
			}
			else
			{
				it++;
			}
		}
		m_vecEquipment.push_back(itemSID);
	}
	break;

	case I_M_BOW:
	{
		// 먼저 양손의 아이템 빼는 부분
		for (vector<int>::iterator it = m_vecEquipment.begin(); it != m_vecEquipment.end(); )
		{
			if (ITEMDB->GetItem((*it))->eMiddleID == I_M_SWORD ||
				ITEMDB->GetItem((*it))->eMiddleID == I_M_AXE ||
				ITEMDB->GetItem((*it))->eMiddleID == I_M_BOW ||
				ITEMDB->GetItem((*it))->eMiddleID == I_M_SHIELD)
			{
				it = m_vecEquipment.erase(it);
			}
			else
			{
				it++;
			}
		}
		m_vecEquipment.push_back(itemSID);
	}
	break;
	case I_M_SHIELD:
	{
		// 먼저 왼손의 아이템 빼는 부분
		for (vector<int>::iterator it = m_vecEquipment.begin(); it != m_vecEquipment.end(); )
		{
			if (ITEMDB->GetItem((*it))->eMiddleID == I_M_BOW ||
				ITEMDB->GetItem((*it))->eMiddleID == I_M_SHIELD)
			{
				it = m_vecEquipment.erase(it);
			}
			else
			{
				it++;
			}
		}
		m_vecEquipment.push_back(itemSID);
	}
	break;
	case I_M_ARMOR:
	{
		// 먼저 갑옷 빼는 부분
		for (vector<int>::iterator it = m_vecEquipment.begin(); it != m_vecEquipment.end(); )
		{
			if (ITEMDB->GetItem((*it))->eMiddleID == I_M_ARMOR)
			{
				it = m_vecEquipment.erase(it);
			}
			else
			{
				it++;
			}
		}
		m_vecEquipment.push_back(itemSID);
	}
	break;
	}
	UnEquip();
	Equip();
}

void cPlayer::PutOffItem(int itemSID)
{
	for (vector<int>::iterator it = m_vecEquipment.begin(); it != m_vecEquipment.end(); )
	{
		int itemMID = ITEMDB->GetItem(itemSID)->eMiddleID;
		int currrentItemMID = ITEMDB->GetItem(*it)->eMiddleID;
		if (itemMID == currrentItemMID)	it = m_vecEquipment.erase(it);
		else it++;
	}
	UnEquip();
	Equip();
}

void cPlayer::Equip()
{
	for (int i = 0; i < m_vecEquipment.size(); i++)
	{
		if (ITEMDB->GetItem(m_vecEquipment[i])->eMiddleID == I_M_SWORD || ITEMDB->GetItem(m_vecEquipment[i])->eMiddleID == I_M_AXE)
		{
			m_RightWeaponMesh = TEXTURE->GetCharacterResource(ITEMDB->GetItem(m_vecEquipment[i])->szTexturePath, ITEMDB->GetItem(m_vecEquipment[i])->szTextureFileName);
			if (TEXTURE->GetCharacterResource(ITEMDB->GetItem(m_vecEquipment[i])->szTexturePath, ITEMDB->GetItem(m_vecEquipment[i])->szTextureFileName)->GetAttackBone() == NULL)
			{
				TEXTURE->GetCharacterResource(ITEMDB->GetItem(m_vecEquipment[i])->szTexturePath,
					ITEMDB->GetItem(m_vecEquipment[i])->szTextureFileName)->FindAttackBone(ITEMDB->GetItem(m_vecEquipment[i])->szColliderBoneName);
			}
		}
		else if (ITEMDB->GetItem(m_vecEquipment[i])->eMiddleID == I_M_BOW ||
			ITEMDB->GetItem(m_vecEquipment[i])->eMiddleID == I_M_SHIELD)
		{
			m_LeftWeaponMesh = TEXTURE->GetCharacterResource(ITEMDB->GetItem(m_vecEquipment[i])->szTexturePath, ITEMDB->GetItem(m_vecEquipment[i])->szTextureFileName);
			if (TEXTURE->GetCharacterResource(ITEMDB->GetItem(m_vecEquipment[i])->szTexturePath, ITEMDB->GetItem(m_vecEquipment[i])->szTextureFileName)->GetAttackBone() == NULL)
			{
				TEXTURE->GetCharacterResource(ITEMDB->GetItem(m_vecEquipment[i])->szTexturePath,
					ITEMDB->GetItem(m_vecEquipment[i])->szTextureFileName)->FindAttackBone(ITEMDB->GetItem(m_vecEquipment[i])->szColliderBoneName);
			}

			if (ITEMDB->GetItem(m_vecEquipment[i])->eMiddleID == I_M_BOW)
			{
				m_AttackType = ATTACK_BOW;
			}
		}
	}

}

void cPlayer::UnEquip()
{
	m_AttackType = ATTACK_MELEE;
	m_RightWeaponMesh = NULL;
	m_LeftWeaponMesh = NULL;
}


void cPlayer::SetAttackColliderPos()
{
	/*if (m_RightWeaponMesh == NULL&&m_LeftWeaponMesh == NULL)
	{
		m_AttackCollideSphere.vCenter = D3DXVECTOR3(0, 0, 0);
		D3DXVec3TransformCoord(&m_AttackCollideSphere.vCenter, &m_AttackCollideSphere.vCenter, &m_rightHand->CombinedTransformationMatrix);
	}
	else if (m_RightWeaponMesh != NULL)
	{
		m_AttackCollideSphere.vCenter = D3DXVECTOR3(0, 0, 0);
		D3DXVec3TransformCoord(&m_AttackCollideSphere.vCenter, &m_AttackCollideSphere.vCenter, &m_RightWeaponMesh->GetAttackBoneMat());
	}
	else if (m_LeftWeaponMesh != NULL&&m_RightWeaponMesh == NULL)
	{
		m_AttackCollideSphere.vCenter = D3DXVECTOR3(0, 0, 0);
		D3DXVec3TransformCoord(&m_AttackCollideSphere.vCenter, &m_AttackCollideSphere.vCenter, &m_LeftWeaponMesh->GetAttackBoneMat());
	}*/
}


bool cPlayer::AddUnitInTown(C_C_ID ID)
{
	switch (ID)
	{
	case C_C_HUMAN_MELEE:case C_C_ORC_MELEE:if (m_mapLeader[LEADER_MELEE]->AddUnitInTown(ID))return true; break;
	case C_C_HUMAN_BOWMAN:case C_C_ORC_BOWMAN: if (m_mapLeader[LEADER_BOW]->AddUnitInTown(ID))return true;  break;
	case C_C_HUMAN_CAVALRY:case C_C_ORC_CAVALRY: if (m_mapLeader[LEADER_CAVALRY]->AddUnitInTown(ID))return true;  break;
	}
	return false;
}

int cPlayer::GetAllUnitSize()
{
	return ((m_mapLeader[LEADER_MELEE]->GetUnits().size() * 10000)
		+ (m_mapLeader[LEADER_BOW]->GetUnits().size() * 100)
		+ (m_mapLeader[LEADER_CAVALRY]->GetUnits().size()));
}
