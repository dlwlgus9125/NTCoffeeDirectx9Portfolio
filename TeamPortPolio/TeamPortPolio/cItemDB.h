#pragma once

#define ITEMDB cItemDB::Instance()

//´ëºÐ·ù
enum I_L_ITEMID
{
	I_L_NONE, 
	I_L_MELEE,
	I_L_RANGE,
	I_L_END,
};

enum I_M_ITEMID
{
	I_M_SWORD,
	I_M_SHEILD,
	I_M_AXE,
	I_M_BOW,
	I_M_INVENTORY,
	I_M_END,
};

enum I_S_ITEMID
{
	I_S_SHORTSWORD,
	I_S_LONGSWORD,
	I_S_BASTARDSWORD,
	I_S_SHEILD,
	I_S_SHORTBOW,
	I_S_LONGBOW,
	I_S_SMALLAXE,
	I_S_WARAXE,
	I_S_TWOHANDAXE,
	I_S_END,
};



struct ST_ITEM
{
	I_L_ITEMID eLargeID;
	I_M_ITEMID eMiddleID;
	I_S_ITEMID eSmallID;
	string name;
	string info;
	int cost;


	char* szImagePath;

	char* szXfilePath;
	char* szXfileName;
	cSkinnedMesh* weaponSkinnedMesh;


	ST_ITEM(I_L_ITEMID L_ID, I_M_ITEMID M_ID, I_S_ITEMID S_ID, string name, string info, int cost, char* szImagePath, char* szXfilePath, char* szXfileName, cSkinnedMesh* weaponSkinnedMesh=NULL)
	{
		eLargeID = L_ID;
		eMiddleID = M_ID;
		eSmallID = S_ID;
		this->name = name;
		this->info = info;
		this->cost = cost;
		this->szImagePath = szImagePath;
		this->szXfilePath = szXfilePath;
		this->szXfileName = szXfileName;
		this->weaponSkinnedMesh = weaponSkinnedMesh;
	}
};

class cItemDB : public Singleton<cItemDB>
{
	map<int, ST_ITEM*> m_mapObject;
public:
	void Setup();
	void Add(ST_ITEM* pData);
	void Destroy();
	ST_ITEM* GetItem(int smallID) { return m_mapObject[smallID]; }
};
