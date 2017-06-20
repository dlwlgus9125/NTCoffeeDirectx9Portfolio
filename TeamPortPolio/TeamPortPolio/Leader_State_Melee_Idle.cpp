#include "stdafx.h"
#include "Leader_State.h"



void Leader_State_Melee_Idle::OnBegin(cLeader * pLeader)
{
	for (int i = 0; i < pLeader->GetUnits().size(); i++)
	{
		if (pLeader->GetUnits()[i]->IsDeath() != true)pLeader->GetUnits()[i]->SetIdleState();
	}
}

void Leader_State_Melee_Idle::OnUpdate(cLeader * pLeader, float deltaTime)
{
	if (pLeader->GetTargetObject()!=NULL&&pLeader->GetTargetObject()->GetCharacterEntity()->IsDeath()==false)
	{
		pLeader->FSM()->Play(LEADER_STATE_MELEE_BATTLE);
	}
	else if (pLeader->GetPath().size() > 0)
	{
		pLeader->FSM()->Play(LEADER_STATE_MELEE_WALK);
	}/*
	else
	{
		for (int i = 0; i < pLeader->GetUnits().size(); i++)
		{
			if (pLeader->GetUnits()[i]->IsDeath() != true&& pLeader->GetUnits()[i]->GetMesh()->GetIndex()!= FG_READYATTACK)pLeader->GetUnits()[i]->SetIdleState();
		}
	}*/
}

void Leader_State_Melee_Idle::OnEnd(cLeader * pUnit)
{
}
