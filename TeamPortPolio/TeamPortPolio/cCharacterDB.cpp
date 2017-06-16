#include "stdafx.h"
#include "cCharacterDB.h"

void cCharacterDB::Setup()
{
	//Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_SHORTSWORD, "¼ô ¼Òµå", "°¡Àå ÈçÇÑ ÂªÀº °ËÀÌ´Ù.", 50, ""));
	/*m_MaxHP = 100.0f;
	m_HP = 100.0f;
	m_Damage = 20.0f;
	m_defence = 4;*/
	Add(new ST_Character(C_R_HUMAN, C_G_MALE, C_C_HUMAN_MALE, 100.0f, 100.f, 20.0f, 4, "Character/BloodeHuman/", "b_footman.x", "Sword_2H_Broadsword_A_03_Bone08"));
	Add(new ST_Character(C_R_HUMAN, C_G_MALE, C_C_HUMAN_BOWMAN, 100.0f, 100.f, 20.0f, 4, "Character/BloodeHuman/", "b_bowman.x", "Sword_2H_Broadsword_A_03_Bone08"));


	Add(new ST_Character(C_R_ORC, C_G_MALE, C_C_ORC_MELEE, 100.0f, 100.f, 20.0f, 4, "Character/Orc/", "orc_Grunt.x", "Axe_2H_Gorehowl_D_01_Bone04"));
	Add(new ST_Character(C_R_HUMAN, C_G_MALE, C_C_ORC_BOWMAN, 100.0f, 100.f, 20.0f, 4, "Character/Orc/", "orc_Bow.x", "Sword_2H_Broadsword_A_03_Bone08"));
}

void cCharacterDB::Add(ST_Character * pData)
{
	if (m_mapCharacter.find(pData->m_characterID) == m_mapCharacter.end())
	{
		m_mapCharacter[pData->m_characterID] = pData;
	}
}

void cCharacterDB::Destroy()
{
	for each(auto it in m_mapCharacter)
	{
		SAFE_DELETE(it.second);
	}

	delete this;
}
