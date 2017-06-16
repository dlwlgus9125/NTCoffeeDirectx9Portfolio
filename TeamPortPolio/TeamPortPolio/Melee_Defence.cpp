#include "stdafx.h"
#include "Melee_State.h"

void Melee_Defence::OnBegin(cMeleeUnit * pUnit)
{
	((cMeleeUnit*)pUnit)->GetMesh()->SetAnimationIndexBlend(FG_SHEILDUP);
	((cMeleeUnit*)pUnit)->GetStatus()->SetDefence(8);
}

void Melee_Defence::OnUpdate(cMeleeUnit * pUnit, float deltaTime)
{
	
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(((cMeleeUnit*)pUnit)->GetOffset(), ((cMeleeUnit*)pUnit)->GetLeader()->Forward());
	D3DXVECTOR3 targetPos = ((cMeleeUnit*)pUnit)->GetLeader()->Pos() + worldOffset;

	targetPos.y = 0;
	D3DXVECTOR3 pos = ((cMeleeUnit*)pUnit)->GetCharacterEntity()->Pos();
	pos.y = 0;
	float distance = MATH->Distance(pos, targetPos);

	if (distance > 0.1f)
	{
		((cMeleeUnit*)pUnit)->GetCharacterEntity()->Steering()->OffsetPursuit(((cMeleeUnit*)pUnit)->GetLeader(), ((cMeleeUnit*)pUnit)->GetOffset());
		((cMeleeUnit*)pUnit)->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());
		((cMeleeUnit*)pUnit)->GetMesh()->SetAnimationIndexBlend(FG_BATTLEWALK);
	}
	else
	{
		((cMeleeUnit*)pUnit)->GetMesh()->SetAnimationIndexBlend(FG_SHEILDUP);
		((cMeleeUnit*)pUnit)->GetCharacterEntity()->SetForward(pUnit->GetLeader()->Forward());
	}
}

void Melee_Defence::OnEnd(cMeleeUnit * pUnit)
{
	((cMeleeUnit*)pUnit)->GetStatus()->SetDefence(2);
}
