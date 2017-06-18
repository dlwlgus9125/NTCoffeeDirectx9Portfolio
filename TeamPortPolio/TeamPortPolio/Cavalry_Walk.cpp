#include "stdafx.h"
#include "Cavalry_State.h"

void Cavalry_Walk::OnBegin(cCavalryUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(K_WALK);
}

void Cavalry_Walk::OnUpdate(cCavalryUnit * pUnit, float deltaTime)
{
	StateChanger(pUnit);
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(pUnit->GetOffset(), pUnit->GetLeader()->Forward());
	D3DXVECTOR3 targetPos = pUnit->GetLeader()->Pos() + worldOffset;

	D3DXVECTOR3 vTotarget = pUnit->GetCharacterEntity()->Pos() - targetPos;
	vTotarget.y = 0;
	float distance = MATH->Magnitude(vTotarget);

	if (distance > 0.1f)
	{
		pUnit->GetCharacterEntity()->Steering()->CavalryOffsetPursuit(pUnit->GetLeader(), pUnit->GetOffset());
		pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());

	}
	else
	{
		pUnit->GetCharacterEntity()->SetForward(pUnit->GetLeader()->Forward());
		pUnit->FSM()->Play(UNIT_STATE_CAVALRY_IDLE);
	}



}

void Cavalry_Walk::OnEnd(cCavalryUnit * pUnit)
{
}

void Cavalry_Walk::StateChanger(cCavalryUnit * pUnit)
{
	if (pUnit->GetMesh()->GetIndex() != K_WALK&&0.002f <= pUnit->GetCharacterEntity()->Speed() && pUnit->GetCharacterEntity()->Speed() <= 0.05f)
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(K_WALK);
	}
	else if (pUnit->GetMesh()->GetIndex() != K_RUN&&0.05f < pUnit->GetCharacterEntity()->Speed())
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(K_RUN);
	}/*
	 else if (pUnit->GetMesh()->Getindex() != F_READYATTACK&&pUnit->GetCharacterEntity()->Speed() < 0.005f)
	 {
	 pUnit->GetMesh()->SetAnimationIndexBlend(F_READYATTACK);
	 }*/
}
