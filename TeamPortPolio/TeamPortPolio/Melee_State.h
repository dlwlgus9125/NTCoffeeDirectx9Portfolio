#pragma once
#include "cMeleeUnit.h"
#include "cLeader.h"
//enum UNIT_STATE
//{
//	UNIT_Melee_STATE_IDLE,
//	UNIT_Melee_STATE_WALK,
//	UNIT_Melee_STATE_ATTACK,
//	UNIT_Melee_STATE_DEFENCE,
//};
class Melee_Idle : public IState<cMeleeUnit*>
{
public:
	void OnBegin(cMeleeUnit* pUnit);

	void OnUpdate(cMeleeUnit* pUnit, float deltaTime);

	void OnEnd(cMeleeUnit* pUnit);

};

class Melee_Walk : public IState<cMeleeUnit*>
{
public:
	void OnBegin(cMeleeUnit* pUnit);

	void OnUpdate(cMeleeUnit* pUnit, float deltaTime);

	void OnEnd(cMeleeUnit* pUnit);

	void StateChanger(cMeleeUnit * pUnit);
};

class Melee_Battle : public IState<cMeleeUnit*>
{
	cObject* BattleTarget;
	bool  m_isShoutCharge;
public:
	void OnBegin(cMeleeUnit* pUnit);

	void OnUpdate(cMeleeUnit* pUnit, float deltaTime);

	void OnEnd(cMeleeUnit* pUnit);

	void StateChanger(cMeleeUnit * pUnit);

	void FindTarget(cMeleeUnit * pUnit);

	void FindNearTarget(cMeleeUnit * pUnit);

	void Charge(cMeleeUnit * pUnit);

	void Battle(cMeleeUnit * pUnit);

	void BattleWithTarget(cMeleeUnit* pUnit);
};

class Melee_Defence : public IState<cMeleeUnit*>
{
public:
	void OnBegin(cMeleeUnit* pUnit);

	void OnUpdate(cMeleeUnit* pUnit, float deltaTime);

	void OnEnd(cMeleeUnit* pUnit);
};


class Melee_Death : public IState<cMeleeUnit*>
{
public:
	void OnBegin(cMeleeUnit* pUnit);

	void OnUpdate(cMeleeUnit* pUnit, float deltaTime);

	void OnEnd(cMeleeUnit* pUnit);
};
