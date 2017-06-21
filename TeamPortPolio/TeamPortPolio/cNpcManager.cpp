#include "stdafx.h"
#include "cNpcManager.h"


cNpcManager::cNpcManager()
{
}


cNpcManager::~cNpcManager()
{
}

void cNpcManager::Init(std::vector<ST_NPC_INFO> vecNpc)
{
	m_vecNpc = vecNpc;
	m_vecSphere.resize(m_vecNpc.size());
	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		m_vecSphere[i].fRadius = 0.7f;
		m_vecSphere[i].vCenter = m_vecNpc[i].pos;
	}
	D3DXCreateSphere(D3DDevice, 0.7f, 10, 10, &m_pMesh, NULL);
	SetMtrl();
}

void cNpcManager::Render()
{
	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, m_vecSphere[i].vCenter.x, m_vecSphere[i].vCenter.y + 0.7f, m_vecSphere[i].vCenter.z);
		D3DDevice->SetTransform(D3DTS_WORLD, &matT);
		D3DDevice->SetTexture(0, NULL);
		D3DDevice->SetFVF(ST_PN_VERTEX::FVF);
		D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		if (i == 0 || i == 1 || i == 3 || i == 4)
		{
			m_mtrl.Ambient = D3DXCOLOR(1.0F, 0.0F, 0.0F, 1.0F);
			D3DDevice->SetMaterial(&m_mtrl);
		}
		else
		{
			m_mtrl.Ambient = D3DXCOLOR(0.0F, 1.0F, 0.0F, 1.0F);
			D3DDevice->SetMaterial(&m_mtrl);
		}
		m_pMesh->DrawSubset(0);
	}
}

void cNpcManager::Update(std::vector<ST_NPC_INFO> vecNpc)
{
	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		m_vecSphere[i].vCenter = m_vecNpc[i].pos;
	}
}

void cNpcManager::Release()
{
	m_vecNpc.clear();
	delete &m_vecNpc;
	m_vecSphere.clear();
	delete &m_vecSphere;
	SAFE_RELEASE(m_pMesh);
}

void cNpcManager::SetMtrl()
{
	ZeroMemory(&m_mtrl, sizeof(D3DMATERIAL9));
	m_mtrl.Diffuse = D3DXCOLOR(1.0F, 0.0F, 0.0F, 1.0F);
	m_mtrl.Specular = D3DXCOLOR(1.0F, 0.0F, 0.0F, 1.0F);
}
