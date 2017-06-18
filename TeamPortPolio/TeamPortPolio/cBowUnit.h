#pragma once
#include "cUnit.h"
#include "Bow_State.h"

class cBowUnit :
	public cUnit
{
protected:


	cStateMachine<cBowUnit*>* m_pFsm;

	//자신을 겨누고있는 최대 적의 수를 파악
public:
	cBowUnit(IEntity* pLeader, D3DXVECTOR3 offset);
	~cBowUnit();

	void Init();
	void Update(float deltaTime);
	void Render();

	cStateMachine<cBowUnit*>* FSM() { return m_pFsm; };

	void SetAnimBlock() { m_pSkinnedMesh->SetAnimationIndexBlend(B_BOWSHEILD); };
	void SetAnimHit() { m_pSkinnedMesh->SetAnimationIndexBlend(B_HIT); };

	void SetAnimDeath() { m_pFsm->Play(UNIT_STATE_BOW_DEATH); };
	void SetBattleState() { m_pFsm->Play(UNIT_STATE_BOW_BATTLE); };
	void SetIdleState() { m_pFsm->Play(UNIT_STATE_BOW_IDLE); };
	void SetDefenceState() {};
};

