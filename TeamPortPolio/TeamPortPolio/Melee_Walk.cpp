#include "stdafx.h"
#include "Melee_State.h"

void Melee_Walk::OnBegin(cMeleeUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(FG_BATTLEWALK);
}

void Melee_Walk::OnUpdate(cMeleeUnit * pUnit, float deltaTime)
{
	StateChanger(pUnit);
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(pUnit->GetOffset(), pUnit->GetLeader()->Forward());
	D3DXVECTOR3 targetPos = pUnit->GetLeader()->Pos() + worldOffset;
	
	D3DXVECTOR3 vTotarget = pUnit->GetCharacterEntity()->Pos() - targetPos;
	vTotarget.y = 0;
	float distance = MATH->Magnitude(vTotarget);

	if (distance >0.1)
	{
		pUnit->GetCharacterEntity()->Steering()->OffsetPursuit(pUnit->GetLeader(), pUnit->GetOffset());
		pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());
		
	}
	else
	{
		pUnit->GetCharacterEntity()->SetForward(pUnit->GetLeader()->Forward());		
		pUnit->FSM()->Play(UNIT_STATE_MELEE_IDLE);	
	}


	
}

void Melee_Walk::OnEnd(cMeleeUnit * pUnit)
{
}

void Melee_Walk::StateChanger(cMeleeUnit * pUnit)
{
	if (pUnit->GetMesh()->GetIndex() != FG_BATTLEWALK&& pUnit->GetCharacterEntity()->Speed() <= 0.06f)
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(FG_BATTLEWALK);
	}
	else if (pUnit->GetMesh()->GetIndex() != FG_BATTLERUN&&0.06f < pUnit->GetCharacterEntity()->Speed())
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(FG_BATTLERUN);
	}/*
	else if (pUnit->GetMesh()->Getindex() != F_READYATTACK&&pUnit->GetCharacterEntity()->Speed() < 0.005f)
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(F_READYATTACK);
	}*/
}
