#include "stdafx.h"
#include "cBowUnit.h"
#include "cPlayer.h"



cBowUnit::cBowUnit(IEntity * pLeader, D3DXVECTOR3 offset) :cUnit::cUnit()
{
	m_CharacterEntity = new ISteeringEntity(pLeader->Pos(), 0.5f,
		pLeader->Forward(), pLeader->Mass(), pLeader->MaxSpeed() * 3);
	m_pLeader = pLeader;
	m_offset = offset;
}

cBowUnit::~cBowUnit()
{
	SAFE_DELETE(m_pFsm);
}

void cBowUnit::Init()
{
	m_CollideSphere.fRadius = 1.0f;
	m_CollideSphere.vCenter = m_CharacterEntity->Pos();

	m_arrangeCollideSphere.fRadius = 25.0f;
	m_arrangeCollideSphere.vCenter = m_CharacterEntity->Pos();
	cUnit::Init();



	m_pSkinnedMesh->FindAttackBone(m_Status->m_szColliderBoneName);
	m_pFsm = new cStateMachine<cBowUnit*>(this);
	m_pFsm->Register(UNIT_STATE_BOW_IDLE, new Bow_Idle());
	m_pFsm->Register(UNIT_STATE_BOW_WALK, new Bow_Walk());
	m_pFsm->Register(UNIT_STATE_BOW_BATTLE, new Bow_Battle());
	m_pFsm->Register(UNIT_STATE_BOW_DEATH, new Bow_Death());
	m_pFsm->Play(UNIT_STATE_BOW_IDLE);
}

void cBowUnit::Update(float deltaTime)
{
	if (m_isDeath == false)
	{
		cUnit::Update(deltaTime);
		m_pFsm->Update(deltaTime);
		D3DXVECTOR3 pos = m_CharacterEntity->Pos();
		MAP->GetHeight(pos.x, pos.y, pos.z);
		m_CharacterEntity->SetPos(pos);
		m_pSkinnedMesh->SetPosition(m_CharacterEntity->Pos(), m_CharacterEntity->Forward());


		if (GetTargetObject() == NULL&&m_camp != CAMP_PLAYER&&MATH->IsCollided(OBJECT->GetPlayer()->GetArrangeSphere(), m_arrangeCollideSphere))
		{
			SetTargetObject(OBJECT->GetPlayer());
			m_pFsm->Play(UNIT_STATE_BOW_BATTLE);
		}
		//if (MATH->IsCollided(OBJECT->GetPlayer()->GetSphere(), m_arrangeCollideSphere&&this->GetLeader()->)
		//{
		//	//battleT
		//}
	}
}

void cBowUnit::Render()
{
	cUnit::Render();
	if (FRUSTUM->IsIn(m_pSkinnedMesh->GetBoundingSphere()))
	{
		m_pSkinnedMesh->UpdateAndRender(m_isDeath);
	}
}
