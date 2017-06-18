#pragma once
#include "cUnit.h"
#include "Melee_State.h"

class cMeleeUnit :
	public cUnit
{
protected:
	

	cStateMachine<cMeleeUnit*>* m_pFsm;

	//자신을 겨누고있는 최대 적의 수를 파악
public:
	cMeleeUnit(IEntity* pLeader, D3DXVECTOR3 offset);
	~cMeleeUnit();
	
	void Init();
	void Update(float deltaTime);
	void Render();

	cStateMachine<cMeleeUnit*>* FSM() { return m_pFsm; };

	void SetAnimBlock() { m_pSkinnedMesh->SetAnimationIndexBlend(FG_SHEILDBLOCK); };
	void SetAnimHit() { m_pSkinnedMesh->SetAnimationIndexBlend(FG_HIT); };
	void SetAnimDeath() { m_pFsm->Play(UNIT_STATE_MELEE_DEATH); };

	void SetBattleState() { m_pFsm->Play(UNIT_STATE_MELEE_BATTLE); };
	void SetIdleState() { m_pFsm->Play(UNIT_STATE_MELEE_IDLE); };
	void SetDefenceState() { m_pFsm->Play(UNIT_STATE_MELEE_DEFENCE); };
};

