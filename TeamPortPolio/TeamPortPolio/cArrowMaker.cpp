#include "stdafx.h"
#include "cArrowMaker.h"
cArrowMaker::cArrowMaker()
{
}

cArrowMaker::~cArrowMaker()
{
}

cBallisticArrow* cArrowMaker::MakePlayerArrow(IEntity * pos, D3DXVECTOR3 forward)
{
	cBallisticArrow* pArrow = new cBallisticArrow(pos->Pos(), D3DXVECTOR3(), forward);
	return pArrow;
}

cBallisticArrow* cArrowMaker::MakeUnitArrow(D3DXVECTOR3 PosOrigin, D3DXVECTOR3 PosTarget)
{
	cBallisticArrow* pArrow = new cBallisticArrow(PosOrigin, PosTarget, D3DXVECTOR3());
	return pArrow;
}
