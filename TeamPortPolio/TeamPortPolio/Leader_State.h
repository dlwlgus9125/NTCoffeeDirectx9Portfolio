#pragma once
#include "cLeader.h"
#include "Melee_State.h"
#include "cUnit.h"
#include "cMeleeUnit.h"
//enum UNIT_STATE
//{
//	UNIT_STATE_STATE_IDLE,
//	UNIT_STATE_STATE_WALK,
//	UNIT_STATE_STATE_ATTACK,
//	UNIT_STATE_STATE_DEFENCE,
//};

//공유 state
class Leader_State_Defeat : public IState<cLeader*>
{
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);
};

class Leader_State_Melee_Idle : public IState<cLeader*>
{
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);

};

class Leader_State_Melee_Walk : public IState<cLeader*>
{
	
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);

	void StateChanger(cLeader * pLeader);
};

class Leader_State_Melee_Battle : public IState<cLeader*>
{
	float fPassedTime;
	
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);
};

class Leader_State_Melee_Defence : public IState<cLeader*>
{
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);
};



//>>궁병
class Leader_State_Bowman_Idle : public IState<cLeader*>
{
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);
};

class Leader_State_Bowman_Walk : public IState<cLeader*>
{
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);
};

class Leader_State_Bowman_Battle : public IState<cLeader*>
{
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);
};


//>>기병
class Leader_State_Cavalry_Idle : public IState<cLeader*>
{
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);
};

class Leader_State_Cavalry_Walk : public IState<cLeader*>
{
	
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);
};

class Leader_State_Cavalry_Battle : public IState<cLeader*>
{
public:
	void OnBegin(cLeader* pLeader);

	void OnUpdate(cLeader* pLeader, float deltaTime);

	void OnEnd(cLeader* pLeader);
};

