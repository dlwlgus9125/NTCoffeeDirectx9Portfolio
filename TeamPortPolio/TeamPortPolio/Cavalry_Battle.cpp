#include "stdafx.h"
#include "Cavalry_State.h"

void Cavalry_Battle::OnBegin(cCavalryUnit * pUnit)
{
	pUnit->GetMesh()->SetAnimationIndexBlend(K_WALK);
}

void Cavalry_Battle::OnUpdate(cCavalryUnit * pUnit, float deltaTime)
{
	StateChanger(pUnit);
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(pUnit->GetOffset(), pUnit->GetLeader()->Forward());
	D3DXVECTOR3 targetPos = pUnit->GetLeader()->Pos() + worldOffset;

	D3DXVECTOR3 vTotarget = pUnit->GetCharacterEntity()->Pos() - targetPos;
	vTotarget.y = 0;
	float distance = MATH->Magnitude(vTotarget);

	if (distance > 0.1f)
	{
		pUnit->GetCharacterEntity()->Steering()->CavalryOffsetPursuit(pUnit->GetLeader(), pUnit->GetOffset());
		pUnit->GetCharacterEntity()->Steering()->ConstrainOverlap(OBJECT->GetEntities());


		for (int i = 0; i < OBJECT->GetCharacter().size(); i++)
		{
			D3DXVECTOR3 collidedTargetPos = OBJECT->GetCharacter()[i]->GetCharacterEntity()->Pos();

			D3DXVECTOR3 vCollidedtarget = pUnit->GetCharacterEntity()->Pos() - collidedTargetPos;
			vTotarget.y = 0;
			float distance = MATH->Magnitude(vCollidedtarget);
			if (pUnit->GetCamp()!= OBJECT->GetCharacter()[i]->GetCamp()&&pUnit->GetCharacterEntity()->Speed()>0.1f&&MATH->IsCollided(pUnit->GetSphere(), OBJECT->GetCharacter()[i]->GetSphere()))
			{
				if (OBJECT->GetCharacter()[i]->GetCharacterEntity()->IsDeath() == false)
				{
					OBJECT->GetCharacter()[i]->SetAnimHit();
					pUnit->Fight(pUnit, OBJECT->GetCharacter()[i]);
					//cout << "HIT" << endl;
					break;
				}
			}
		}

	}
	else
	{
		pUnit->GetCharacterEntity()->SetForward(pUnit->GetLeader()->Forward());
	}

	


	

}

void Cavalry_Battle::OnEnd(cCavalryUnit * pUnit)
{
}

void Cavalry_Battle::StateChanger(cCavalryUnit * pUnit)
{
	if (pUnit->GetMesh()->GetIndex() != K_WALK&&0.002f <= pUnit->GetCharacterEntity()->Speed() && pUnit->GetCharacterEntity()->Speed() <= 0.05f)
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(K_WALK);
	}
	else if (pUnit->GetMesh()->GetIndex() != K_RUN&&0.05f < pUnit->GetCharacterEntity()->Speed())
	{
		pUnit->GetMesh()->SetAnimationIndexBlend(K_RUN);
	}/*
	 else if (pUnit->GetMesh()->Getindex() != F_READYATTACK&&pUnit->GetCharacterEntity()->Speed() < 0.005f)
	 {
	 pUnit->GetMesh()->SetAnimationIndexBlend(F_READYATTACK);
	 }*/
}
