#include "stdafx.h"
#include "Leader_State.h"
#include "cObjectManager.h"


void Leader_State_Melee_Defence::OnBegin(cLeader * pLeader)
{
	for (int i = 0; i < pLeader->GetUnits().size(); i++)
	{
		if (((cMeleeUnit*)pLeader->GetUnits()[i])->IsDeath() == false)((cMeleeUnit*)pLeader->GetUnits()[i])->FSM()->Play(UNIT_STATE_MELEE_DEFENCE);
	}
}

void Leader_State_Melee_Defence::OnUpdate(cLeader * pLeader, float deltaTime)
{

}

void Leader_State_Melee_Defence::OnEnd(cLeader * pLeader)
{
	for (int i = 0; i < pLeader->GetUnits().size(); i++)
	{
		if (((cMeleeUnit*)pLeader->GetUnits()[i])->IsDeath() == false)((cMeleeUnit*)pLeader->GetUnits()[i])->FSM()->Play(UNIT_STATE_MELEE_IDLE);
	}
}
