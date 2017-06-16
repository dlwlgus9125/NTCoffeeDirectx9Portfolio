#pragma once
#include"stdafx.h"
#include "cBallisticArrow.h"

cBallisticArrow::cBallisticArrow(D3DXVECTOR3 pos, D3DXVECTOR3 vtarget, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed)
	: IEntity(pos, radius, forward, mass, maxSpeed)
{
	m_pArrow = new BallisticMotion(this,pos,vtarget,forward);
}

cBallisticArrow::~cBallisticArrow()
{
	SAFE_DELETE(m_pArrow);
}

BallisticMotion * cBallisticArrow::Shoot()
{
	return m_pArrow;
}
