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
	//>>목표 타겟 평소엔 NULL
	cObject*         m_targetObject;
	//<<
	int              m_currentIndex;

	MeshSpere        m_MeshSphere;
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
	void             SetAttackColliderPos();

	void             SetDeath(bool death) { m_isDeath = death; }
	bool             IsDeath() { return m_isDeath; }

	FIGHT_STATE      Fight(cCharacter* attacker, cCharacter* defender);
	ST_Character*    GetStatus() { return m_Status; }


	virtual void SetAnimBlock() {};
	virtual void SetAnimHit() {};
	virtual void SetAnimDeath() {};

	void SetID(C_C_ID id) { m_ID = id; }

};

