#include "stdafx.h"
#include "cCavalryUnit.h"
#include "cCavalryUnit.h"



cCavalryUnit::cCavalryUnit(IEntity * pLeader, D3DXVECTOR3 offset) :cUnit::cUnit()
{
	m_CharacterEntity = new ISteeringEntity(pLeader->Pos(), 0.5f,
		pLeader->Forward(), pLeader->Mass(), pLeader->MaxSpeed() * 3);
	m_pLeader = pLeader;
	m_offset = offset;
}

cCavalryUnit::~cCavalryUnit()
{
	SAFE_DELETE(m_pFsm);
}

void cCavalryUnit::Init()
{
	m_CollideSphere.fRadius = 1.0f;
	m_CollideSphere.vCenter = m_CharacterEntity->Pos();

	m_arrangeCollideSphere.fRadius = 15.0f;
	m_arrangeCollideSphere.vCenter = m_CharacterEntity->Pos();
	cUnit::Init();



	m_pSkinnedMesh->FindAttackBone(m_Status->m_szColliderBoneName);
	m_pFsm = new cStateMachine<cCavalryUnit*>(this);
	m_pFsm->Register(UNIT_STATE_CAVALRY_IDLE, new Cavalry_Idle());
	m_pFsm->Register(UNIT_STATE_CAVALRY_WALK, new Cavalry_Walk());
	m_pFsm->Register(UNIT_STATE_CAVALRY_BATTLE, new Cavalry_Battle());
	m_pFsm->Register(UNIT_STATE_CAVALRY_DEATH, new Cavalry_Death());
	m_pFsm->Play(UNIT_STATE_CAVALRY_IDLE);
}

void cCavalryUnit::Update(float deltaTime)
{
	if (m_isDeath == false)
	{
		cUnit::Update(deltaTime);
		m_pFsm->Update(deltaTime);
		D3DXVECTOR3 pos = m_CharacterEntity->Pos();
		MAP->GetHeight(pos.x, pos.y, pos.z);
		m_CharacterEntity->SetPos(pos);
		m_pSkinnedMesh->SetPosition(m_CharacterEntity->Pos(), m_CharacterEntity->Forward());

		//if (MATH->IsCollided(OBJECT->GetPlayer()->GetSphere(), m_arrangeCollideSphere&&this->GetLeader()->)
		//{
		//	//battleT
		//}
	}
}

void cCavalryUnit::Render()
{
	cUnit::Render();
	if (FRUSTUM->IsIn(m_pSkinnedMesh->GetBoundingSphere()))
	{
		m_pSkinnedMesh->UpdateAndRender(m_isDeath);
	}
}
