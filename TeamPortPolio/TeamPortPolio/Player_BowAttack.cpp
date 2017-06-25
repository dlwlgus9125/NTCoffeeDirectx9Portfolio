#include "stdafx.h"
#include "Player_State.h"


void Player_BowAttack::OnBegin(cPlayer* pPlayer)
{
	pPlayer->SetMode(FIGHTING_PLAYER_MODE);
	pPlayer->GetBowSkin()->SetAnimationIndexBlend(BOW_PULL);
	pPlayer->GetMesh()->SetAnimationIndexBlend(P_BOWATTACK1);
	m_fPrevCameraDist = CAMERA->GetCameraDitance();

	if (SOUND->FindChannel("PullBow") == NULL)SOUND->Play("PullBow",2.0f);
}

void Player_BowAttack::OnUpdate(cPlayer* pPlayer, float deltaTime)
{
	SetCursor(nullptr);




	if ((P_STATE)pPlayer->GetMesh()->GetIndex() == P_BOWATTACK1)
	{
		CAMERA->SetCameraDistance(CAMERA->GetCameraDitance() - m_fPrevCameraDist / 10);
		if (CAMERA->GetCameraDitance() < 2) CAMERA->SetCameraDistance(2);
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
		if (SOUND->FindChannel("ShootBow") == NULL)SOUND->Play("ShootBow", 2.0f);
		pPlayer->GetBowSkin()->SetAnimationIndexBlend(BOW_PUSH);
		pPlayer->GetMesh()->SetAnimationIndexBlend(P_BOWATTACK2);
		pPlayer->IsPullBow(false);

		OBJECT->AddPlayerArrow(pPlayer->GetCharacterEntity(), pPlayer->SetUpAim());

		CAMERA->SetCameraDistance(m_fPrevCameraDist);
	}

}

void Player_BowAttack::OnEnd(cPlayer* pPlayer)
{

}
