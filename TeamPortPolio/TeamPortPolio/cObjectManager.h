#pragma once

class cObject;
class cCharacter;
class cUnit;
class cPlayer;
class cLeader;
class cSkinnedMesh;
class cBallisticArrow;
class BallisticMotion;

class IEntity;
#define OBJECT  cObjectManager::Instance()



class cObjectManager : public Singleton<cObjectManager>
{
	vector<cObject*>    m_vecObject;
	vector<IEntity*>    m_vecEntity;
	vector<cLeader*>    m_vecLeader;
	vector<cCharacter*> m_vecCharacter;

	cPlayer*        m_player;
	
	queue<cSkinnedMesh*> m_queFootman;

	list<cBallisticArrow*> m_listPlayerArrow;
	list<cBallisticArrow*> m_listUnitArrow;

	void PlayerArrow(cBallisticArrow * pArrow);
	void UnitArrow(cBallisticArrow * pArrow);
public:


	void Init();
	void Update(float deltaTime);
	void Render();
	void Release();

	void AddEntity(IEntity* entity);
	void AddObject(cObject* object);
	void AddLeader(cLeader* leader) { m_vecLeader.push_back(leader); };
	void SetPlayer(cPlayer* player) { m_player = player; }
	void AddCharacter(cCharacter* character) { m_vecCharacter.push_back(character); }

	vector<IEntity*> GetEntities() { return m_vecEntity; }
	vector<cLeader*> GetLeader() { return m_vecLeader; }
	vector<cCharacter*> GetCharacter() { return m_vecCharacter; }
	vector<cObject*> GetObjects() { return m_vecObject; }

	cPlayer* GetPlayer() { return m_player; }



	list<cBallisticArrow*> GetPlayerArrows();
	list<cBallisticArrow*> GetUnitArrows();
	void AddPlayerArrow(IEntity * pos, D3DXVECTOR3 forward);
	void AddUnitArrow(D3DXVECTOR3 PosOrigin, D3DXVECTOR3 PosTarget, CAMP_STATE camp);
	void ArrowUpdate();
	void ClearArrow();

	vector<int> GetInventory();
	vector<int> GetEquipment();
	void SellItem(int itemSID);
	void BuyItem(int itemSID);
	void PutOnItem(int itemSID);
	void PutOffItem(int itemSID);

	int GetPlayerID();

	void ClearToChangeScene();

	void SetCurrentLeader(LEADER_TYPE leaderType);
	int GetCurrentLeaderType();
	float GetPlayerHPRate();
	D3DXVECTOR2 GetPlayerPosV2();
	D3DXVECTOR2 GetUnitLeaderPosV2();
	D3DXVECTOR2 GetEnemyLeaderPosV2();
};

