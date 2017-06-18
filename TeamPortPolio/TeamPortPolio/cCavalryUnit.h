#pragma once
#include "cUnit.h"
#include "Cavalry_State.h"

class cCavalryUnit :
	public cUnit
{
protected:


	cStateMachine<cCavalryUnit*>* m_pFsm;

	//자신을 겨누고있는 최대 적의 수를 파악
public:
	cCavalryUnit(IEntity* pLeader, D3DXVECTOR3 offset);
	~cCavalryUnit();

	void Init();
	void Update(float deltaTime);
	void Render();

	cStateMachine<cCavalryUnit*>* FSM() { return m_pFsm; };

	void SetAnimBlock() { };
	void SetAnimHit() { m_pSkinnedMesh->SetAnimationIndexBlend(K_HIT); };

	void SetAnimDeath() { m_pFsm->Play(UNIT_STATE_CAVALRY_DEATH); };
	void SetBattleState() { m_pFsm->Play(UNIT_STATE_CAVALRY_BATTLE); };
	void SetIdleState() { m_pFsm->Play(UNIT_STATE_CAVALRY_IDLE); };
	void SetDefenceState() {  };
};

