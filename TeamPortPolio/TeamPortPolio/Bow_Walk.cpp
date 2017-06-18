#include "stdafx.h"
#include "Bow_State.h"

void Bow_Walk::OnBegin(cBowUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(B_BATTLEWALK);
}

void Bow_Walk::OnUpdate(cBowUnit * pUnit, float deltaTime)
{
	StateChanger(pUnit);
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(pUnit->GetOffset(), pUnit->GetLeader()->Forward());
	D3DXVECTOR3 targetPos = pUnit->GetLeader()->Pos() + worldOffset;

	D3DXVECTOR3 vTotarget = pUnit->GetCharacterEntity()->Pos() - targetPos;
	vTotarget.y = 0;
	float distance = MATH->Magnitude(vTotarget);

	if (distance > 0.1f)
	{
		pUnit->GetCharacterEntity()->Steering()->OffsetPursuit(pUnit->GetLeader(), pUnit->GetOffset());
		pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());

	}
	else
	{
		pUnit->GetCharacterEntity()->SetForward(pUnit->GetLeader()->Forward());
		pUnit->FSM()->Play(UNIT_STATE_BOW_IDLE);
	}



}

void Bow_Walk::OnEnd(cBowUnit * pUnit)
{
}

void Bow_Walk::StateChanger(cBowUnit * pUnit)
{
	if (pUnit->GetMesh()->GetIndex() != FG_BATTLEWALK&&0.002f <= pUnit->GetCharacterEntity()->Speed() && pUnit->GetCharacterEntity()->Speed() <= 0.05f)
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(FG_BATTLEWALK);
	}
	else if (pUnit->GetMesh()->GetIndex() != FG_BATTLERUN&&0.05f < pUnit->GetCharacterEntity()->Speed())
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(FG_BATTLERUN);
	}/*
	 else if (pUnit->GetMesh()->Getindex() != F_READYATTACK&&pUnit->GetCharacterEntity()->Speed() < 0.005f)
	 {
	 pUnit->GetMesh()->SetAnimationIndexBlend(F_READYATTACK);
	 }*/
}
