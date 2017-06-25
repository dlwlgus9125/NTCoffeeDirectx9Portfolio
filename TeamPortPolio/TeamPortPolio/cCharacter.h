#pragma once
#include "ISteeringEntity.h"
#include "cCharacterDB.h"
#include "cSkinnedMesh.h"
#include "cObject.h"

enum FIGHT_STATE
{
	FIGHT_HIT,
	FIGHT_BLOCK,
};




class cCharacter : public cObject
{
	
protected:
	C_C_ID           m_ID;
	ISteeringEntity* m_CharacterEntity;
	ST_SPHERE        m_CollideSphere;
	ST_SPHERE        m_arrangeCollideSphere;
	ST_SPHERE        m_AttackCollideSphere;
	cSkinnedMesh*    m_pSkinnedMesh;

	MODE_STATE       m_currentMode;
	ST_Character*    m_Status;
	bool             m_isDeath;
	bool			 m_isAiming;
	bool			 m_isShoot;
	//>>목표 타겟 평소엔 NULL
	cObject*         m_targetObject;
	//<<
	int              m_currentIndex;
	CAMP_STATE       m_camp;
	MeshSpere        m_MeshSphere;

	bool             m_isAnimDeath;
	bool             m_isEquiped;
	vector<cConstruct*>	m_vecNearConstruct;
	cConstruct* m_pTargetConstruct;
	
public:
	cCharacter();
	virtual ~cCharacter();

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();

	ST_SPHERE        GetSphere() { return m_CollideSphere; }
	ST_SPHERE        GetArrangeSphere() { return m_arrangeCollideSphere; }
	ISteeringEntity* GetCharacterEntity() { return m_CharacterEntity; }
	cSkinnedMesh*    GetMesh() { return m_pSkinnedMesh; }
	MODE_STATE       GetMode() { return m_currentMode; }

	void             SetMode(int mode) { m_currentMode = (MODE_STATE)mode; }
	int              GetIndex() { return m_currentIndex; }
	void             SetIndex(int index) { m_currentIndex = index; }
	void             RenderSphere();

	cObject*         GetTargetObject() { return m_targetObject; }
	void             SetTargetObject(cObject* object) { m_targetObject = object; }

	//전투용 충돌 체크
	ST_SPHERE        GetAttackCollider() { return m_AttackCollideSphere; }
	virtual void     SetAttackColliderPos();

	void             SetDeath(bool death) { m_isDeath = death; }
	bool             IsDeath() { return m_isDeath; }

	FIGHT_STATE      Fight(cCharacter* attacker, cCharacter* defender);
	ST_Character*    GetStatus() { return m_Status; }

	//>>진영 설정
	void             SetCamp(int camp) { m_camp = (CAMP_STATE)camp; }
	CAMP_STATE       GetCamp() { return m_camp; }

	virtual void SetAnimBlock() {};
	virtual void SetAnimHit() {};
	virtual void SetAnimDeath() {};

	C_C_ID GetID() { return m_ID; }
	void SetID(C_C_ID id) { m_ID = id; }
	MeshSpere GetMeshSphere() { return m_MeshSphere; }


	bool isAnimDeath() {};

	void UpdateNearConstruct();

	virtual void SetSceneEnter()
	{
		m_Status->m_HP = m_Status->m_MaxHP;
		m_CharacterEntity->SetDeath(false);
		m_isDeath = false;
	}
	

	D3DMATERIAL9 m_mtrl;
	
};

