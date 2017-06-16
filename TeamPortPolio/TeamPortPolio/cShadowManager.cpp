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

void cShadowManager::Setup(std::vector<cConstruct*> vecList)
{
	SetLight();
	m_vecConstruct = vecList;

}

void cShadowManager::Render()
{
	D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DDevice->Clear(NULL, NULL, D3DCLEAR_STENCIL, D3DCOLOR_XRGB(47, 121, 112), 1.0f, 0);
	for (int i = 0; i < m_vecConstruct.size(); i++)
	{

		D3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		D3DDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		D3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

		D3DDevice->SetRenderState(D3DRS_STENCILREF, 0x0);
		D3DDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
		D3DDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);

		D3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
		D3DDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		D3DDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

		D3DXPLANE groundPlane(0.0f, -1.0f, 0.0f, 0.0f);

		D3DXVECTOR4 lightTest(-m_light.Direction.x, -m_light.Direction.y, -m_light.Direction.z, 0.0f);

		D3DXMATRIX S;
		D3DXMatrixShadow(
			&S,
			&lightTest,
			&groundPlane);

		D3DXMATRIX T;
		D3DXMatrixTranslation(
			&T,
			m_vecConstruct[i]->GetPosition().x, m_vecConstruct[i]->GetPosition().y, m_vecConstruct[i]->GetPosition().z);

		D3DXMATRIXA16 matS;
		D3DXMatrixScaling(&matS, m_vecConstruct[i]->GetScale().x, m_vecConstruct[i]->GetScale().y, m_vecConstruct[i]->GetScale().z);

		D3DXMATRIX W = matS *T * S;

		D3DDevice->SetTransform(D3DTS_WORLD, &W);

		D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		D3DMATERIAL9 mtrl = InitMtrl(D3DCOLOR_XRGB(0, 0, 0), D3DCOLOR_XRGB(0, 0, 0), D3DCOLOR_XRGB(0, 0, 0), D3DCOLOR_XRGB(0, 0, 0), 0.0f);
		mtrl.Diffuse.a = 0.5f; // 50% transparency.

							   // Disable depth buffer so that z-fighting doesn't occur when we
							   // render the shadow on top of the floor.


		D3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

		for (int j = 0; j < m_vecConstruct[i]->GetVecObjMtlTex().size(); j++)
		{
			D3DDevice->SetMaterial(&mtrl);
			D3DDevice->SetTexture(0, 0);
			m_vecConstruct[i]->GetObjMesh()->DrawSubset(j);
		}

		D3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

		D3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		D3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		D3DDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
		D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	}
	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void cShadowManager::Destroy()
{

}

void cShadowManager::SetLight()
{
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));

	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);            // 주변에 영향을 받는 것들은 색을 띄게 만듬
	m_light.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_light.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3   vDir(1.0f, 1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	m_light.Direction = vDir;
	D3DDevice->SetLight(0, &m_light);
	D3DDevice->LightEnable(0, true);
}
