#pragma once
#include "cObject.h"

class cSkinnedMesh;


//상태
enum NPC_STATE
{
	NPC_NONE,
	NPC_IDLE,
	NPC_WALK,
};

//NPC종류
enum NPC_KINDS
{
	NPC_NONE,
	NPC_STORE, //상점
	NPC_CITIZEN, // 걸어다니는놈
};

class cNonPlayerCharacter  : public cCharacter
{
private:
	
protected:
	float                               m_fRotY;
	cSkinnedMesh*                       m_SkinnedMesh;
	cStateMachine<cNonPlayerCharacter*> m_pFsm;

public:
	cNonPlayerCharacter(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward);
	~cNonPlayerCharacter();

	void Init();
	void Update(float deltaTime);
	void Render();

	cStateMachine<cNonPlayerCharacter*> FSM() { return m_pFsm; }
};

