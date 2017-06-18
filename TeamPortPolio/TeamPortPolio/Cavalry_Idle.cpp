#include "stdafx.h"
#include "Cavalry_State.h"

void Cavalry_Idle::OnBegin(cCavalryUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(K_STAND);
}

void Cavalry_Idle::OnUpdate(cCavalryUnit * pUnit, float deltaTime)
{
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(pUnit->GetOffset(), pUnit->GetLeader()->Forward());
	D3DXVECTOR3 targetPos = pUnit->GetLeader()->Pos() + worldOffset;

	D3DXVECTOR3 vTotarget = pUnit->GetCharacterEntity()->Pos() - targetPos;
	vTotarget.y = 0;

	float distance = MATH->Magnitude(vTotarget);
	if (distance > 0.1f)
	{
		pUnit->FSM()->Play(UNIT_STATE_CAVALRY_WALK);
	}
	else
	{
		pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());

	}
	D3DXVECTOR3 pos;
	float x = -50;
	float x2 = 50;

}

void Cavalry_Idle::OnEnd(cCavalryUnit * pUnit)
{
}
