#include "stdafx.h"
#include "Melee_State.h"

void Melee_Idle::OnBegin(cMeleeUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(FG_READYATTACK);
}

void Melee_Idle::OnUpdate(cMeleeUnit * pUnit, float deltaTime)
{
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(pUnit->GetOffset(), pUnit->GetLeader()->Forward());
	D3DXVECTOR3 targetPos = pUnit->GetLeader()->Pos() + worldOffset;
	
	D3DXVECTOR3 vTotarget = pUnit->GetCharacterEntity()->Pos() - targetPos;
	vTotarget.y = 0;

	float distance = MATH->Magnitude(vTotarget);
	if (distance > 0.1f)
	{
		pUnit->FSM()->Play(UNIT_STATE_MELEE_WALK);
	}
	else
	{
		pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());
		switch (pUnit->GetMode())
		{
		case FIGHTING_MODE: pUnit->GetMesh()->SetAnimationIndexBlend(FG_READYATTACK); break;
		case DEFENDING_MODE:pUnit->GetMesh()->SetAnimationIndexBlend(FG_STAND); break;
		}

	}
	D3DXVECTOR3 pos;
	float x = -50;
	float x2 = 50;

}

void Melee_Idle::OnEnd(cMeleeUnit * pUnit)
{
}
