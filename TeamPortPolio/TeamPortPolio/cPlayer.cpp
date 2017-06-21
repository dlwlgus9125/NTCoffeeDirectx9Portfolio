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
	m_unitLeader->Init();*/
	//m_unitLeader->SetTargetIndex(ASTAR->GetGraph()->GetNode(16001)->Id());
	
	m_fRotY = 0.0f;
	m_isAiming = false;
	m_AttackType = ATTACK_MELEE;
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
}

void cPlayer::Update(float deltaTime)
{
	if (INPUT->IsKeyDown(VK_SPACE))
	{
		cout << m_CharacterEntity->Pos().x << " " << m_CharacterEntity->Pos().y << " " << m_CharacterEntity->Pos().z << endl;
	}
	if (m_isDeath == true && m_isPull == false)m_isPull = true;
	if (m_isDeath == false)
	{
		cCharacter::Update(deltaTime);

		m_CollideSphere.vCenter.y += 0.5f; // 충돌판 높이값 조절
		m_pFsm->Update(deltaTime);
		D3DXVECTOR3 movePos = m_CharacterEntity->Pos();
		MAP->GetHeight(movePos.x, movePos.y, movePos.z);
		m_CharacterEntity->SetPos(movePos);
		m_MeleeCollider.vCenter = m_CharacterEntity->Pos() + (m_CharacterEntity->Forward()*0.8f);
		m_MeleeCollider.vCenter.y += 0.5f;
		if (INPUT->IsKeyPress(VK_A))
		{
			m_fRotY -= 0.03;
		}
		if (INPUT->IsKeyPress(VK_D))
		{
			m_fRotY += 0.03;
		}

		if (INPUT->IsKeyDown('1'))EquipLeftHand(1);
		if (INPUT->IsKeyDown('2'))EquipRightHand(1);
if (INPUT->IsKeyDown('3'))TestEquip();

//화살처리

D3DXMATRIXA16 matR;
D3DXVECTOR3 forward = D3DXVECTOR3(0, 0, 1);
D3DXMatrixIdentity(&matR);
D3DXMatrixRotationY(&matR, m_fRotY);

D3DXVec3TransformCoord(&forward, &forward, &matR);
m_CharacterEntity->SetForward(forward);

m_pSkinnedMesh->SetPosition(m_CharacterEntity->Pos(), m_CharacterEntity->Forward());


	}
	CAMERA->SetLookAt(m_CharacterEntity->Pos(), m_fRotY);

}

void cPlayer::Render()
{
	cCharacter::Render();
	if (FRUSTUM->IsIn(m_pSkinnedMesh->GetBoundingSphere()))
	{
		m_pSkinnedMesh->UpdateAndRender(m_isPull);

		//>>아이템착용 출력단
		if (m_RightWeaponMesh != NULL)m_RightWeaponMesh->UpdateAndRenderForItem(m_isDeath, m_rightHand->CombinedTransformationMatrix);
		if (m_LeftWeaponMesh != NULL)m_LeftWeaponMesh->UpdateAndRenderForItem(m_isPull, m_leftHand->CombinedTransformationMatrix);
		//<<


		SetAttackColliderPos();
		D3DXMATRIXA16 matT;
		D3DXMatrixIdentity(&matT);

		D3DXMatrixTranslation(&matT, m_MeleeCollider.vCenter.x, m_MeleeCollider.vCenter.y, m_MeleeCollider.vCenter.z);

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
			THREAD->TerminateThreadByKey(HANDLE_ATSTAR_FINDPATH);
			if (!THREAD->IsReCreateFindPathThread(HANDLE_ATSTAR_FINDPATH))
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
}

void cPlayer::PutOffItem(int itemSID)
{
	for (vector<int>::iterator it = m_vecEquipment.begin(); it != m_vecEquipment.end(); )
	{
		int itemMID = ITEMDB->GetItem(itemSID)->eMiddleID;
		int currrentItemMID = ITEMDB->GetItem(*it)->eMiddleID;
		if(itemMID == currrentItemMID)	it = m_vecEquipment.erase(it);
		else it++;
	}
}

void cPlayer::EquipRightHand(int itemSID)
{
	m_AttackType = ATTACK_BOW;
	m_RightWeaponMesh = NULL;
	m_LeftWeaponMesh = TEXTURE->GetCharacterResource(CHARACTERDB->GetMapCharacter(C_C_BOW_BOW)->m_szPath, CHARACTERDB->GetMapCharacter(C_C_BOW_BOW)->m_szFileName);

}

void cPlayer::TestEquip()
{
	m_AttackType = ATTACK_MELEE;
	m_RightWeaponMesh = NULL;
	m_LeftWeaponMesh = NULL;
}
void cPlayer::EquipLeftHand(int itemSID)
{
	m_AttackType = ATTACK_MELEE;
	//Add(new ST_Character(C_R_END, C_G_END, C_C_BOW_BOW, 100.0f, 100.f, 100.0f, 4, "Character/Weapon/", "WeaponBow.x", "Weapon_Attack_Bone_Col_root"));
	m_RightWeaponMesh = TEXTURE->GetCharacterResource(CHARACTERDB->GetMapCharacter(C_C_SWORD_SWORD)->m_szPath, CHARACTERDB->GetMapCharacter(C_C_SWORD_SWORD)->m_szFileName);
	m_LeftWeaponMesh = TEXTURE->GetCharacterResource(CHARACTERDB->GetMapCharacter(C_C_SHIELD_SHIELD)->m_szPath, CHARACTERDB->GetMapCharacter(C_C_SHIELD_SHIELD)->m_szFileName);
	
}

void cPlayer::SetAttackColliderPos()
{
	if (m_RightWeaponMesh == NULL&&m_LeftWeaponMesh == NULL)
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
	}
}
