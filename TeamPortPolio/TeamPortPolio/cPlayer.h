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
	cLeader*       m_unitLeader;//부대이동을 담당할 멤버변수
	cSkinnedMesh*  m_SkinnedMesh;
	float          m_fRotY;
	cStateMachine<cPlayer*>* m_pFsm;



	

	// >> 케릭터 아이템 저장
	SYNTHESIZE(vector<int>, m_vecInventory, Inventory);	// 인벤토리(가방)
	SYNTHESIZE(vector<int>, m_vecEquipment, Equipment); // 착용 아이템
	// << 

	//>>무기를 장착할 손의 좌표를 불러오기위한 주소값 그릇
	ST_BONE* m_rightHand;
	ST_BONE* m_leftHand;
	ST_BONE* m_AttackCollider;


public:
	cPlayer(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed);
	~cPlayer();

	void Init();
	void Update(float deltaTime);
	void Render();
	
	
	//Scene에서 부대 이동을 관리할 겟함수
	cLeader*       GetUnitLeader() { return m_unitLeader; }

	// 추가
	cStateMachine<cPlayer*>* FSM() { return m_pFsm; }
	void SetUnitLeaderTargetIndex(int index);

	// >> 인벤토리용 함수
	void SellItem(int itemSID);
	void ByuItem(int itemSID);

	void EquipRightHand(int itemSID);
	void EquipLeftHand(int itemSID);
	// <<

	D3DXVECTOR3 SetUpAim() {
		D3DXVECTOR3 vAim = CAMERA->GetLookAt() - CAMERA->GetEye();
		vAim.y += 1;
		return	MATH->Nomalize(vAim);
	}



};

