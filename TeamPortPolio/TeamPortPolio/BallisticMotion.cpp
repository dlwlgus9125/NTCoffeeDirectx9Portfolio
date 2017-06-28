#include "stdafx.h"
#include "BallisticMotion.h"
#include "IEntity.h"

BallisticMotion::BallisticMotion(IEntity * entity, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vTarget, D3DXVECTOR3 vDir, float radius) :
	m_pEntity(entity)
	, m_vTarget(vTarget)
	, m_vOrigin(vOrigin)
{
	m_pEntity->SetForward(vDir);
}

BallisticMotion::~BallisticMotion()
{
}

void BallisticMotion::Update_with_targetpos()
{
	if (Entity()->Pos().y < -1)return;

	D3DXVECTOR3 vToTarget = m_vTarget - m_vOrigin;

	float fdistance = D3DXVec3Length(&(vToTarget));
	float maxHeight = fdistance*cosf(30);

	vToTarget.y = maxHeight - m_fGravity*GravityMultiPlier(fdistance);
	m_fGravity += (maxHeight / TIME->FPS());

	Entity()->SetForward(vToTarget);
	Entity()->AddPos(Entity()->Forward());
}

void BallisticMotion::Update_with_dir()
{
	D3DXVECTOR3 vDirtoTarget = Entity()->Forward();
	float fDistance = MATH->Distance(m_vOrigin, Entity()->Pos());
	m_fGravity = 0.01 / GravityMultiPlier(fDistance);
	vDirtoTarget.y -= m_fGravity;

	Entity()->SetForward(vDirtoTarget);
	Entity()->AddPos(vDirtoTarget);
}

float BallisticMotion::GravityMultiPlier(float distance)
{
	return  2 * TIME->FPS() / distance;
}

void BallisticMotion::UpdateMatrix()
{
	D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, Entity()->Pos().x, Entity()->Pos().y, Entity()->Pos().z);

	m_matrix = matT;
}
