#include "stdafx.h"
#include "cCharacterDB.h"

void cCharacterDB::Setup()
{
	//Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_SHORTSWORD, "¼ô ¼Òµå", "°¡Àå ÈçÇÑ ÂªÀº °ËÀÌ´Ù.", 50, ""));
	/*m_MaxHP = 100.0f;
	m_HP = 100.0f;
	m_Damage = 20.0f;
	m_defence = 4;*/

	Add(new ST_Character(C_R_HUMAN, C_G_MALE, C_C_HUMAN_MALE, 100.0f, 100.f, 100.0f, 4, "Character/Player/", "C_Human.X", "RHand_Bone_Col_root"));
	Add(new ST_Character(C_R_ORC, C_G_MALE, C_C_ORC_MALE, 100.0f, 100.f, 100.0f, 4, "Character/Player/", "C_Orcman.X", "RHand_Bone_Col_root"));


	Add(new ST_Character(C_R_HUMAN, C_G_MALE, C_C_HUMAN_MELEE, 100.0f, 100.f, 20.0f, 4, "Character/BloodeHuman/", "b_footman.x", "Sword_2H_Broadsword_A_03_Bone08"));
	Add(new ST_Character(C_R_HUMAN, C_G_MALE, C_C_HUMAN_BOWMAN, 100.0f, 100.f, 20.0f, 4, "Character/BloodeHuman/", "b_bowman.x", "Sword_2H_Broadsword_A_03_Bone08"));
	Add(new ST_Character(C_R_HUMAN, C_G_MALE, C_C_HUMAN_CAVALRY, 100.0f, 100.f, 100.0f, 4, "Character/BloodeHuman/", "b_knightman.x", "Sword_2H_Broadsword_A_03_Bone08"));


	Add(new ST_Character(C_R_ORC, C_G_MALE, C_C_ORC_MELEE, 100.0f, 100.f, 20.0f, 4, "Character/Orc/", "orc_Grunt.x", "Axe_2H_Gorehowl_D_01_Bone04"));
	Add(new ST_Character(C_R_ORC, C_G_MALE, C_C_ORC_BOWMAN, 100.0f, 100.f, 20.0f, 4, "Character/Orc/", "orc_Bow.x", "Sword_2H_Broadsword_A_03_Bone08"));
	Add(new ST_Character(C_R_ORC, C_G_MALE, C_C_ORC_CAVALRY, 100.0f, 100.f, 20.0f, 4, "Character/Orc/", "orc_gronn.x", "Sword_2H_Broadsword_A_03_Bone08"));

	Add(new ST_Character(C_R_END, C_G_END, C_C_ARROW_ARROW, 100.0f, 100.f, 50.0f, 4, "Character/Weapon/", "arrow.x", "Arrow"));
	Add(new ST_Character(C_R_END, C_G_END, C_C_SWORD_SWORD, 100.0f, 100.f, 100.0f, 4, "Character/Weapon/", "Weapon_Sword1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_Character(C_R_END, C_G_END, C_C_BOW_BOW, 100.0f, 100.f, 100.0f, 4, "Character/Weapon/", "WeaponBow.x", "Weapon_Attack_Bone_Col_root"));

	Add(new ST_Character(C_R_END, C_G_END, C_C_SHIELD_SHIELD, 100.0f, 100.f, 100.0f, 4, "Character/Weapon/", "Sheild_Blood1.x", "Weapon_Attack_Bone_Col_root"));
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
	m_mapCharacter.clear();
	//delete this;
}
