#pragma once
#include "cBowUnit.h"
#include "cLeader.h"
//enum UNIT_STATE
//{
//	UNIT_Bow_STATE_IDLE,
//	UNIT_Bow_STATE_WALK,
//	UNIT_Bow_STATE_ATTACK,
//	UNIT_Bow_STATE_DEFENCE,
//};
class Bow_Idle : public IState<cBowUnit*>
{
public:
	void OnBegin(cBowUnit* pUnit);

	void OnUpdate(cBowUnit* pUnit, float deltaTime);

	void OnEnd(cBowUnit* pUnit);

};

class Bow_Walk : public IState<cBowUnit*>
{
public:
	void OnBegin(cBowUnit* pUnit);

	void OnUpdate(cBowUnit* pUnit, float deltaTime);

	void OnEnd(cBowUnit* pUnit);

	void StateChanger(cBowUnit * pUnit);
};

class Bow_Battle : public IState<cBowUnit*>
{
	cObject* BattleTarget;
public:
	void OnBegin(cBowUnit* pUnit);

	void OnUpdate(cBowUnit* pUnit, float deltaTime);

	void OnEnd(cBowUnit* pUnit);

	void FindNearTarget(cBowUnit * pUnit);

};


class Bow_Death : public IState<cBowUnit*>
{
public:
	void OnBegin(cBowUnit* pUnit);

	void OnUpdate(cBowUnit* pUnit, float deltaTime);

	void OnEnd(cBowUnit* pUnit);
};
