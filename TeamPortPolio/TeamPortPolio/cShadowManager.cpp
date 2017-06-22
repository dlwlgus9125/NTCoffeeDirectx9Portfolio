#include "stdafx.h"
#include "cShadowManager.h"
#include "cMtlTex.h"
#include "cObjLoader.h"

cShadowManager::cShadowManager()
{
}


cShadowManager::~cShadowManager()
{
}

D3DMATERIAL9 cShadowManager::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = a;
	mtrl.Diffuse = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power = p;
	return mtrl;
}

void cShadowManager::Setup(std::vector<cConstruct*>& vecList)
{
	m_vecConstruct = vecList;
}

void cShadowManager::SetLightDir(D3DXVECTOR3 dir)
{
	m_shadowLight = dir;
}

void cShadowManager::Render()
{
	D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DDevice->Clear(NULL, NULL, D3DCLEAR_STENCIL, D3DCOLOR_XRGB(47, 121, 112), 1.0f, 0);
	D3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	D3DDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	D3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	D3DDevice->SetRenderState(D3DRS_STENCILREF, 0x0);
	D3DDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	D3DDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);

	D3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	D3DDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	D3DDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	D3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	for (int i = 0; i < m_vecConstruct.size(); i++)
	{

		D3DXPLANE groundPlane(0.0f, -1.0f, 0.0f, m_vecConstruct[i]->GetPosition().y + 0.001f);

		D3DXVECTOR4 lightTest(-m_shadowLight.x, -m_shadowLight.y, -m_shadowLight.z, 0.0f);

		D3DXMATRIX S;
		D3DXMatrixShadow(
			&S,
			&lightTest,
			&groundPlane);

		D3DXMATRIXA16 matRY;
		D3DXMatrixRotationY(&matRY, m_vecConstruct[i]->GetRotationY());

		D3DXMATRIX T;
		D3DXMatrixTranslation(
			&T,
			m_vecConstruct[i]->GetPosition().x, m_vecConstruct[i]->GetPosition().y, m_vecConstruct[i]->GetPosition().z);

		D3DXMATRIXA16 matS;
		D3DXMatrixScaling(&matS, m_vecConstruct[i]->GetScale().x, m_vecConstruct[i]->GetScale().y, m_vecConstruct[i]->GetScale().z);

		D3DXMATRIX W = matS*matRY *T * S;

		D3DDevice->SetTransform(D3DTS_WORLD, &W);

		D3DMATERIAL9 mtrl = InitMtrl(D3DCOLOR_XRGB(0, 0, 0), D3DCOLOR_XRGB(0, 0, 0), D3DCOLOR_XRGB(0, 0, 0), D3DCOLOR_XRGB(0, 0, 0), 0.0f);
		if (m_alpha == NULL)
			mtrl.Diffuse.a = 0.5f;
		else
			mtrl.Diffuse.a = m_alpha;
		
		for (int j = 0; j < m_vecConstruct[i]->GetVecObjMtlTex().size(); j++)
		{
			D3DDevice->SetMaterial(&mtrl);
			D3DDevice->SetTexture(0, 0);
			m_vecConstruct[i]->GetObjMesh()->DrawSubset(j);
		}
	}

	D3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	D3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	D3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	D3DDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void cShadowManager::SetAlpha(float alpha)
{
	m_alpha = alpha;
}

void cShadowManager::Destroy()
{

}


