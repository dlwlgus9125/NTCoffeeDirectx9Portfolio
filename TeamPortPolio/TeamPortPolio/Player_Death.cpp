#include "stdafx.h"
#include "Player_State.h"


void Player_Death::OnBegin(cPlayer* pPlayer)
{
	pPlayer->GetMesh()->SetAnimationIndexBlend(P_DEATH);
	pPlayer->GetCharacterEntity()->SetDeath(true);
	if (CHARACTERDB->GetMapCharacter(pPlayer->GetID())->m_raceID == C_R_HUMAN)
	{
		SOUND->Play("HumanDeath");
	}
	else
	{
		SOUND->Play("OrcDeath");
	}
}

void Player_Death::OnUpdate(cPlayer* pPlayer, float deltaTime)
{
	if (pPlayer->IsDeath() == false && pPlayer->GetMesh()->GetPassedTime() > pPlayer->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.3f)
	{
		pPlayer->SetDeath(true);
	}
}

void Player_Death::OnEnd(cPlayer* pPlayer)
{

}
