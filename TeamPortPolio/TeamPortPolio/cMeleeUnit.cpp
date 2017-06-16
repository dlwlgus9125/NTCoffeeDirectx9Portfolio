#include "stdafx.h"
#include "cMeleeUnit.h"
#include "cPlayer.h"



cMeleeUnit::cMeleeUnit(IEntity * pLeader, D3DXVECTOR3 offset) :cUnit::cUnit()
{
	m_CharacterEntity = new ISteeringEntity(pLeader->Pos(), 0.5f,
		pLeader->Forward(), pLeader->Mass(), pLeader->MaxSpeed() * 3);
	m_pLeader = pLeader;
	m_offset = offset;
}

cMeleeUnit::~cMeleeUnit()
{
	SAFE_DELETE(m_pFsm);
}

void cMeleeUnit::Init()
{
	m_CollideSphere.fRadius = 1.0f;
	m_CollideSphere.vCenter = m_CharacterEntity->Pos();

	m_arrangeCollideSphere.fRadius = 15.0f;
	m_arrangeCollideSphere.vCenter = m_CharacterEntity->Pos();
	cUnit::Init();

	

	m_pSkinnedMesh->FindAttackBone(m_Status->m_szColliderBoneName);
	m_pFsm = new cStateMachine<cMeleeUnit*>(this);
	m_pFsm->Register(UNIT_STATE_MELEE_IDLE, new Melee_Idle());
	m_pFsm->Register(UNIT_STATE_MELEE_WALK, new Melee_Walk());
	m_pFsm->Register(UNIT_STATE_MELEE_BATTLE, new Melee_Battle());
	m_pFsm->Register(UNIT_STATE_MELEE_DEFENCE, new Melee_Defence());
	m_pFsm->Register(UNIT_STATE_MELEE_DEATH, new Melee_Death());
	m_pFsm->Play(UNIT_STATE_MELEE_IDLE);
}

void cMeleeUnit::Update(float deltaTime)
{
	if (m_isDeath == false)
	{
		cUnit::Update(deltaTime);
		m_pFsm->Update(deltaTime);
		D3DXVECTOR3 pos = m_CharacterEntity->Pos();
		MAP->GetHeight(pos.x, pos.y, pos.z);
		m_CharacterEntity->SetPos(pos);
		m_pSkinnedMesh->SetPosition(m_CharacterEntity->Pos(), m_CharacterEntity->Forward());

		//if (MATH->IsCollided(OBJECT->GetPlayer()->GetSphere(), m_arrangeCollideSphere)
		//{
		//	//battleT
		//}
	}
}

void cMeleeUnit::Render()
{
	cUnit::Render();
	
}
