#pragma once
#include "cPlayer.h"

#include "cLeader.h"
#include "cUnit.h"

class Player_Idle : public IState<cPlayer*>
{

public:
	void OnBegin(cPlayer* pPlayer);

	void OnUpdate(cPlayer* pPlayer, float deltaTime);

	void OnEnd(cPlayer* pPlayer);
};

class Player_Walk : public IState<cPlayer*>
{
public:
	void OnBegin(cPlayer* pPlayer);

	void OnUpdate(cPlayer* pPlayer, float deltaTime);

	void OnEnd(cPlayer* pPlayer);

	void StateChanger(cPlayer * pPlayer, D3DXVECTOR3 prevPos, D3DXVECTOR3 movePos);

	void Move(cPlayer* pPlayer);
};

class Player_Attack : public IState<cPlayer*>
{
	cObject* BattleTarget;

public:
	void OnBegin(cPlayer* pPlayer);

	void OnUpdate(cPlayer* pPlayer, float deltaTime);

	void OnEnd(cPlayer* pPlayer);

	void FindBattleTarget(cPlayer * pPlayer);
};

class Player_BowAttack : public IState<cPlayer*>
{
	cObject* BattleTarget;
	float m_fPrevCameraDist;
public:
	void OnBegin(cPlayer* pPlayer);

	void OnUpdate(cPlayer* pPlayer, float deltaTime);

	void OnEnd(cPlayer* pPlayer);

	void StateChanger(cPlayer * pPlayer);
};

class Player_Defence : public IState<cPlayer*>
{
public:
	void OnBegin(cPlayer* pPlayer);

	void OnUpdate(cPlayer* pPlayer, float deltaTime);

	void OnEnd(cPlayer* pPlayer);
};


class Player_Death : public IState<cPlayer*>
{
public:
	void OnBegin(cPlayer* pPlayer);

	void OnUpdate(cPlayer* pPlayer, float deltaTime);

	void OnEnd(cPlayer* pPlayer);
};