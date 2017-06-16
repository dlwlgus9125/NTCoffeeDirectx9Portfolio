#include "stdafx.h"
#include "Player_State.h"


void Player_Defence::OnBegin(cPlayer* pPlayer)
{
	pPlayer->SetMode(FIGHTING_PLAYER_MODE);
	pPlayer->GetMesh()->SetAnimationIndexBlend(P_SHEILDUP);
}

void Player_Defence::OnUpdate(cPlayer* pPlayer, float deltaTime)
{
	if (INPUT->IsMouseUp(MOUSE_RIGHT))
	{
		pPlayer->FSM()->Play(PLAYER_STATE_IDLE);
	}
}

void Player_Defence::OnEnd(cPlayer* pPlayer)
{

}
