#include "stdafx.h"
#include "Player_State.h"

void Player_Idle::OnBegin(cPlayer* pPlayer)
{
	cout << "Mode:" << pPlayer->GetMode() << endl;
}

void Player_Idle::OnUpdate(cPlayer* pPlayer, float deltaTime)
{
	switch (pPlayer->GetMode())
	{
	case IDLE_PLAYER_MODE:
		pPlayer->GetMesh()->SetAnimationIndexBlend(P_STAND);
		break;
	case FIGHTING_PLAYER_MODE:
		pPlayer->GetMesh()->SetAnimationIndexBlend(P_READYATTACK);
		break;
	}

	if (INPUT->IsKeyDown(VK_E))
	{
		if ((PLAYER_MODE_STATE)pPlayer->GetMode() != IDLE_PLAYER_MODE)
		{
			pPlayer->SetMode(IDLE_PLAYER_MODE);
		}

		else if ((PLAYER_MODE_STATE)pPlayer->GetMode() != FIGHTING_PLAYER_MODE)
		{
			pPlayer->SetMode(FIGHTING_PLAYER_MODE);
		}
	}




	if (INPUT->IsKeyPress(VK_W) || INPUT->IsKeyPress(VK_S))
	{
		pPlayer->FSM()->Play(PLAYER_STATE_WALK);
	}

	if (INPUT->IsMouseDown(MOUSE_LEFT) && (PLAYER_MODE_STATE)pPlayer->GetMode() == FIGHTING_PLAYER_MODE)
	{
		switch (pPlayer->GetAttackType())
		{
		case ATTACK_MELEE:pPlayer->FSM()->Play(PLAYER_STATE_ATTACK); break;
		case ATTACK_BOW:pPlayer->FSM()->Play(PLAYER_STATE_BOWATTACK); break;
		}
		
	}
	
	else if (INPUT->IsKeyPress(MOUSE_RIGHT)&& (PLAYER_MODE_STATE)pPlayer->GetMode() == FIGHTING_PLAYER_MODE)
	{
		switch (pPlayer->GetAttackType())
		{
		case ATTACK_MELEE:pPlayer->FSM()->Play(PLAYER_STATE_DEFENCE); break;
		}
	}
}

void Player_Idle::OnEnd(cPlayer* pPlayer)
{

}
