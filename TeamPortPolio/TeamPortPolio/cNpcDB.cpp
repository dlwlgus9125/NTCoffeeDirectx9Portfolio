#include "stdafx.h"
#include "cNpcDB.h"

void cNpcDB::Setup()
{
	Add(new ST_Npc(N_R_HUMAN, N_C_HUMAN_WEAPON, "obj/NPC/Human/Weapon/", "Blacksmith.X"));
	Add(new ST_Npc(N_R_HUMAN, N_C_HUMAN_ARMOR, "obj/NPC/Human/Armor/", "Citizenmid.X"));
	Add(new ST_Npc(N_R_HUMAN, N_C_HUMAN_STUFF, "obj/NPC/Human/Stuff/", "FemalePeasant.X"));
	Add(new ST_Npc(N_R_HUMAN, N_C_HUMAN_INN, "obj/NPC/Human/Inn/", "FemaleMerchant.X"));
	Add(new ST_Npc(N_R_HUMAN, N_C_HUMAN_RECRUIT, "obj/NPC/Human/Recruit/", "Warriormedium.X"));
	
	Add(new ST_Npc(N_R_ORC, N_C_ORC_WEAPON, "obj/NPC/Orc/Weapon/", "felorc_sword.X"));
	Add(new ST_Npc(N_R_ORC, N_C_ORC_ARMOR, "obj/NPC/Orc/Armor/", "orcmalewarriorlight.X"));
	Add(new ST_Npc(N_R_ORC, N_C_ORC_RECRUIT, "obj/NPC/Orc/Recruit/", "rexxar.X"));
	Add(new ST_Npc(N_R_ORC, N_C_ORC_STUFF, "obj/NPC/Orc/Stuff/", "orcmalekidgruntling.X"));
	Add(new ST_Npc(N_R_ORC, N_C_ORC_INN, "obj/NPC/Orc/Inn/", "orcmalemerchantlight.X"));

}

void cNpcDB::Add(ST_Npc * pData)
{
	if (m_mapNpc.find(pData->m_npcID) == m_mapNpc.end())
	{
		m_mapNpc[pData->m_npcID] = pData;
	}
}

void cNpcDB::Destroy()
{
	for each(auto p in m_mapNpc)
	{
		SAFE_DELETE(p.second);
	}
	m_mapNpc.clear();
	//delete this;
}
