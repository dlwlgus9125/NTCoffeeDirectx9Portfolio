#include "stdafx.h"
#include "cItem.h"

cItem::cItem()
	:m_sName(NULL)
	,m_eTag(I_L_NONE)
	//>>아이템 스테이터스
	,m_Atk(0)
	,m_Def(0)
{

}

cItem::~cItem()
{
}

void cItem::SetItem(I_L_ITEMID key)
{
	SetItemTag(key);
	switch (m_eTag)
	{
	case I_L_NONE: SetItemAtk(0), SetItemDef(0), SetItemName("none"); break;
	case I_L_MELEE:SetItemAtk(0), SetItemDef(0), SetItemName("Sword"); break;
	case I_L_RANGE:SetItemAtk(0), SetItemDef(0), SetItemName("Bow"); break;
	}
}
