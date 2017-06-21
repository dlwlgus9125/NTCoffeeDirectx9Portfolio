#include "stdafx.h"
#include "Player_State.h"


void Player_Attack::OnBegin(cPlayer* pPlayer)
{
	pPlayer->SetMode(FIGHTING_PLAYER_MODE);
	pPlayer->GetMesh()->SetAnimationIndexBlend(P_ATTACK1);
}

void Player_Attack::OnUpdate(cPlayer* pPlayer, float deltaTime)
{
	P_STATE state;
	if (pPlayer->GetMode() == FIGHTING_PLAYER_MODE)
	{

	if (INPUT->IsMouseDown(MOUSE_LEFT))
	{
		if ((P_STATE)pPlayer->GetMesh()->GetIndex() == P_ATTACK1)
		{
			state = P_ATTACK2;
		}
		else if ((P_STATE)pPlayer->GetMesh()->GetIndex() == P_ATTACK2)
		{
			state = P_ATTACK3;
		}
		else if ((P_STATE)pPlayer->GetMesh()->GetIndex() == P_ATTACK3)
		{
			state = P_ATTACK1;
		}

		if (pPlayer->GetMesh()->GetPassedTime() > pPlayer->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.4f)
		{
			pPlayer->GetMesh()->SetAnimationIndexBlend(state);
		}
	}
	else if (INPUT->IsKeyPress(MOUSE_RIGHT) && pPlayer->GetMesh()->GetPassedTime() > pPlayer->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.4f)
	{
		pPlayer->FSM()->Play(PLAYER_STATE_DEFENCE);
	}

	else
	{
		if (pPlayer->GetMesh()->GetPassedTime() > pPlayer->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.25f)
		{
			pPlayer->FSM()->Play(PLAYER_STATE_IDLE);
		}
	}
	// 충돌 처리 및 공격 카운트 후 죽는 모션까지..
	  for (int i = 0; i < OBJECT->GetLeader().size(); i++)
         {
            if (OBJECT->GetLeader()[i]->GetCamp() == CAMP_PLAYER)return;
            
            for each(auto p in OBJECT->GetLeader()[i]->GetUnits())
            {
				int attackCount = 0;
               if (MATH->IsCollided(pPlayer->GetAttackCollider(), p->GetSphere()))
               {
                  p->GetMesh()->SetAnimationIndexBlend(FG_HIT);

				  if (p->GetMesh()->GetPassedTime() > p->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.25f)
				  {
					  attackCount++;
				  }
               }
			   else if (attackCount > 5)
			   {
				   p->SetDeath(true);
				   attackCount = 0;
			   }

			   if (p->GetLeader()->IsDeath() == true)
			   {
				   p->GetMesh()->SetAnimationIndexBlend(FG_DEATH);
			   }
			}
         }
	}
}

void Player_Attack::OnEnd(cPlayer* pPlayer)
{
}
