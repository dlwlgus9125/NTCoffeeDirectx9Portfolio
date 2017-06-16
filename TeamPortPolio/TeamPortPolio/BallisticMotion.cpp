#include "stdafx.h"
#include "BallisticMotion.h"
#include "IEntity.h"

BallisticMotion::BallisticMotion(IEntity * entity, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vTarget, D3DXVECTOR3 vDir) :
	m_pEntity(entity)
	, m_vTarget(vTarget)
	,m_vOrigin(vOrigin)
	,m_fGravity(-1)
{
	m_pEntity->SetForward(vDir);
	m_stSphere.fRadius = entity->Radius();
	m_stSphere.vCenter = entity->Pos();
	m_stSphere.vCenter.y = entity->Pos().y;
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
	m_fGravity += maxHeight / TIME->FPS();
	
	Entity()->SetForward(vToTarget);
	Entity()->AddPos(Entity()->Forward());
	m_stSphere.vCenter = Entity()->Pos();
	m_stSphere.vCenter.y++;
}

void BallisticMotion::Update_with_dir()
{
	D3DXVECTOR3 vDirtoTarget = Entity()->Forward();
	float power = 30;
	D3DXVECTOR3 vArrowvellocity = vDirtoTarget*power;
	float fDistance =MATH->Distance(m_vOrigin , Entity()->Pos());
	vDirtoTarget.y += m_fGravity/GravityMultiPlier(fDistance);

	Entity()->SetForward(vDirtoTarget);
	Entity()->AddPos(vArrowvellocity / 60);
	m_stSphere.vCenter = Entity()->Pos();
	m_stSphere.vCenter.y++;
}

float BallisticMotion::GravityMultiPlier(float distance)
{
	return  2*TIME->FPS() / distance;
}
