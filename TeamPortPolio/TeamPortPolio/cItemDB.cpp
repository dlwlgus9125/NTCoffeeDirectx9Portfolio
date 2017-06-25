#include "stdafx.h"
#include "cItemDB.h"

void cItemDB::Setup()
{
	//Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_SHORTSWORD, "숏 소드", "가장 흔한 짧은 검이다.", 50, "image/item/sword/shortsword.png"));
	//Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_LONGSWORD, "롱 소드", "평범한 긴 검이다.", 250, "image/item/sword/longsword.png"));
	//Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_BASTARDSWORD, "바스타드 소드", "중세 양날 검이다.", 750, "image/item/sword/bastardsword.png"));
	//Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_SMALLAXE, "짧은 도끼", "싸우기엔 짧은 도끼.", 50, "image/item/axe/ShortAxe.png"));
	//Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_WARAXE, "전투 도끼", "고기 썰 정도의 도끼.", 250, "image/item/axe/WarAxe.png"));
	//Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_TWOHANDAXE, "양날 도끼", "양날로 싸우기 좋은 도끼.", 750, "image/item/axe/TH_axe.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD,I_S_SWORD_SHORT_NOR, "단검", "평범한 단검", 100, "image/item/sword/sword1.png", "Character/Weapon/", "Weapon_Sword1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD,I_S_SWORD_SHORT_ECH,"강화된 단검","조금 강해진 단검", 250, "image/item/sword/sword1_2.png", "Character/Weapon/", "Weapon_Sword1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD,I_S_SWORD_SHORT_GLZ,"빛나는 단검","꽤 강하지만 단검", 400, "image/item/sword/sword1_3.png", "Character/Weapon/", "Weapon_Sword1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD,I_S_SWORD_LONG_NOR,"장검", "평범하고 긴 검", 500, "image/item/sword/sword2.png", "Character/Weapon/", "Weapon_Sword1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD,I_S_SWORD_LONG_ECH, "강화된 장검", "강화되어 싸우기 좋은 장검", 700, "image/item/sword/sword2_2.png", "Character/Weapon/", "Weapon_Sword1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD,I_S_SWORD_MITHRIL_NOR,"미스릴검", "뽀대나는 미스릴 검", 1000, "image/item/sword/sword3.png", "Character/Weapon/", "Weapon_Sword1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD,I_S_SWORD_MITHRIL_ECH,"강화된 미스릴검", "뽀대나고 센 미스릴검", 1500, "image/item/sword/sword3_2.png", "Character/Weapon/", "Weapon_Sword1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD,I_S_SWORD_MITHRIL_GLZ,"빛나는 미스릴검", "상대방의 눈까지 머는 미스릴검", 2000, "image/item/sword/sword3_3.png", "Character/Weapon/", "Weapon_Sword1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_AXE_STONE,"돌 도끼", "구석기 시대 유물같은 도끼", 90, "image/item/axe/axe1.png", "Character/Weapon/", "WeaponAxe.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_AXE_IRON_NOR, "철 도끼", "나름 신석기 시대에 잘나갔던 도끼", 400,"image/item/axe/axe2.png", "Character/Weapon/", "WeaponAxe.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_AXE_IRON_HQ, "강화된 철도끼", "강화되어 두드려 패기 좋은 도끼", 500, "image/item/axe/axe2_2.png", "Character/Weapon/", "WeaponAxe.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_AXE_MITHRIL_NOR,"미스릴 도끼","미스릴을 입혀 싸우기 좋은 도끼", 1000, "image/item/axe/axe3.png", "Character/Weapon/", "WeaponAxe.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_AXE_MITHRIL_HQ, "강화된 미스릴 도끼", "강화되어 두명씩 때리기 좋은 도끼", 1500, "image/item/axe/axe3_2.png", "Character/Weapon/", "WeaponAxe.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_AXE_HAND_RUST,"빛 바랜 손도끼","손 맛 좋은 도끼", 200, "image/item/axe/axe4.png", "Character/Weapon/", "WeaponAxe.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_AXE_HAND_HQ,"빛나는 손도끼","눈 부시지만 그래도 손도끼", 300, "image/item/axe/axe4_1.png", "Character/Weapon/", "WeaponAxe.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_AXE_HONORABLE,"명예로운 손도끼","도끼에 깃든 명예로 비싼 도끼", 700, "image/item/axe/axe4_2.png", "Character/Weapon/", "WeaponAxe.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_RANGE, I_M_BOW, I_S_BOW_WOODEN_NOR,"나무 활","연습용 활", 100 , "image/item/bow/bow1.png", "Character/Weapon/", "WeaponBow.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_RANGE, I_M_BOW, I_S_BOW_WOODEN_ECH,"강화된 나무 활","장거리 연습으로 좋은 활", 200, "image/item/bow/bow2.png", "Character/Weapon/", "WeaponBow.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_RANGE, I_M_BOW, I_S_BOW_WOODEN_GLZ,"빛나는 나무 활","남들에게 자랑하기 위한 활", 350, "image/item/bow/bow2_2.png", "Character/Weapon/", "WeaponBow.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_RANGE, I_M_BOW, I_S_BOW_HUNTER_NOR,"사냥꾼의 활","토끼 사냥에 쓸만할 활", 500, "image/item/bow/bow3.png", "Character/Weapon/", "WeaponBow.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_RANGE, I_M_BOW, I_S_BOW_HUNTER_GLZ,"빛나는 사냥꾼의 활", "멧돼지 잡기에 좋은 활", 700, "image/item/bow/bow3_2.png", "Character/Weapon/", "WeaponBow.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_RANGE, I_M_BOW, I_S_BOW_ELF_NOR,"엘프족의 활","적군을 멀리서 저격하기 좋은 활", 1100, "image/item/bow/bow4.png", "Character/Weapon/", "WeaponBow.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_RANGE, I_M_BOW, I_S_BOW_ELF_ECH,"강화된 엘프족의 활","방패까지 뚫어버릴 활", 1350, "image/item/bow/bow4_2.png", "Character/Weapon/", "WeaponBow.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_RANGE, I_M_BOW, I_S_BOW_ELF_GLZ,"빛나는 엘프족장의 활","적장의 심장을 뚫는 활", 1600, "image/item/bow/bow4_3.png", "Character/Weapon/", "WeaponBow.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_ARMOR, I_S_ARMOR_OLD,"허름한 갑옷","맨 살만 가려주는 갑옷", 150, "image/item/armor/chest1.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_ARMOR, I_S_ARMOR_PLATED,"도금된 갑옷","감쪽같이 철갑옷으로 보이는 갑옷", 400, "image/item/armor/chest1_2.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_ARMOR, I_S_ARMOR_MAGIC,"마력의 갑옷","30년 모솔의 마력이 깃든 갑옷", 650, "image/item/armor/chest1_3.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_ARMOR, I_S_ARMOR_DWARFMITHRIL,"드워프제 미스릴 갑옷","드워프 동네에서 수입한 갑옷", 1000, "image/item/armor/chest1_4.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_ARMOR, I_S_ARMOR_SOLDEIER_RUST,"빛 바랜 병사 갑옷","보세로 수입된 병사용 갑옷", 1300, "image/item/armor/chest2.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_ARMOR, I_S_ARMOR_SOLDEIER_GLZ,"빛나는 병사 갑옷","전투를 위해 갓 제작된 병사용 갑옷", 1800, "image/item/armor/chest2_2.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_ARMOR, I_S_ARMOR_GENERAL_RUST,"빛 바랜 장군 갑옷","튼튼하지만 남이 쓰다 버린 갑옷", 2500, "image/item/armor/chest3.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_ARMOR, I_S_ARMOR_GENERAL_GLZ,"빛 나는 장군 갑옷","천하를 호령할 장군을 위한 갑옷", 4000, "image/item/armor/chest3_2.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SHIELD, I_S_SHIELD_WOODEN_NOR,"나무 방패","훈련용 방패", 100, "image/item/shield/shield1.png", "Character/Weapon/", "Sheild_Blood1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SHIELD, I_S_SHIELD_WOODEN_IRONOVER,"철 덧댄 나무 방패","철을 덧대어 단단한 방패",250, "image/item/shield/shield1_2.png", "Character/Weapon/", "Sheild_Blood1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SHIELD, I_S_SHIELD_WOODEN_ECH,"강화된 나무 방패","상대의 주먹을 방어할 방패",400, "image/item/shield/shield1_3.png", "Character/Weapon/", "Sheild_Blood1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SHIELD, I_S_SHIELD_WOODEN_GLZ,"빛나는 나무 방패","빛나서 예쁜 방패",700, "image/item/shield/shield1_4.png", "Character/Weapon/", "Sheild_Blood1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SHIELD, I_S_SHIELD_IRON_NOR,"철 방패","전투용 기본 방패",1100, "image/item/shield/shield2.png", "Character/Weapon/", "Sheild_Blood1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SHIELD, I_S_SHIELD_IRON_RUST,"빛 바랜 철 방패","수 많은 전투를 겪은 방패", 1300, "image/item/shield/shield2_2.png", "Character/Weapon/", "Sheild_Blood1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SHIELD, I_S_SHIELD_IRON_GLZ,"빛나는 철 방패","전장에서 돋보이는 강한 방패", 1600, "image/item/shield/shield2_3.png", "Character/Weapon/", "Sheild_Blood1.x", "Weapon_Attack_Bone_Col_root"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SHIELD, I_S_SHIELD_HONORABLE,"명예로운 방패","용맹한 장군을 위한 방패", 2200, "image/item/shield/shield3.png", "Character/Weapon/", "Sheild_Blood1.x", "Weapon_Attack_Bone_Col_root"));
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
	m_mapObject.clear();
	//delete this;
}