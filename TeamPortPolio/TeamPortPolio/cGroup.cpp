#include "stdafx.h"
#include "cGroup.h"


cGroup::cGroup()
	: m_pMtlTex(NULL)
{
}

cGroup::~cGroup()
{
	SAFE_RELEASE(m_pMtlTex);
}

void cGroup::Render()
{
	if (m_pMtlTex)
	{
		D3DDevice->SetTexture(0, m_pMtlTex->GetTexture());
		D3DDevice->SetMaterial(&m_pMtlTex->GetMaterial());
	}

	D3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PNT_VERTEX));
}