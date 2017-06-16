#pragma once
#include "IEntity.h"

class cUnit;
// 조종행동을 처리하는 클래스
class SteeringBehavior
{
	IEntity* m_pEntity;

	D3DXVECTOR3 m_force;				// 조종행으로 발생한 조종힘의 합
	float m_forceMultiplier;			// 조종힘에 곱해주는 값
	float m_maxForce;					// 최대 조종힘

	D3DXVECTOR3 m_wander;			// 배회 벡터

public:
	SteeringBehavior(IEntity* pEntity, float maxForce = 2, float forceMultiplier = 200);

	IEntity* Entity();

	void AddForce(D3DXVECTOR3 force);

	//m_force += force;


// 조종힘으로 속도 계산후 적용
	void UpdateVelocity(float deltaTime);

	// 찾기 : 목표점을 찾아가는 조종힘을 합산
	void Seek(D3DXVECTOR3 targetPos);
	// 피하기 : 목표점으로부터 멀어지는 조종힘을 합산
	void Flee(D3DXVECTOR3 targetPos);

	// 도착 : 목표점으로 도착하는 조종힘을 합산
	void Arrive(D3DXVECTOR3 targetPos);

	// 도착 : 부대가 목표점으로 
	void LeaderArrive(D3DXVECTOR3 targetPos);

	// 도착 : 유닛이 목표점으로 
	void UnitArrive(D3DXVECTOR3 targetPos);
	// 추격
	void Pursuit(IEntity* pTarget);

	// 도주
	void Evade(IEntity* pTarget);

	// 배회
	void Wander(float distance, float radius, float jitter);


	// 장애물 회피
	void AvoidObstacle(IEntity* pObstacle);

	// 장애물 회피 (복수)
	void AvoidObstacle(vector<cUnit*> obstacles);

	// 겹침 제한
	void ConstrainOverlap(IEntity* pTarget);

	// 겹침 제한
	void ConstrainOverlap(vector<IEntity*> targets);

	void OffsetPursuit(IEntity* pLeader, D3DXVECTOR3 offset);

	// 길 이동
	/*void FollowPath(Grid& grid, vector<int>& path, float seekDistance)
	{
		if (path.size() == 0) return;

		Vector targetPos = grid.TilePos(path.back());

		if (path.size() > 1)
		{
			Seek(targetPos);

			if (MATH->SqrDistance(Entity()->Pos(), targetPos) < seekDistance * seekDistance)
			{
				path.pop_back();
			}
		}
		else
		{
			Arrive(targetPos);

			if (MATH->SqrDistance(Entity()->Pos(), targetPos) < 20)
			{
				path.pop_back();
				m_force = Vector(0, 0);
				Entity()->SetVelocity(Vector(0, 0));
			}
		}
	}*/
};