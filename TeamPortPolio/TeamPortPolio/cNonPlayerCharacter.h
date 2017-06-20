#pragma once
#include "cObject.h"
#include "cSkinnedMesh.h"

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

class cNonPlayerCharacter  : public cObject
{
private:
	
protected:
	D3DXVECTOR3                          m_vPosition;
	float                                m_speed;
	float                                m_fRotY;

	//선택되었나 안되었나.
	bool                                 m_isPicked;

	//NPC 종류
	NPC_KINDS                            m_kind;

	//상태처리
	NPC_STATE                            m_state;

	//충돌처리 구체
	ST_SPHERE                            m_pSphere;

	//이동 경로 
	std::vector<D3DXVECTOR3>             m_path;

	cSkinnedMesh*                        m_pSkinnedMesh;

public:
	cNonPlayerCharacter(D3DXVECTOR3 pos, float moveSpeed, float rot, NPC_KINDS kind);
	~cNonPlayerCharacter();

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();

	void MovePosition(D3DXVECTOR3 pos, float speed);
	void SetPath(D3DXVECTOR3 pos);
	void AutoMoveAI(vector<D3DXVECTOR3> path);

	NPC_STATE State() { return m_state; }
	D3DXVECTOR3 Postiion() { return m_vPosition; }
	ST_SPHERE Sphere() { return m_pSphere; }
	vector<D3DXVECTOR3> Path() { return m_path; }

	//Manager 
	//void ChangeNpc(int Scene_Tag) { tag = Scene_tag;}
	// SAFE_RELEASE(vector<NPC>) 해주고
	// 새로 생성
	// tag 값마다 Setup이 다 다르게 시켜준다.

};

