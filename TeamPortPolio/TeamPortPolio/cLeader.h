#pragma once
#include "cCharacter.h"
#include "Leader_State.h"

enum LEADER_STATE
{
	LEADER_STATE_MELEE_IDLE,
	LEADER_STATE_MELEE_WALK,
	LEADER_STATE_MELEE_BATTLE,
	LEADER_STATE_MELEE_DEFENCE,

	LEADER_STATE_BOW_IDLE,
	LEADER_STATE_BOW_WALK,
	LEADER_STATE_BOW_BATTLE,

	LEADER_STATE_CAVALRY_IDLE,
	LEADER_STATE_CAVALRY_WALK,
	LEADER_STATE_CAVALRY_BATTLE,


	LEADER_STATE_DEFEAT,
};




class cUnit;
class cMeleeUnit;
class cBowUnit;
class cCavalryUnit;

class cLeader :
	public cCharacter
{
	cStateMachine<cLeader*>* m_pFsm;
	ISteeringEntity*  m_unitLeader;//부대이동을 담당할 멤버변수
	vector<cUnit*> m_vectorUnit;
	vector<D3DXVECTOR3> m_RectOffest;
	vector<D3DXVECTOR3> m_TriOffest;
	float          m_fRotY;
	int            m_targetIndex;
	vector<int>    m_path;
	MeshSpere      m_meshSphere;

	LEADER_TYPE    m_type;
	LEADER_STATE   m_TypeStart;
	float          m_velocity;
public:
	cLeader(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed);
	~cLeader();

	void Init();
	void Update(float deltaTime);
	void Render();
	void AddUnit(cUnit* pUnit);
	bool AddUnitInTown(C_C_ID ID);
	void AddUnitInManager();
	void DeleteDeathUnitInExitScene();
	//부대 추가
	void DeleteUnit(int key);

	void SetRectOffset();
	void SetTriOffset();
	void SetAttackMode();
	void SetDefendMode();

	//Scene에서 부대 이동을 관리할 겟함수
	cStateMachine<cLeader*>* FSM() { return m_pFsm; }
	IEntity*       GetUnitLeader() { return m_unitLeader; }
	vector<cUnit*> GetUnits() { return m_vectorUnit; }

	
	void             SetPath(vector<int> path) { if (!path.empty()) { m_path.clear();  m_path = path; } }
	vector<int>      GetPath() { return m_path; }
	void             SetTargetIndex(int i) { m_targetIndex = i; }
	int              GetTargetIndex() { return m_targetIndex; }

	void             SetMeleeType();
	void             SetBowType();
	void             SetCavalryType();

	void             SetType();

	void             ClickedButtonOne();
	void             ClickedButtonTwo();

	void             PathPopBack() { m_path.pop_back(); }
	void             PathClear() 
	{
		for (int i = 0; i < m_path.size(); i++)m_path.pop_back();

		m_path.clear(); 
	}

	float            GetVelocity() { return m_velocity; }
	void             AddVelocity(float force) { m_velocity += force; m_velocity=MATH->Clamp(m_velocity, 0.0f, 0.05f); }
	void             SetVelocity(float velocity) { m_velocity = velocity; m_velocity= MATH->Clamp(m_velocity, 0.0f, 0.05f);
	}

	void SetSceneEnter()
	{
		cCharacter::SetSceneEnter();
		m_pFsm->Play(m_TypeStart);
	}
};

