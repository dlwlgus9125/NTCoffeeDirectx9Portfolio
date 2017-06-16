#pragma once
#include "cObject.h"
#include "cMtlTex.h"

class cGroup :
	public cObject
{
public:
	cGroup();
	~cGroup();

private:
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);
public:
	void Render();

};