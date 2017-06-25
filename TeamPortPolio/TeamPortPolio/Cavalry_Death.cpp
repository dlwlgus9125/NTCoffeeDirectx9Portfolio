#include "stdafx.h"
#include "Cavalry_State.h"


void Cavalry_Death::OnBegin(cCavalryUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(K_DEATH);
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

void Cavalry_Death::OnUpdate(cCavalryUnit * pUnit, float deltaTime)
{
	if (pUnit->IsDeath() == false && pUnit->GetMesh()->GetPassedTime() > pUnit->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.3f)
	{
		pUnit->SetDeath(true);
	}
}

void Cavalry_Death::OnEnd(cCavalryUnit * pUnit)
{
}
