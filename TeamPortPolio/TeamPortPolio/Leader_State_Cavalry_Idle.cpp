#include "stdafx.h"
#include "Leader_State.h"

void Leader_State_Cavalry_Idle::OnBegin(cLeader * pLeader)
{
	for (int i = 0; i < pLeader->GetUnits().size(); i++)
	{
		if (pLeader->GetUnits()[i]->IsDeath() == false)pLeader->GetUnits()[i]->SetIdleState();
	}
}

void Leader_State_Cavalry_Idle::OnUpdate(cLeader * pLeader, float deltaTime)
{
	if (pLeader->GetPath().size() > 0)
	{
		pLeader->FSM()->Play(LEADER_STATE_CAVALRY_WALK);
	}
}

void Leader_State_Cavalry_Idle::OnEnd(cLeader * pLeader)
{
}
