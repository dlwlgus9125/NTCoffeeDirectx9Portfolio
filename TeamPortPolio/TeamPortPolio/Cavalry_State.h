#pragma once
#include "cCavalryUnit.h"
#include "cLeader.h"
//enum UNIT_STATE
//{
//	UNIT_Cavalry_STATE_IDLE,
//	UNIT_Cavalry_STATE_WALK,
//	UNIT_Cavalry_STATE_ATTACK,
//	UNIT_Cavalry_STATE_DEFENCE,
//};
class Cavalry_Idle : public IState<cCavalryUnit*>
{
public:
	void OnBegin(cCavalryUnit* pUnit);

	void OnUpdate(cCavalryUnit* pUnit, float deltaTime);

	void OnEnd(cCavalryUnit* pUnit);

};

class Cavalry_Walk : public IState<cCavalryUnit*>
{
public:
	void OnBegin(cCavalryUnit* pUnit);

	void OnUpdate(cCavalryUnit* pUnit, float deltaTime);

	void OnEnd(cCavalryUnit* pUnit);

	void StateChanger(cCavalryUnit * pUnit);
};

class Cavalry_Battle : public IState<cCavalryUnit*>
{
	cObject* BattleTarget;
public:
	void OnBegin(cCavalryUnit* pUnit);

	void OnUpdate(cCavalryUnit* pUnit, float deltaTime);

	void OnEnd(cCavalryUnit* pUnit);

	void StateChanger(cCavalryUnit * pUnit);
};


class Cavalry_Death : public IState<cCavalryUnit*>
{
public:
	void OnBegin(cCavalryUnit* pUnit);

	void OnUpdate(cCavalryUnit* pUnit, float deltaTime);

	void OnEnd(cCavalryUnit* pUnit);
};
