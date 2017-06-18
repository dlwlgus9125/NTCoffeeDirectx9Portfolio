#include "stdafx.h"
#include "Melee_State.h"

void Melee_Defence::OnBegin(cMeleeUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(FG_SHEILDUP);
	pUnit->GetStatus()->SetDefence(8);
}

void Melee_Defence::OnUpdate(cMeleeUnit * pUnit, float deltaTime)
{
	
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(pUnit->GetOffset(), pUnit->GetLeader()->Forward());
	D3DXVECTOR3 targetPos = pUnit->GetLeader()->Pos() + worldOffset;

	targetPos.y = 0;
	D3DXVECTOR3 pos = pUnit->GetCharacterEntity()->Pos();
	pos.y = 0;
	float distance = MATH->Distance(pos, targetPos);

	if (distance > 0.1f)
	{
		pUnit->GetCharacterEntity()->Steering()->OffsetPursuit(pUnit->GetLeader(), pUnit->GetOffset());
		pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());
		pUnit->GetMesh()->SetAnimationIndexBlend(FG_BATTLEWALK);
	}
	else
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(FG_SHEILDUP);
		pUnit->GetCharacterEntity()->SetForward(pUnit->GetLeader()->Forward());
	}
}

void Melee_Defence::OnEnd(cMeleeUnit * pUnit)
{
	pUnit->GetStatus()->SetDefence(2);
}
