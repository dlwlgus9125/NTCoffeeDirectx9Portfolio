#pragma once
#include "IEntity.h"
#include "SteeringBehavior.h"

class ISteeringEntity : public IEntity
{
	SteeringBehavior* m_pSteering;

public:
	ISteeringEntity(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed);

	SteeringBehavior* Steering();
};