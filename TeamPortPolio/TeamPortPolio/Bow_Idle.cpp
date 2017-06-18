#include "stdafx.h"
#include "Bow_State.h"

void Bow_Idle::OnBegin(cBowUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(B_READYATTACK);
}

void Bow_Idle::OnUpdate(cBowUnit * pUnit, float deltaTime)
{
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(pUnit->GetOffset(), pUnit->GetLeader()->Forward());
	D3DXVECTOR3 targetPos = pUnit->GetLeader()->Pos() + worldOffset;

	D3DXVECTOR3 vTotarget = pUnit->GetCharacterEntity()->Pos() - targetPos;
	vTotarget.y = 0;

	float distance = MATH->Magnitude(vTotarget);
	if (distance > 0.1f)
	{
		pUnit->FSM()->Play(UNIT_STATE_BOW_WALK);
	}
	else
	{
		pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());
		switch (pUnit->GetMode())
		{
		case FIGHTING_MODE: pUnit->GetMesh()->SetAnimationIndexBlend(B_READYATTACK); break;
		case DEFENDING_MODE:pUnit->GetMesh()->SetAnimationIndexBlend(B_STAND); break;
		}

	}
	D3DXVECTOR3 pos;
	float x = -50;
	float x2 = 50;

}

void Bow_Idle::OnEnd(cBowUnit * pUnit)
{
}
