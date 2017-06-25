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
	PLAYER_STATE_BOWATTACK,
	PLAYER_STATE_DEFENCE,
	PLAYER_STATE_DEFEAT,
};

enum CURRENT_ATTACKTYPE
{
	ATTACK_MELEE,
	ATTACK_BOW,
};

class cLeader;
class Player_State;
class cSkinnedMesh;
class cBallisticArrow;





class cPlayer :
	public cCharacter
{
private:
	cLeader*       m_currentLeader;//부대이동을 담당할 멤버변수

	//각 병종을 담을 맵
	map<int, cLeader*> m_mapLeader;
	LEADER_TYPE m_currentLeaderType;

	cSkinnedMesh*  m_SkinnedMesh;
	float          m_fRotY;
	cStateMachine<cPlayer*>* m_pFsm;


	cSkinnedMesh* m_RightWeaponMesh;
	cSkinnedMesh* m_LeftWeaponMesh;
	

	// >> 케릭터 아이템 저장
	SYNTHESIZE(vector<int>, m_vecInventory, Inventory);	// 인벤토리(가방)
	SYNTHESIZE(vector<int>, m_vecEquipment, Equipment); // 착용 아이템
	// << 

	//>>무기를 장착할 손의 좌표를 불러오기위한 주소값 그릇
	ST_BONE* m_rightHand;
	ST_BONE* m_leftHand;
	ST_BONE* m_AttackCollider;

	CURRENT_ATTACKTYPE m_AttackType;

	bool m_isPull;

	ST_SPHERE m_MeleeCollider;


	bool FLY;// 영상찍을라고 카메라 날릴라는 변수
	D3DXVECTOR3 FLYPos;
public:
	cPlayer(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed);
	~cPlayer();

	void Init();
	void Update(float deltaTime);
	void Render();
	
	void SetRotY(float rotY) { m_fRotY = rotY; }
	float GetRotY() { return m_fRotY; }
	//Scene에서 부대 이동을 관리할 겟함수
	cLeader*       GetUnitLeader() { return m_currentLeader; }
	void           SetCurrentLeader(LEADER_TYPE leaderTYPE) { m_currentLeaderType = leaderTYPE; m_currentLeader = m_mapLeader[(int)m_currentLeaderType]; }
	void           SetCurrentLeader() { m_currentLeader = m_mapLeader[(int)m_currentLeaderType]; }
	int			GetCurrentLeaderType() { return m_currentLeaderType;}

	// 추가
	cStateMachine<cPlayer*>* FSM() { return m_pFsm; }
	void SetUnitLeaderTargetIndex(int index);

	// >> 인벤토리용 함수
	void SellItem(int itemSID);
	void BuyItem(int itemSID);
	void PutOnItem(int itemSID);
	void PutOffItem(int itemSID);
	// <<

	void Equip();
	void UnEquip();

	//>>활당기는 모션
	void IsPullBow(bool pull) { m_isPull = pull; }
	cSkinnedMesh* GetBowSkin() { return m_LeftWeaponMesh; }
	// <<

	//>>칼 전투용 충돌체
	ST_SPHERE GetMeleeCollider() { return m_MeleeCollider; }

	D3DXVECTOR3 SetUpAim() {
		D3DXVECTOR3 vAim = CAMERA->GetLookAt() - CAMERA->GetEye();
	
		return	MATH->Nomalize(vAim);
	}

	CURRENT_ATTACKTYPE GetAttackType() { return m_AttackType; }
	void SetAttackColliderPos();

	bool AddUnitInTown(C_C_ID ID);



	void SetAnimBlock() { m_pSkinnedMesh->SetAnimationIndexBlend(P_SHEILDBLOCK); };
	void SetAnimHit() { m_pSkinnedMesh->SetAnimationIndexBlend(P_HIT); };
	void SetAnimDeath() { m_pFsm->Play(PLAYER_STATE_DEFEAT); };
	
	virtual void SetSceneEnter()
	{
		cCharacter::SetSceneEnter();
		m_pFsm->Play(PLAYER_STATE_IDLE);
		SetMode(IDLE_PLAYER_MODE);
		m_isPull = false;
	}

	int GetAllUnitSize();
};

