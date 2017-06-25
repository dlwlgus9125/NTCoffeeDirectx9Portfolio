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
	I_M_AXE,
	I_M_BOW,
	I_M_ARMOR,
	I_M_SHIELD,
	I_M_HELM,
	I_M_BOOTS,
	I_M_INVENTORY,
	I_M_END,
};

enum I_S_ITEMID
{
	I_S_SWORD_SHORT_NOR,
	I_S_SWORD_SHORT_ECH,
	I_S_SWORD_SHORT_GLZ,
	I_S_SWORD_LONG_NOR,
	I_S_SWORD_LONG_ECH,
	I_S_SWORD_MITHRIL_NOR,
	I_S_SWORD_MITHRIL_ECH,
	I_S_SWORD_MITHRIL_GLZ,
	I_S_AXE_STONE,
	I_S_AXE_IRON_NOR,
	I_S_AXE_IRON_HQ,
	I_S_AXE_MITHRIL_NOR,
	I_S_AXE_MITHRIL_HQ,
	I_S_AXE_HAND_RUST,
	I_S_AXE_HAND_HQ,
	I_S_AXE_HONORABLE,
	I_S_BOW_WOODEN_NOR,
	I_S_BOW_WOODEN_ECH,
	I_S_BOW_WOODEN_GLZ,
	I_S_BOW_HUNTER_NOR,
	I_S_BOW_HUNTER_GLZ,
	I_S_BOW_ELF_NOR,
	I_S_BOW_ELF_ECH,
	I_S_BOW_ELF_GLZ,
	I_S_ARMOR_OLD,
	I_S_ARMOR_PLATED,
	I_S_ARMOR_MAGIC,
	I_S_ARMOR_DWARFMITHRIL,
	I_S_ARMOR_SOLDEIER_RUST,
	I_S_ARMOR_SOLDEIER_GLZ,
	I_S_ARMOR_GENERAL_RUST,
	I_S_ARMOR_GENERAL_GLZ,
	I_S_SHIELD_WOODEN_NOR,
	I_S_SHIELD_WOODEN_IRONOVER,
	I_S_SHIELD_WOODEN_ECH,
	I_S_SHIELD_WOODEN_GLZ,
	I_S_SHIELD_IRON_NOR,
	I_S_SHIELD_IRON_RUST,
	I_S_SHIELD_IRON_GLZ,
	I_S_SHIELD_HONORABLE,

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


	char* szTexturePath;
	char* szTextureFileName;
	char* szColliderBoneName;


	ST_ITEM(I_L_ITEMID L_ID, I_M_ITEMID M_ID, I_S_ITEMID S_ID, string name, string info, int cost,
		char* szImagePath, char* szTexturePath = "", char* szTextureFileName = "", char* szColliderBoneName = "")
	{
		eLargeID = L_ID;
		eMiddleID = M_ID;
		eSmallID = S_ID;
		this->name = name;
		this->info = info;
		this->cost = cost;
		this->szImagePath = szImagePath;
		this->szTexturePath = szTexturePath;
		this->szTextureFileName = szTextureFileName;
		this->szColliderBoneName = szColliderBoneName;
	}
	~ST_ITEM() {}
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
