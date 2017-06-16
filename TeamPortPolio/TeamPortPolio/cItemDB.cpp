#include "stdafx.h"
#include "cItemDB.h"

void cItemDB::Setup()
{
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_SHORTSWORD, "숏 소드", "가장 흔한 짧은 검이다.", 50, "image/item/sword/shortsword.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_LONGSWORD, "롱 소드", "평범한 긴 검이다.", 250, "image/item/sword/longsword.png"));
	Add(new ST_ITEM(I_L_MELEE, I_M_SWORD, I_S_BASTARDSWORD, "바스타드 소드", "중세 양날 검이다.", 750, "image/item/sword/bastardsword.png"));
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