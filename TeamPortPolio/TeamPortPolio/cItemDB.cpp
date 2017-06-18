#include "stdafx.h"
#include "cItemDB.h"

void cItemDB::Setup()
{
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_SHORTSWORD, "¼ô ¼Òµå", "°¡Àå ÈçÇÑ ÂªÀº °ËÀÌ´Ù.", 50, "image/item/sword/shortsword.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_LONGSWORD, "·Õ ¼Òµå", "Æò¹üÇÑ ±ä °ËÀÌ´Ù.", 250, "image/item/sword/longsword.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_BASTARDSWORD, "¹Ù½ºÅ¸µå ¼Òµå", "Áß¼¼ ¾ç³¯ °ËÀÌ´Ù.", 750, "image/item/sword/bastardsword.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_SMALLAXE, "ÂªÀº µµ³¢", "½Î¿ì±â¿£ ÂªÀº µµ³¢.", 50, "image/item/axe/ShortAxe.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_WARAXE, "ÀüÅõ µµ³¢", "°í±â ½ä Á¤µµÀÇ µµ³¢.", 250, "image/item/axe/WarAxe.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_AXE, I_S_TWOHANDAXE, "¾ç³¯ µµ³¢", "¾ç³¯·Î ½Î¿ì±â ÁÁÀº µµ³¢.", 750, "image/item/axe/TH_axe.png"));
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