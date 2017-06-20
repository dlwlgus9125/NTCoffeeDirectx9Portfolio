#include "stdafx.h"
#include "cNpcDB.h"

void cNpcDB::Setup()
{
	Add(new ST_NPC(N_R_HUMAN, N_P_HUMAN_WEAPON, "Object/Npc/Human/Weapon/", "b_weapon.x", "asdasd"));
	Add(new ST_NPC(N_R_HUMAN, N_P_HUMAN_DEFFEND, "Object/Npc/Human/Armor/", "b_armor.x", "asdasd"));
	Add(new ST_NPC(N_R_HUMAN, N_P_HUMAN_POSITION, "Object/Npc/Human/Stuff/", "b_stuff.x", "asdasd"));
	Add(new ST_NPC(N_R_HUMAN, N_P_HUMAN_MOTEL, "Object/Npc/Human/Inn/", "b_inn.x", "asdasd"));
	Add(new ST_NPC(N_R_HUMAN, N_P_HUMAN_WARRIOR, "Object/Npc/Human/Recuit/", "b_recuit.x", "asdasd"));
	Add(new ST_NPC(N_R_HUMAN, N_P_HUMAN_CITIZEN1, "Object/Npc/Human/Resident1/", "b_resident1.x", "asdasd"));
	Add(new ST_NPC(N_R_HUMAN, N_P_HUMAN_CITIZEN2, "Object/Npc/Human/Resident2/", "b_resident2.x", "asdasd"));
	Add(new ST_NPC(N_R_HUMAN, N_P_HUMAN_CITIZEN3, "Object/Npc/Human/Resident3/", "b_resident3.x", "asdasd"));
	Add(new ST_NPC(N_R_HUMAN, N_P_HUMAN_CITIZEN4, "Object/Npc/Human/Resident4/", "b_resident4.x", "asdasd"));


	Add(new ST_NPC(N_R_ORC, N_P_ORC_WEAPON, "Object/Npc/Orc/Weapon/", "b_weapon.x", "asdasd"));
	Add(new ST_NPC(N_R_ORC, N_P_ORC_DEFFEND, "Object/Npc/Orc/Armor/", "b_armor.x", "asdasd"));
	Add(new ST_NPC(N_R_ORC, N_P_ORC_POSITION, "Object/Npc/Orc/Stuff/", "b_stuff.x", "asdasd"));
	Add(new ST_NPC(N_R_ORC, N_P_ORC_MOTEL, "Object/Npc/Orc/Inn/", "b_inn.x", "asdasd"));
	Add(new ST_NPC(N_R_ORC, N_P_ORC_WARRIOR, "Object/Npc/Orc/Recuit/", "b_recuit.x", "asdasd"));
	Add(new ST_NPC(N_R_ORC, N_P_ORC_CITIZEN1, "Object/Npc/Orc/Resident1/", "b_resident1.x", "asdasd"));
	Add(new ST_NPC(N_R_ORC, N_P_ORC_CITIZEN2, "Object/Npc/Orc/Resident2/", "b_resident2.x", "asdasd"));
	Add(new ST_NPC(N_R_ORC, N_P_ORC_CITIZEN2, "Object/Npc/Orc/Resident3/", "b_resident3.x", "asdasd"));

}

void cNpcDB::Add(ST_NPC * pData)
{
	if (m_mapNPC.find(pData->m_npcID) == m_mapNPC.end())
	{
		m_mapNPC[pData->m_npcID] = pData;
	}
}

void cNpcDB::Destroy()
{
	for each(auto p in m_mapNPC)
	{
		SAFE_DELETE(p.second);
	}
	delete this;
}
