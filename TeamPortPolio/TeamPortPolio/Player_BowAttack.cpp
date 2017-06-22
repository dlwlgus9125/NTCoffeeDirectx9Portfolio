#include "stdafx.h"
#include "Player_State.h"


void Player_BowAttack::OnBegin(cPlayer* pPlayer)
{
	pPlayer->SetMode(FIGHTING_PLAYER_MODE);
	pPlayer->GetBowSkin()->SetAnimationIndexBlend(BOW_PULL);
	pPlayer->GetMesh()->SetAnimationIndexBlend(P_BOWATTACK1);
}

void Player_BowAttack::OnUpdate(cPlayer* pPlayer, float deltaTime)
{
	SetCursor(nullptr);
	D3DXVECTOR3 left;

	left.x = -pPlayer->GetCharacterEntity()->Forward().x;
	left.y = pPlayer->GetCharacterEntity()->Forward().y;
	left.z = pPlayer->GetCharacterEntity()->Forward().z;

	if ((P_STATE)pPlayer->GetMesh()->GetIndex() == P_BOWATTACK1)
	{
		CAMERA->SetCameraDistance(CAMERA->GetCameraDitance() - 0.111111111111f);
		if (CAMERA->GetCameraDitance() < 1.5) CAMERA->SetCameraDistance(1.5);
		if (pPlayer->GetMesh()->GetPassedTime() > pPlayer->GetMesh()->GetCurrentAnim()->GetPeriod() - 0.1f)
		{
			pPlayer->IsPullBow(true);
		}
	}
	if ((P_STATE)pPlayer->GetMesh()->GetIndex() == P_BOWATTACK2)
	{
		pPlayer->GetBowSkin()->SetAnimationIndexBlend(BOW_NORMAL);
		pPlayer->FSM()->Play(PLAYER_STATE_IDLE);
	}
	else if (INPUT->IsMouseUp(MOUSE_LEFT))
	{	
		pPlayer->GetBowSkin()->SetAnimationIndexBlend(BOW_PUSH);
		pPlayer->GetMesh()->SetAnimationIndexBlend(P_BOWATTACK2);
		pPlayer->IsPullBow(false);

		OBJECT->AddPlayerArrow(pPlayer->GetCharacterEntity(), pPlayer->SetUpAim());
	}

}

void Player_BowAttack::OnEnd(cPlayer* pPlayer)
{

}
