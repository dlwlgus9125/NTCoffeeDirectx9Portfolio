#include "stdafx.h"
#include "cItemDB.h"

void cItemDB::Setup()
{
	/*Add(new ST_Character(C_R_END, C_G_END, C_C_SWORD_SWORD, 100.0f, 100.f, 100.0f, 4, "Character/Weapon/", "Weapon_Sword1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_Character(C_R_END, C_G_END, C_C_SHIELD_SHIELD, 100.0f, 100.f, 100.0f, 4, "Character/Weapon/", "Sheild_Blood1.x", "Weapon_Attack_Bone_Col_root"));*/
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_SHORTSWORD, "숏 소드", "가장 흔한 짧은 검이다.", 50, "image/item/sword/shortsword.png"," "," "));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_LONGSWORD, "롱 소드", "평범한 긴 검이다.", 250, "image/item/sword/longsword.png", " ", " "));

	//>>실제 착용 가능한 무기
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_BASTARDSWORD, "바스타드 소드", "중세 양날 검이다.", 750, "image/item/sword/bastardsword.png", "Character/Weapon/", "Weapon_Sword1.x", TEXTURE->GetCharacterResource("Character/Weapon/", "Weapon_Sword1.x")));
	Add(new ST_ITEM(I_L_MELEE, I_M_SHEILD, I_S_SHEILD, "카이트 쉴드", "중세 기사 방패이다.", 750, "image/item/sword/bastardsword.png", "Character/Weapon/", "Sheild_Blood1.x", TEXTURE->GetCharacterResource("Character/Weapon/", "Sheild_Blood1.x")));
	
	
	Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_SMALLAXE, "짧은 도끼", "싸우기엔 짧은 도끼.", 50, "image/item/axe/ShortAxe.png", " ", " "));
	Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_WARAXE, "전투 도끼", "고기 썰 정도의 도끼.", 250, "image/item/axe/WarAxe.png", " ", " "));
	Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_TWOHANDAXE, "양날 도끼", "양날로 싸우기 좋은 도끼.", 750, "image/item/axe/TH_axe.png", " ", " "));
}

void cItemDB::Add(ST_ITEM * pData)
{
	if (m_mapObject.find(pData->eSmallID) == m_mapObject.end())
	{
		m_mapObject[pData->eSmallID] = pData;
	}
}

void cItemDB::Destroy()
{
	for each(auto it in m_mapObject)
	{
		SAFE_DELETE(it.second);
	}

	delete this;
}