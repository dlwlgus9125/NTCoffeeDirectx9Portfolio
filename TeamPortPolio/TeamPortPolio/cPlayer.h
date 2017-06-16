#pragma once
#include "cCharacter.h"
#include "cUnit.h"
#include "cFrustum.h"
#include "Player_State.h"

enum PLAYER_STATE
{
	PLAYER_STATE_IDLE,
	PLAYER_STATE_WALK,
	PLAYER_STATE_ATTACK,
	PLAYER_STATE_DEFENCE,
};

class cLeader;
class Player_State;
class cSkinnedMesh;
class cBallisticArrow;
class cPlayer :
	public cCharacter
{
private:
	cLeader*       m_unitLeader;//�δ��̵��� ����� �������
	cSkinnedMesh*  m_SkinnedMesh;
	float          m_fRotY;
	cStateMachine<cPlayer*>* m_pFsm;


	//ȭ��ó�� ������ �޽�ǥ�ú�����
	cBallisticArrow* m_pBalisticArrow;
	LPD3DXMESH				m_pMeshSphere;
	D3DMATERIAL9			m_stMtlSphere;
public:
	cPlayer(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed);
	~cPlayer();

	void Init();
	void Update(float deltaTime);
	void Render();
	

	//Scene���� �δ� �̵��� ������ ���Լ�
	cLeader*       GetUnitLeader() { return m_unitLeader; }

	// �߰�
	cStateMachine<cPlayer*>* FSM() { return m_pFsm; }
	void SetUnitLeaderTargetIndex(int index);
};
