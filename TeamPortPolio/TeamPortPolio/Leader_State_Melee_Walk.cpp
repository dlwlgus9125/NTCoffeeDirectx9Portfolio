#include "stdafx.h"
#include "Leader_State.h"



void Leader_State_Melee_Walk::OnBegin(cLeader * pUnit)
{
}

void Leader_State_Melee_Walk::OnUpdate(cLeader * pLeader, float deltaTime)
{
	if (pLeader->GetTargetObject() != NULL)
	{
		pLeader->SetTargetIndex(((cCharacter*)pLeader->GetTargetObject())->GetIndex());
		pLeader->FSM()->Play(LEADER_STATE_MELEE_BATTLE);
	}
	else if (pLeader->GetPath().size() > 0)
	{
		D3DXVECTOR3 LeaderPos = pLeader->GetCharacterEntity()->Pos();
		D3DXVECTOR3 targetPos = ASTAR->GetGraph()->GetNode(pLeader->GetPath().back())->Pos();

		float distance = MATH->Distance(LeaderPos, targetPos);

		if (distance > 0.01f)
		{

			pLeader->GetCharacterEntity()->Steering()->LeaderArrive(targetPos);

			if (MATH->IsCollided(pLeader->GetSphere(), ASTAR->GetGraph()->GetNode(pLeader->GetPath().back())->GetSphere()))
			{
				pLeader->PathPopBack();
			}
		}

	}
	else if (MATH->IsCollided(pLeader->GetSphere(), ASTAR->GetGraph()->GetNode(pLeader->GetTargetIndex())->GetSphere()))
	{
		pLeader->PathClear();
		cout << "clear!" << endl;
		pLeader->FSM()->Play(LEADER_STATE_MELEE_IDLE);
	}


}

void Leader_State_Melee_Walk::OnEnd(cLeader * pUnit)
{
}

void Leader_State_Melee_Walk::StateChanger(cLeader * pUnit)
{
}
