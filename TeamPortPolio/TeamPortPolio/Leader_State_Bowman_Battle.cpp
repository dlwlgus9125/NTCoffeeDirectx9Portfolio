#include "stdafx.h"
#include "Leader_State.h"

void Leader_State_Bowman_Battle::OnBegin(cLeader * pLeader)
{
	for (int i = 0; i < pLeader->GetUnits().size(); i++)
	{
		if (pLeader->GetUnits()[i]->IsDeath() != true)
		{
			//pLeader->GetUnits()[i]->SetTargetObject(pLeader->GetTargetObject());
			pLeader->GetUnits()[i]->SetBattleState();
		}
	}
}

void Leader_State_Bowman_Battle::OnUpdate(cLeader * pLeader, float deltaTime)
{
	if ((pLeader->GetTargetObject()!=NULL&&!MATH->IsCollided(pLeader->GetArrangeSphere(), ((cLeader*)pLeader->GetTargetObject())->GetArrangeSphere())))
	{
		/*pLeader->FSM()->Play(LEADER_STATE_BOW_IDLE);*/
		//pLeader->SetTargetObject(NULL);
		
	}
	

	//if (TIME->UpdateOneSecond()&&pLeader->GetTargetObject() != NULL&& ((cCharacter*)pLeader->GetTargetObject())->IsDeath() != true)
	//{
	//	for (int i = 0; i < pLeader->GetUnits().size(); i++)
	//	{
	//		if (pLeader->GetUnits()[i]->IsDeath() != true)
	//		{
	//			if(pLeader->GetUnits()[i]->GetTargetObject()==NULL)pLeader->GetUnits()[i]->SetTargetObject(pLeader->GetTargetObject());
	//			//pLeader->GetUnits()[i]->SetBattleState();
	//		}
	//	}
	//}
	if (pLeader->GetTargetObject() != NULL && ((cCharacter*)pLeader->GetTargetObject())->IsDeath() == true)
	{
		for (int i = 0; i < pLeader->GetUnits().size(); i++)
		{
			if (pLeader->GetUnits()[i]->IsDeath() != true)
			{
				pLeader->GetUnits()[i]->SetTargetObject(NULL);
				//pLeader->GetUnits()[i]->SetBattleState();
			}
		}
	}
}

void Leader_State_Bowman_Battle::OnEnd(cLeader * pLeader)
{
	pLeader->SetIndex(pLeader->GetIndex());
	pLeader->PathClear();

	for (int i = 0; i < pLeader->GetUnits().size(); i++)
	{
		if (pLeader->GetUnits()[i]->IsDeath() != true)
		{
			pLeader->GetUnits()[i]->SetIdleState();
		}
	}
}
