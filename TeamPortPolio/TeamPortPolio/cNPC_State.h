#pragma once
#include "cNonPlayerCharacter.h"

class Npc_Idle : public IState<cNonPlayerCharacter*>
{

public:
	void OnBegin(cNonPlayerCharacter* pPlayer);

	void OnUpdate(cNonPlayerCharacter* pPlayer, float deltaTime);

	void OnEnd(cNonPlayerCharacter* pPlayer);
};

class Npc_Walk : public IState<cNonPlayerCharacter*>
{

public:
	void OnBegin(cNonPlayerCharacter* pPlayer);

	void OnUpdate(cNonPlayerCharacter* pPlayer, float deltaTime);

	void OnEnd(cNonPlayerCharacter* pPlayer);

	void StateChanger(cNonPlayerCharacter* pPlayer, D3DXVECTOR3 prevPos, D3DXVECTOR3 movePos);

	void Move(cNonPlayerCharacter* pPlayer);
};
