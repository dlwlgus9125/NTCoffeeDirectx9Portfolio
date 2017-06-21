#pragma once

#define CHARACTERDB cCharacterDB::Instance()

//종족
enum C_R_ID
{
	C_R_HUMAN,
	C_R_ORC,
	C_R_END,
};

//성별
enum C_G_ID
{
	C_G_MALE,
	C_G_FEMALE,
	C_G_END,
};

enum C_C_ID
{
	C_C_HUMAN_MALE,
	C_C_HUMAN_FEMALE,
	C_C_ORC_MALE,
	C_C_ORC_FEMALE,
	C_C_HUMAN_MELEE,
	C_C_HUMAN_BOWMAN,
	C_C_HUMAN_CAVALRY,
	C_C_ORC_MELEE,
	C_C_ORC_BOWMAN,
	C_C_ORC_CAVALRY,

	C_C_ARROW_ARROW,
	C_C_SWORD_SWORD,
	C_C_SHIELD_SHIELD,
	C_C_BOW_BOW,
};

struct ST_Character
{
	C_R_ID     m_raceID;
	C_G_ID     m_genderID;
	C_C_ID     m_characterID;
	float      m_MaxHP;
	float      m_HP;
	float      m_Damage;
	int        m_defence;
	char*      m_szPath;
	char*      m_szFileName;
	char*      m_szColliderBoneName;

	ST_Character() {};
	ST_Character(C_R_ID raceID, C_G_ID genderID, C_C_ID characterID, float MaxHP, float HP, float damage, float defence, 
		         char* szPath, char* szFileName, char* ColliderBoneName)
	{
		m_raceID             = raceID;
		m_genderID           = genderID;
		m_characterID        = characterID;
		m_MaxHP              = MaxHP;
		m_HP                 = HP;
		m_Damage             = damage;
		m_defence            = defence;
		m_szPath             = szPath;
		m_szFileName         = szFileName;
		m_szColliderBoneName = ColliderBoneName;
	}
	ST_Character(const ST_Character& characterDB)
	{
		m_raceID              = characterDB.m_raceID;
		m_genderID            = characterDB.m_genderID;
		m_characterID         = characterDB.m_characterID;
		m_MaxHP               = characterDB.m_MaxHP;
		m_HP                  = characterDB.m_HP;
		m_Damage              = characterDB.m_Damage;
		m_defence             = characterDB.m_defence;
		m_szPath              = characterDB.m_szPath;
		m_szFileName          = characterDB.m_szFileName;
		m_szColliderBoneName  = characterDB.m_szColliderBoneName;
	}


	void SetHP(float Damage) { m_HP = MATH->Clamp(m_HP + Damage, 0.0f, m_MaxHP); }
	void SetDefence(int defence) { m_defence = defence; }
};
class cCharacterDB : public Singleton<cCharacterDB>
{
	map<int, ST_Character*> m_mapCharacter;
public:
	void Setup();
	void Add(ST_Character* pData);
	void Destroy();
	ST_Character* GetMapCharacter(int characterID) { return m_mapCharacter[characterID]; }
};



