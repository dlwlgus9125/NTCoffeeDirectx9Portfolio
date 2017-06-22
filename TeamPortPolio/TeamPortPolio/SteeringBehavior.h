#pragma once
#include "IEntity.h"

class cUnit;
// 조종행동을 처리하는 클래스
class SteeringBehavior
{
	IEntity* m_pEntity;
	// 배회 벡터

public:
	SteeringBehavior(IEntity* pEntity);

	IEntity* Entity();

	//m_force += force;


	// 도착 : 목표점으로 도착하는 조종힘을 합산
	void Arrive(D3DXVECTOR3 targetPos);

	// 도착 : 부대가 목표점으로 
	void LeaderArrive(D3DXVECTOR3 targetPos);

	// 도착 : 기병부대가 목표점으로 
	void CavalryLeaderArrive(D3DXVECTOR3 targetPos, float velocity);

	// 도착 : 유닛이 목표점으로 
	void UnitArrive(D3DXVECTOR3 targetPos);

	// 도착 : 기병유닛이 목표점으로 
	void CavalryUnitArrive(D3DXVECTOR3 targetPos, float velocity);
	// 추격
	void Pursuit(IEntity* pTarget);

	// 도주
	void Evade(IEntity* pTarget);

	void Wander(D3DXVECTOR3 PosOrigin, float distance);

	void Wander(IEntity * pEntity);

	// 배회
	void Wander(float distance, float radius, float jitter);

	void AvoidObstacle(ST_SPHERE pObstacle);


	// 장애물 회피
	void AvoidObstacle(IEntity* pObstacle);

	// 장애물 회피 (복수)
	void AvoidObstacle(vector<cUnit*> obstacles);

	// 겹침 제한
	void ConstrainOverlap(IEntity* pTarget);

	// 겹침 제한
	void ConstrainOverlap(vector<IEntity*> targets);

	void OffsetPursuit(IEntity* pLeader, D3DXVECTOR3 offset);

	void CavalryOffsetPursuit(IEntity* pLeader, D3DXVECTOR3 offset);

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