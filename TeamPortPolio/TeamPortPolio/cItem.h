#pragma once
#include "cObject.h"
class cItem : public cObject
{
	SYNTHESIZE(string, m_sName,ItemName);
	SYNTHESIZE(ITEM_TAG, m_eTag, ItemTag);
	//>>
	SYNTHESIZE(int, m_Atk, ItemAtk);
	SYNTHESIZE(int, m_Def, ItemDef);
	//<<
public:
	cItem();
	~cItem();
	void SetItem(ITEM_TAG key);

};
