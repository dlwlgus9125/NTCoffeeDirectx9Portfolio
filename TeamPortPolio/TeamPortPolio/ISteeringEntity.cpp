#include "stdafx.h"
#include "ISteeringEntity.h"


ISteeringEntity::ISteeringEntity(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed)
	: IEntity(pos, radius, forward, mass, maxSpeed)
{
	m_pSteering = new SteeringBehavior(this);
}

SteeringBehavior* ISteeringEntity::Steering() { return m_pSteering; }