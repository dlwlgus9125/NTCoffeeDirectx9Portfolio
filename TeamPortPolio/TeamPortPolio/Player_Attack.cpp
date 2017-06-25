#include "stdafx.h"
#include "Player_State.h"
#include "cCharacter.h"


void Player_Attack::OnBegin(cPlayer* pPlayer)
{
	pPlayer->SetMode(FIGHTING_PLAYER_MODE);
	pPlayer->GetMesh()->SetAnimationIndexBlend(P_ATTACK1);
}

void Player_Attack::OnUpdate(cPlayer* pPlayer, float deltaTime)
{
	P_STATE state;
	FindBattleTarget(pPlayer);


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
		else
		{
			state = P_ATTACK1;
		}
		if (pPlayer->GetMesh()->GetPassedTime() > pPlayer->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.4f)
		{
			SOUND->Play("SwingSword");
			pPlayer->GetMesh()->SetAnimationIndexBlend(state);
			if (BattleTarget && ((cCharacter*)BattleTarget)->GetCharacterEntity()->IsDeath() == false
				&& ((cCharacter*)BattleTarget)->GetCharacterEntity()->IsDeath() == false)
			{				
				((cCharacter*)BattleTarget)->SetAnimHit();
				pPlayer->Fight(pPlayer, (cCharacter*)BattleTarget);

			}
		}
	}
	else if (INPUT->IsKeyPress(MOUSE_RIGHT) && pPlayer->GetMesh()->GetPassedTime() > pPlayer->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.4f)
	{
		pPlayer->FSM()->Play(PLAYER_STATE_DEFENCE);
		pPlayer->GetStatus()->m_defence = 10.0f;
	}
	else if (INPUT->IsKeyUp(MOUSE_RIGHT))
	{
		pPlayer->GetStatus()->m_defence = 4.0f;
	}
	else
	{
		if (pPlayer->GetMesh()->GetPassedTime() > pPlayer->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.25f)
		{
			pPlayer->FSM()->Play(PLAYER_STATE_IDLE);
		}
	}
	// 충돌 처리 및 공격 카운트 후 죽는 모션까지..
}

void Player_Attack::OnEnd(cPlayer* pPlayer)
{
}

void Player_Attack::FindBattleTarget(cPlayer * pPlayer)
{
	BattleTarget = NULL;
	for each(auto t in OBJECT->GetCharacter())
	{
		if (t->GetCharacterEntity()->IsDeath() == false && t->GetCamp() != pPlayer->GetCamp() && MATH->IsCollided(t->GetSphere(), pPlayer->GetMeleeCollider()))
		{
			BattleTarget = t;
			break;
		}
	}
}