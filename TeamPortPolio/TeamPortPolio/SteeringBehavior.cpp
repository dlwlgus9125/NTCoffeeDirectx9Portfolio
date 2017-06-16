#include "stdafx.h"
#include "SteeringBehavior.h"
#include "cUnit.h"

SteeringBehavior::SteeringBehavior(IEntity* pEntity, float maxForce, float forceMultiplier)
{
	m_pEntity = pEntity;
	m_force = D3DXVECTOR3(0, 0, 0);
	m_forceMultiplier = forceMultiplier;
	m_maxForce = maxForce;
}

IEntity* SteeringBehavior::Entity() { return m_pEntity; }

void SteeringBehavior::AddForce(D3DXVECTOR3 force)
{
	float currentForce = MATH->Magnitude(m_force);
	float remainedForce = m_maxForce - currentForce;
	if (remainedForce > 0)
	{
		if ((MATH->Magnitude(force)) < remainedForce)
		{
			m_force += force;
		}
		else
		{
			D3DXVec3Normalize(&force, &force);
			m_force += force *remainedForce;
		}
	}

	//m_force += force;
}

// 조종힘으로 속도 계산후 적용
void SteeringBehavior::UpdateVelocity(float deltaTime)
{
	m_force = MATH->Clamp(m_force, 0, m_maxForce) * m_forceMultiplier;
	D3DXVECTOR3 acceleration = m_force / Entity()->Mass();
	D3DXVECTOR3 velocity = Entity()->Velocity() + acceleration * deltaTime;
	Entity()->SetVelocity(velocity);
	Entity()->SetForward(velocity);

	m_force = D3DXVECTOR3(0, 0, 0);
}

// 찾기 : 목표점을 찾아가는 조종힘을 합산
void SteeringBehavior::Seek(D3DXVECTOR3 targetPos)
{
	D3DXVECTOR3 targetDir;
	D3DXVec3Normalize(&targetDir, &(targetPos - Entity()->Pos()));
	D3DXVECTOR3 targetVelocity = targetDir * Entity()->MaxSpeed();
	AddForce(targetVelocity - Entity()->Velocity());
}

// 피하기 : 목표점으로부터 멀어지는 조종힘을 합산
void SteeringBehavior::Flee(D3DXVECTOR3 targetPos)
{
	D3DXVECTOR3 targetDir;
	D3DXVec3Normalize(&targetDir, &(Entity()->Pos() - targetPos));
	D3DXVECTOR3 targetVelocity = targetDir * Entity()->MaxSpeed();
	AddForce(targetVelocity - Entity()->Velocity());
}

// 도착 : 목표점으로 도착하는 조종힘을 합산
void SteeringBehavior::Arrive(D3DXVECTOR3 targetPos)
{
	D3DXVECTOR3 vToTarget = targetPos - Entity()->Pos();
	vToTarget.y = 0;
	float distance = MATH->Magnitude(vToTarget);
	float speedMultiplier = 3;
	if (distance > EPSILON)
	{
		float speed = (distance / TIME->FPS())*speedMultiplier;

		if (speed > 0.05)speed = 0.05;

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
	float speedMultiplier = 3;
	if (distance > EPSILON)
	{
		float speed = (distance / TIME->FPS())*speedMultiplier;
		if (speed > 0.05)speed = 0.05;
		Entity()->SetForward(vToTarget);
		Entity()->AddPos(Entity()->Forward()*speed);
		Entity()->SetSpeed(speed);
	}
}

void SteeringBehavior::UnitArrive(D3DXVECTOR3 targetPos)
{
	D3DXVECTOR3 vToTarget = targetPos - Entity()->Pos();
	float distance = MATH->Magnitude(vToTarget);
	float speedMultiplier = 3;
	if (distance > EPSILON)
	{
		float speed = (distance / TIME->FPS())*speedMultiplier;
		if (speed > 0.05)speed = 0.05;

		Entity()->SetForward(vToTarget);
		Entity()->AddPos(Entity()->Forward()*speed);
		Entity()->SetSpeed(speed);
	}
}

// 추격
void SteeringBehavior::Pursuit(IEntity* pTarget)
{
	D3DXVECTOR3 vToTarget = pTarget->Pos() - Entity()->Pos();
	float distance = MATH->Magnitude(vToTarget);
	float lookAheadTime = distance / (Entity()->MaxSpeed() + pTarget->MaxSpeed());
	Seek(pTarget->Pos() + pTarget->Velocity() * lookAheadTime);
}

// 도주
void SteeringBehavior::Evade(IEntity* pTarget)
{
	D3DXVECTOR3 vToTarget = pTarget->Pos() - Entity()->Pos();
	float distance = MATH->Magnitude(vToTarget);
	float lookAheadTime = distance / (Entity()->MaxSpeed() + pTarget->MaxSpeed());
	Flee(pTarget->Pos() + pTarget->Velocity() * lookAheadTime);
}

// 배회
void SteeringBehavior::Wander(float distance, float radius, float jitter)
{
	/*float randomX = MATH->Random(-1.0f, 1.0f) * jitter;
	float randomY = MATH->Random(-1.0f, 1.0f) * jitter;
	m_wander += Vector(randomX, randomY);
	m_wander = m_wander.Normalize() * radius;

	Vector targetPos = Entity()->Pos() + Entity()->Forward() * distance + m_wander;
	AddForce(targetPos - Entity()->Pos());*/
}

// 장애물 회피
void SteeringBehavior::AvoidObstacle(IEntity* pObstacle)
{
	//if (Entity()->Velocity().SqrMagnitude() < EPSILON) return;

	//float sensingLength = Entity()->Speed();
	//float expandRadius = Entity()->Radius() + pObstacle->Radius();
	//float breakingForceWeight = 0.005f;

	//Vector localPos = MATH->WorldToLocal(pObstacle->Pos() - Entity()->Pos(), Entity()->Forward());

	//// 감지범위 & 장애물 충돌 체크
	//if (localPos.x > EPSILON && localPos.x - pObstacle->Radius() < sensingLength
	//	&& abs(localPos.y) < expandRadius)
	//{
	//	// 충돌 위치 계산
	//	float A = sqrt(expandRadius * expandRadius - localPos.y * localPos.y);
	//	float collidedX = localPos.x - A;

	//	// 제동력
	//	float breakingForce = -(sensingLength - collidedX) * breakingForceWeight;

	//	// 옆방향힘 계산
	//	float overlappedY = expandRadius - abs(localPos.y);
	//	float lateralForce = (localPos.y > 0) ? -overlappedY : overlappedY;

	//	AddForce(MATH->LocalToWorld(Vector(breakingForce, lateralForce), Entity()->Forward()));
	//}
}

// 장애물 회피 (복수)
void SteeringBehavior::AvoidObstacle(vector<cUnit*> obstacles)
{
	////if (MATH->SqrMagnitude( Entity()->Velocity().SqrMagnitude() < EPSILON) return;
	//float sensingLength = Entity()->Speed();

	//float closestX = 999999.9f;
	//IEntity* closestEntity = NULL;

	//for (int i = 0; i < obstacles.size(); i++)
	//{
	//	float expandRadius = Entity()->Radius() + obstacles[i]->GetCharacterEntity()->Radius();
	//	D3DXVECTOR3 localPos = MATH->WorldToLocal(obstacles[i]->GetCharacterEntity()->Pos() - Entity()->Pos(), Entity()->Forward());

	//	// 감지범위 & 장애물 충돌 체크
	//	if (localPos.x > EPSILON && localPos.x - obstacles[i]->Radius() < sensingLength
	//		&& abs(localPos.y) < expandRadius)
	//	{
	//		// 충돌 위치 계산
	//		float A = sqrt(expandRadius * expandRadius - localPos.y * localPos.y);
	//		float collidedX = localPos.x - A;

	//		if (collidedX < closestX)
	//		{
	//			closestX = collidedX;
	//			closestEntity = obstacles[i];
	//		}
	//	}
	//}

	//if (closestEntity != NULL)
	//{
	//	AvoidObstacle(closestEntity);
	//}
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
	D3DXVECTOR3 worldOffset = MATH->LocalToWorld(offset, pLeader->Forward());
	D3DXVECTOR3 targetPos = pLeader->Pos() + worldOffset;
	targetPos.y=0;
	float distance = MATH->Distance(Entity()->Pos(), targetPos);
	float arrivalTime = distance / Entity()->MaxSpeed();
	Arrive(targetPos + pLeader->Velocity() * arrivalTime);

	/*cout << "worldOffset : " << worldOffset.x << ", " << worldOffset.y << ", " << worldOffset.z << endl;
	cout << "targetPos : " << targetPos.x << ", " << targetPos.y << ", " << targetPos.z << endl;
	*/
}