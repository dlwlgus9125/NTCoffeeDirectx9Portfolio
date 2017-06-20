#include "stdafx.h"
#include "Leader_State.h"

void Leader_State_Melee_Battle::OnBegin(cLeader * pLeader)
{
	//pLeader->SetPath(ASTAR->GetPath(pLeader->GetIndex(), pLeader->GetTargetIndex()));
	//>>전투 시작과 동시에 휘하 유닛에게 상대 부대 id를 넘김
	for (int i = 0; i < pLeader->GetUnits().size(); i++)
	{
		if (pLeader->GetUnits()[i]->IsDeath() != true)
		{
			pLeader->GetUnits()[i]->SetTargetObject(pLeader->GetTargetObject());
			pLeader->GetUnits()[i]->SetBattleState();
		}
	}
		
}

void Leader_State_Melee_Battle::OnUpdate(cLeader * pLeader, float deltaTime)
{
	if (((cCharacter*)pLeader->GetTargetObject())->GetCharacterEntity()->IsDeath() == true)
	{
		pLeader->SetTargetObject(NULL);
		pLeader->SetTargetIndex(pLeader->GetIndex());
		pLeader->FSM()->Play(LEADER_STATE_MELEE_IDLE);
	}
	else
	{
		D3DXVECTOR3 pos = pLeader->GetCharacterEntity()->Pos();
		D3DXVECTOR3 targetPos = pLeader->GetTargetObject()->GetCharacterEntity()->Pos() + pLeader->GetTargetObject()->GetCharacterEntity()->Forward();


		float distance = MATH->Distance(pos, targetPos);

		if (distance > 0.5f)
		{
			pLeader->GetCharacterEntity()->Steering()->LeaderArrive(targetPos);
			//pLeader->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());

		}

		if (INPUT->IsKeyDown(VK_SPACE))cout << pLeader->GetUnits().size() << endl;

	}

}

void Leader_State_Melee_Battle::OnEnd(cLeader * pLeader)
{
	pLeader->PathClear();
	pLeader->SetIndex(pLeader->GetIndex());
}
