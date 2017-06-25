#pragma once

#define NPCDB cNpcDB::Instance()

enum N_R_ID
{
	N_R_HUMAN,
	N_R_ORC,
	N_R_END,
};

enum N_C_ID
{
	N_C_HUMAN_WEAPON = 117,
	N_C_HUMAN_ARMOR,
	N_C_HUMAN_STUFF,
	N_C_HUMAN_INN,
	N_C_HUMAN_RECRUIT,

	N_C_TEN_NONE,

	N_C_ORC_WEAPON = 128,
	N_C_ORC_ARMOR,
	N_C_ORC_STUFF,
	N_C_ORC_INN,
	N_C_ORC_RECRUIT,
};

struct ST_Npc
{
	N_R_ID m_raceID;
	N_C_ID m_npcID;
	char* m_szPath;
	char* m_szFileName;

	ST_Npc() {};
	ST_Npc(N_R_ID raceID, N_C_ID npcID, char* szPath, char* szFileName)
	{
		m_raceID = raceID;
		m_npcID = npcID;
		m_szPath = szPath;
		m_szFileName = szFileName;
	}
	ST_Npc(const ST_Npc& NpcDB)
	{
		m_raceID = NpcDB.m_raceID;
		m_npcID = NpcDB.m_npcID;
		m_szPath = NpcDB.m_szPath;
		m_szFileName = NpcDB.m_szFileName;
	}
};

class cNpcDB : public Singleton<cNpcDB>
{
protected:
	map<int, ST_Npc*> m_mapNpc;
public:
	void Setup();
	void Add(ST_Npc* pData);
	void Destroy();
	ST_Npc* GetMapNpc(int npcID) { return m_mapNpc[npcID]; }
};

