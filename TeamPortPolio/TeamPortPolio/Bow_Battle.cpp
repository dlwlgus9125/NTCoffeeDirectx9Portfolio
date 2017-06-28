#include "stdafx.h"
#include "Bow_State.h"
#include "cBallisticArrow.h"

void Bow_Battle::OnBegin(cBowUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(B_READYATTACK);
	if (SOUND->FindChannel("PullBow") == NULL)SOUND->Play("PullBow", 2.0f);
}

void Bow_Battle::OnUpdate(cBowUnit * pUnit, float deltaTime)
{
	FindNearTarget(pUnit);
	if (pUnit->GetTargetObject() != NULL)
	{
		if (pUnit->GetMesh()->GetPassedTime() > pUnit->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.3f)
		{
			switch (pUnit->GetMesh()->GetIndex())
			{
			case B_BOWATTACK1:
				pUnit->GetMesh()->SetAnimationIndexBlend(B_BOWATTACK2);
				OBJECT->AddUnitArrow(pUnit->GetCharacterEntity()->Pos() , pUnit->GetTargetObject()->GetCharacterEntity()->Pos(), pUnit->GetCamp());
				if (SOUND->FindChannel("ShootBow") == NULL)SOUND->Play("ShootBow", 2.0f);
				break;
			default:
				pUnit->GetMesh()->SetAnimationIndexBlend(B_BOWATTACK1);
				if (SOUND->FindChannel("PullBow") == NULL)SOUND->Play("PullBow", 2.0f);
				break;
			}
		}
	}
	else//거리로 계산해서 못쏘게 해야할 듯함
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(B_READYATTACK);
		
	}
}

void Bow_Battle::OnEnd(cBowUnit * pUnit)
{
	pUnit->SetTargetObject(NULL);
}

void Bow_Battle::FindNearTarget(cBowUnit * pUnit)
{
	if (TIME->UpdateOneSecond())
	{
		D3DXVECTOR3 nextTargetPos, prevTargetPos;
		D3DXVECTOR3 pos = pUnit->GetCharacterEntity()->Pos();
		if (OBJECT->GetCharacter()[0]->GetCharacterEntity()->IsDeath() == false && OBJECT->GetCharacter()[0]->GetCamp() != pUnit->GetCamp() && MATH->IsCollided(pUnit->GetArrangeSphere(), OBJECT->GetCharacter()[0]->GetArrangeSphere()))
		{
			pUnit->SetTargetObject(OBJECT->GetCharacter()[0]);
		}

		for (int i = 1; i < OBJECT->GetCharacter().size(); i++)
		{
			if (OBJECT->GetCharacter()[i]->GetCharacterEntity()->IsDeath() == false && OBJECT->GetCharacter()[i]->GetCamp() != pUnit->GetCamp() && MATH->IsCollided(pUnit->GetArrangeSphere(), OBJECT->GetCharacter()[i]->GetArrangeSphere()))
			{
				prevTargetPos = OBJECT->GetCharacter()[i - 1]->GetCharacterEntity()->Pos();
				nextTargetPos = OBJECT->GetCharacter()[i]->GetCharacterEntity()->Pos();

				if (MATH->Distance(pos, prevTargetPos) > MATH->Distance(pos, nextTargetPos))
				{
					pUnit->SetTargetObject(OBJECT->GetCharacter()[i]);
				}
				else
				{
					pUnit->SetTargetObject(OBJECT->GetCharacter()[i - 1]);
				}
			}
		}
	}
}
