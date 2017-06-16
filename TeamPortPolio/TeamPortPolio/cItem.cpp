#include "stdafx.h"
#include "cItem.h"

cItem::cItem()
	:m_sName(NULL)
	,m_eTag(ITEM_NONE)
	//>>아이템 스테이터스
	,m_Atk(0)
	,m_Def(0)
{

}

cItem::~cItem()
{
}

void cItem::SetItem(ITEM_TAG key)
{
	SetItemTag(key);
	switch (m_eTag)
	{
	case ITEM_NONE: SetItemAtk(0), SetItemDef(0), SetItemName("none"); break;
	case ITEM_MELEE:SetItemAtk(0), SetItemDef(0), SetItemName("Sword"); break;
	case ITEM_RANGE:SetItemAtk(0), SetItemDef(0), SetItemName("Bow"); break;
	}
}
