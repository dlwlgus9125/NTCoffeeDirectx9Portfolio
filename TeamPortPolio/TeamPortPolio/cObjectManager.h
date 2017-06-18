#pragma once

class cObject;
class cCharacter;
class cUnit;
class cPlayer;
class cLeader;
class cSkinnedMesh;
class cBallisticArrow;

class IEntity;
#define OBJECT  cObjectManager::Instance()



class cObjectManager : public Singleton<cObjectManager>
{
	vector<cObject*>    m_vecObject;
	vector<IEntity*>    m_vecEntity;
	vector<cLeader*>    m_vecLeader;
	vector<cCharacter*> m_vecCharacter;
	vector<cBallisticArrow*> m_vecArrow;
	list<cBallisticArrow*> m_UnitArrow;
	list<cBallisticArrow*> m_PlayerArrow;
	cPlayer*        m_player;
	
	queue<cSkinnedMesh*> m_queFootman;


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

	cPlayer* GetPlayer() { return m_player; }

	void AddArrowByPlayer(cBallisticArrow* pArrow);
	void AddArrowByUnit(cBallisticArrow* pArrow, CAMP_STATE camp);

	void DeleteArrows();

	vector<int> GetInventory();
	void SellItem(int itemSID);
	void ByuItem(int itemSID);
};

