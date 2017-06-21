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
}

void cNpcManager::Render()
{
	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, m_vecSphere[i].vCenter.x, m_vecSphere[i].vCenter.y + 0.7f, m_vecSphere[i].vCenter.z);
		D3DDevice->SetTransform(D3DTS_WORLD, &matT);
		
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
	
}
