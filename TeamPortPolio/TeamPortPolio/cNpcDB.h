#pragma once

#define NPCDB cNpcDB::Instance()

enum N_R_ID
{
	N_R_HUMAN,
	N_R_ORC,
	N_R_END,
};

enum N_P_ID
{
	N_P_HUMAN_WEAPON,
	N_P_HUMAN_DEFFEND,
	N_P_HUMAN_POSITION,
	N_P_HUMAN_MOTEL,
	N_P_HUMAN_WARRIOR,
	N_P_HUMAN_CITIZEN1,
	N_P_HUMAN_CITIZEN2,
	N_P_HUMAN_CITIZEN3,
	N_P_HUMAN_CITIZEN4,

	N_P_BOUNDARY = 9,

	N_P_ORC_WEAPON,
	N_P_ORC_DEFFEND,
	N_P_ORC_POSITION,
	N_P_ORC_MOTEL,
	N_P_ORC_WARRIOR,
	N_P_ORC_CITIZEN1,
	N_P_ORC_CITIZEN2,
	N_P_ORC_CITIZEN3,
};

struct ST_NPC
{
	N_R_ID m_raceID;
	N_P_ID m_npcID;
	char*  m_szPath;
	char*  m_szFileName;
	char*  m_szColliderBoneName;

	ST_NPC(N_R_ID raceID, N_P_ID npcID,
		char* szPath, char* szFileName, char* ColliderBoneName)
	{
		m_raceID = raceID;
		m_npcID = npcID;
		m_szPath = szPath;
		m_szFileName = szFileName;
		m_szColliderBoneName = ColliderBoneName;
	}

	ST_NPC(const ST_NPC& npcDB)
	{
		m_raceID = npcDB.m_raceID;
		m_npcID = npcDB.m_npcID;
		m_szPath = npcDB.m_szPath;
		m_szFileName = npcDB.m_szFileName;
		m_szColliderBoneName = npcDB.m_szColliderBoneName;
	}
};

class cNpcDB : public Singleton<cNpcDB>
{
protected:
	map<int, ST_NPC*> m_mapNPC;
public:
	void Setup();
	void Add(ST_NPC* pData);
	void Destroy();
	ST_NPC* GetMapNPC(int npcID) { return m_mapNPC[npcID]; }
};

