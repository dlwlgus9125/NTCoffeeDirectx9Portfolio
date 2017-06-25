#include "stdafx.h"
#include "Leader_State.h"

void Leader_State_Cavalry_Battle::OnBegin(cLeader * pLeader)
{
	int index = 0;
	D3DXVECTOR3 pos = pLeader->GetCharacterEntity()->Pos();
	MAP->GetMap()->GetIndex(pos.x, pos.z, index);
	pLeader->SetIndex(index);
	pLeader->PathClear();
	for (int i = 0; i < pLeader->GetUnits().size(); i++)
	{
		if (pLeader->GetUnits()[i]->IsDeath() != true)
		{
			//pLeader->GetUnits()[i]->SetTargetObject(pLeader->GetTargetObject());
			pLeader->GetUnits()[i]->SetBattleState();
		}
	}	
}

void Leader_State_Cavalry_Battle::OnUpdate(cLeader * pLeader, float deltaTime)
{
	if (pLeader->GetIndex()!=pLeader->GetTargetIndex())
	{
		D3DXVECTOR3 LeaderPos = pLeader->GetCharacterEntity()->Pos();
		D3DXVECTOR3 targetPos = ASTAR->GetGraph()->GetNode(pLeader->GetTargetIndex())->Pos();
		//targetPos.y = 0;
		//LeaderPos.y = 0;

		float distance = MATH->Distance(LeaderPos, targetPos);

		if (distance > 0.01f)
		{
			pLeader->GetCharacterEntity()->Steering()->CavalryLeaderArrive(targetPos, pLeader->GetVelocity());
		}

		/*if (distance > 5)
		{
			pLeader->AddVelocity(-deltaTime*0.05f);
		}
		else
		{
			pLeader->AddVelocity(deltaTime*0.01f);
		}*/
	}
	//else if (MATH->IsCollided(pLeader->GetSphere(), ASTAR->GetGraph()->GetNode(pLeader->GetTargetIndex())->GetSphere()))
	//{
	//	pLeader->PathClear();
	//	cout << "clear!" << endl;
	//	pLeader->FSM()->Play(LEADER_STATE_CAVALRY_IDLE);

	//	for (int i = 0; i < pLeader->GetUnits().size(); i++)
	//	{
	//		if (pLeader->GetUnits()[i]->IsDeath() == false)pLeader->GetUnits()[i]->SetIdleState();
	//	}
	//}
}

void Leader_State_Cavalry_Battle::OnEnd(cLeader * pLeader)
{
	pLeader->SetIndex(pLeader->GetIndex());
	pLeader->PathClear();

	for (int i = 0; i < pLeader->GetUnits().size(); i++)
	{
		if (pLeader->GetUnits()[i]->IsDeath() != true)
		{
			//pLeader->GetUnits()[i]->SetTargetObject(pLeader->GetTargetObject());
			pLeader->GetUnits()[i]->SetIdleState();
		}
	}
}
