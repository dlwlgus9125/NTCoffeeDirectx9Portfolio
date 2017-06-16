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

			//'17-06-16 Ãß°¡ ÇÏ°Ú½À´Ï´Ù. feat ±èÀ±Áß
			//if (MATH->IsCollided(pPlayer->GetAttackCollider(), ((cUnit*)BattleTarget)->GetSphere()))
			//{

			//}
		}

	}

	else if (INPUT->IsKeyPress(VK_W) || INPUT->IsKeyPress(VK_S))
	{
		pPlayer->FSM()->Play(PLAYER_STATE_WALK);
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

}

void Player_Attack::OnEnd(cPlayer* pPlayer)
{
}
