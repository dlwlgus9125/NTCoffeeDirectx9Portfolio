#include "stdafx.h"
#include "Melee_State.h"


void Melee_Death::OnBegin(cMeleeUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(FG_DEATH);
	pUnit->GetCharacterEntity()->SetDeath(true);
	if (CHARACTERDB->GetMapCharacter(pUnit->GetID())->m_raceID == C_R_HUMAN)
	{
		SOUND->Play("HumanDeath");
	}
	else
	{
		SOUND->Play("OrcDeath");
	}
}

void Melee_Death::OnUpdate(cMeleeUnit * pUnit, float deltaTime)
{
	if (pUnit->IsDeath()==false&& pUnit->GetMesh()->GetPassedTime() > pUnit->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.3f)
	{
		pUnit->SetDeath(true);
	}
}

void Melee_Death::OnEnd(cMeleeUnit * pUnit)
{
}
