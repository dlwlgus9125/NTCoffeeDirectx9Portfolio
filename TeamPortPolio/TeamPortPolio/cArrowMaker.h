#pragma once
#include "Singleton.h"
#include "cBallisticArrow.h"

#define ARROW cArrowMaker::Instance()

class cArrowMaker :public Singleton<cArrowMaker>
{
public:
	cArrowMaker();
	~cArrowMaker();

	cBallisticArrow * MakePlayerArrow(IEntity * pos, D3DXVECTOR3 forward);
	cBallisticArrow * MakeUnitArrow(D3DXVECTOR3 PosOrigin, D3DXVECTOR3 PosTarget);
};
