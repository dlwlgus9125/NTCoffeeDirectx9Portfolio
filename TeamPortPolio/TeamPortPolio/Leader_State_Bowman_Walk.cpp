#include "stdafx.h"
#include "Leader_State.h"

void Leader_State_Bowman_Walk::OnBegin(cLeader * pLeader)
{
	for (int i = 0; i < pLeader->GetUnits().size(); i++)
	{
		if (pLeader->GetUnits()[i]->IsDeath() == false)pLeader->GetUnits()[i]->SetIdleState();
	}
}

void Leader_State_Bowman_Walk::OnUpdate(cLeader * pLeader, float deltaTime)
{
	if (pLeader->GetPath().size() > 0)
	{
		D3DXVECTOR3 LeaderPos = pLeader->GetCharacterEntity()->Pos();
		D3DXVECTOR3 targetPos = ASTAR->GetGraph()->GetNode(pLeader->GetPath().back())->Pos();
		//targetPos.y = 0;
		//LeaderPos.y = 0;

		float distance = MATH->Distance(LeaderPos, targetPos);

		if (distance > 0.1f)
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
		pLeader->FSM()->Play(LEADER_STATE_BOW_IDLE);
	}

}

void Leader_State_Bowman_Walk::OnEnd(cLeader * pLeader)
{
}
