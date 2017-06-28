#include "stdafx.h"
#include "SteeringBehavior.h"
#include "cUnit.h"

SteeringBehavior::SteeringBehavior(IEntity* pEntity)
{
	m_pEntity = pEntity;

}

IEntity* SteeringBehavior::Entity() { return m_pEntity; }

// 도착 : 목표점으로 도착하는 조종힘을 합산
void SteeringBehavior::Arrive(D3DXVECTOR3 targetPos)
{
	D3DXVECTOR3 vToTarget = targetPos - Entity()->Pos();
	vToTarget.y = 0;
	float distance = MATH->Magnitude(vToTarget);
	float speedMultiplier = 5;
	if (distance > 1)
	{
		float speed = (distance / TIME->FPS())*speedMultiplier;
		if (speed > 0.08)speed = 0.08;


		Entity()->SetForward(vToTarget);
		Entity()->AddPos(Entity()->Forward()*speed);
		Entity()->SetSpeed(speed);

	}
	else
	{
		float speed= 0.01;


		Entity()->SetForward(vToTarget);
		Entity()->AddPos(Entity()->Forward()*speed);
		Entity()->SetSpeed(speed);
	}
}
void SteeringBehavior::LeaderArrive(D3DXVECTOR3 targetPos)
{
	D3DXVECTOR3 vToTarget = targetPos - Entity()->Pos();
	vToTarget.y = 0;
	float distance = MATH->Magnitude(vToTarget);
	float speedMultiplier = 9;
	if (distance > 1)
	{
		float speed = (distance / TIME->FPS())*speedMultiplier;
		if (speed > 0.12)speed = 0.12;
		Entity()->SetForward(vToTarget);
		Entity()->AddPos(Entity()->Forward() / 17);
		Entity()->SetSpeed(speed);
	}
	else
	{
		float speed = 0.01;


		Entity()->SetForward(vToTarget);
		Entity()->AddPos(Entity()->Forward()*speed);
		Entity()->SetSpeed(speed);
	}
}

void SteeringBehavior::CavalryLeaderArrive(D3DXVECTOR3 targetPos, float velocity)
{
	D3DXVECTOR3 vToTarget = targetPos - Entity()->Pos();
	vToTarget.y = 0;
	float distance = MATH->Magnitude(vToTarget);
	float speedMultiplier = 9;
	if (distance > 1)
	{
		float speed = (distance / TIME->FPS())*speedMultiplier;
		if (speed > 0.16)speed = 0.16;

		Entity()->SetForward(vToTarget);
		Entity()->AddPos(Entity()->Forward()*(speed ));
		Entity()->SetSpeed(speed );
	}
}

void SteeringBehavior::UnitArrive(D3DXVECTOR3 targetPos)
{
	D3DXVECTOR3 vToTarget = targetPos - Entity()->Pos();
	float distance = MATH->Magnitude(vToTarget);
	float speedMultiplier = 9;
	if (distance > 1)
	{
		float speed = (distance / TIME->FPS())*speedMultiplier;
		if (speed > 0.12)speed = 0.12;
		Entity()->SetForward(vToTarget);
		Entity()->AddPos(Entity()->Forward()*speed);
		Entity()->SetSpeed(speed);

	}
	else
	{
		float speed = 0.01;


		Entity()->SetForward(vToTarget);
		Entity()->AddPos(Entity()->Forward()*speed);
		Entity()->SetSpeed(speed);
	}
}

void SteeringBehavior::CavalryUnitArrive(D3DXVECTOR3 targetPos, float velocity)
{
	D3DXVECTOR3 vToTarget = targetPos - Entity()->Pos();
	float distance = MATH->Magnitude(vToTarget);
	float speedMultiplier = 3;
	if (distance > 1)
	{
		float speed = (distance / TIME->FPS())*speedMultiplier;
		if (speed > 0.12f)speed = 0.12f;

		Entity()->SetForward(vToTarget);
		Entity()->AddPos(Entity()->Forward()*(speed));
		Entity()->SetSpeed(speed);
	}
	else
	{
		float speed = 0.02;


		Entity()->SetForward(vToTarget);
		Entity()->AddPos(Entity()->Forward()*speed);
		Entity()->SetSpeed(speed);
	}
}

// 도주
void SteeringBehavior::Evade(IEntity* pTarget)
{
	D3DXVECTOR3 fleeDir;
	D3DXVec3Normalize(&fleeDir, &(Entity()->Pos() - pTarget->Pos()));
	Entity()->SetForward(fleeDir);
	Arrive(Entity()->Forward());
}

// 배회
void SteeringBehavior::Wander(float distance, float radius, float jitter)
{
	//	float randomX = MATH->Random(-1.0f, 1.0f) * jitter;
	//	float randomY = MATH->Random(-1.0f, 1.0f) * jitter;
	//	m_wander += Vector(randomX, randomY);
	//	m_wander = m_wander.Normalize() * radius;
	//
	//	Vector targetPos = Entity()->Pos() + Entity()->Forward() * distance + m_wander;
	//	AddForce(targetPos - Entity()->Pos());
	//
	//	D3DXVECTOR3 vPos = Entity()->Pos();
	//
	//	D3DXVECTOR3 targetPos((-1 + rand() % 2 + 1), (-1 + rand() % 2 + 1), (-1 + rand() % 2 + 1));
	//
	//	Entity()->SetForward(targetPos);
	//	if (MATH->Distance(Entity()->Pos(), PosOrigin) > distance)Entity()->SetForward(-targetPos);
	//
	//	Entity()->AddPos(Entity()->Forward());
	//	Entity()->SetForward(vPos);
	//	Entity()->AddPos(Entity()->Forward);
}

// 장애물 회피
void SteeringBehavior::AvoidObstacle(ST_SPHERE pObstacle)
{
	float distance = MATH->Distance(Entity()->Pos(), pObstacle.vCenter);
	float length = distance - (Entity()->Radius() + pObstacle.fRadius);
	if (length < 0)
	{
		D3DXVECTOR3 vDir = Entity()->Pos() - pObstacle.vCenter;
		Entity()->AddPos(vDir / TIME->FPS());
	}
}

// 겹침 제한
void SteeringBehavior::ConstrainOverlap(IEntity* pTarget)
{
	if (pTarget->IsDeath() == false)
	{
		D3DXVECTOR3 vEntity = pTarget->Pos() - Entity()->Pos();
		float distance = MATH->Magnitude(vEntity);
		float totalRadius = Entity()->Radius() + pTarget->Radius();

		if (distance < totalRadius)
		{
			D3DXVec3Normalize(&vEntity, &vEntity);
			pTarget->AddPos(vEntity * (distance)*0.01f);
		}
	}
}

// 겹침 제한
void SteeringBehavior::ConstrainOverlap(vector<IEntity*> targets)
{
	for (int i = 0; i < targets.size(); i++)
	{
		if (targets[i]->IsDeath() == false)
		{
			ST_SPHERE thisSphere(Entity()->Pos(), Entity()->Radius());
			ST_SPHERE itSphere(targets[i]->Pos(), targets[i]->Radius());
			if (MATH->IsCollided(thisSphere, itSphere))
			{
				D3DXVECTOR3 pushDir = MATH->GetOverlappedVector(thisSphere, itSphere);
				Entity()->SetPos(Entity()->Pos() - pushDir);
				ConstrainOverlap(targets[i]);
			}
		}
	}
}

void SteeringBehavior::OffsetPursuit(IEntity* pLeader, D3DXVECTOR3 offset)
{
	D3DXVECTOR3 forward;
	
	forward = pLeader->Forward();

	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(offset, forward);
	D3DXVECTOR3 targetPos = pLeader->Pos() + worldOffset;
	targetPos.y = 0;
	float distance = MATH->Distance(Entity()->Pos(), targetPos);
	float arrivalTime = distance / Entity()->MaxSpeed();
	Arrive(targetPos);
}

void SteeringBehavior::CavalryOffsetPursuit(IEntity* pLeader, D3DXVECTOR3 offset)
{
	D3DXVECTOR3 forward = pLeader->Forward();

	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(offset, forward);
	D3DXVECTOR3 targetPos = pLeader->Pos() + worldOffset;
	CavalryUnitArrive(targetPos, (pLeader->Speed()*0.8f));
}