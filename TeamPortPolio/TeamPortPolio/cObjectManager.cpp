#include "stdafx.h"
#include "cObjectManager.h"
#include "cTextureManager.h"
#include "cObject.h"
#include "cPlayer.h"
#include "cLeader.h"
#include "cUnit.h"
//#include "IEntity.h"



void cObjectManager::Init()
{


	/*cLeader* pEnemy = new cLeader(D3DXVECTOR3(0, 0, 50), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pEnemy->Init();
	m_vecObject.push_back(pEnemy);
	m_vecEnemyLeader.push_back(pEnemy);

	cLeader* pEnemy1 = new cLeader(D3DXVECTOR3(50, 0, 0), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pEnemy1->Init();
	m_vecObject.push_back(pEnemy1);
	m_vecEnemyLeader.push_back(pEnemy1);

	cLeader* pEnemy2 = new cLeader(D3DXVECTOR3(-50, 0, 0), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pEnemy2->Init();
	m_vecObject.push_back(pEnemy2);
	m_vecEnemyLeader.push_back(pEnemy2);

	cLeader* pEnemy3 = new cLeader(D3DXVECTOR3(0, 0, -50), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 200);
	pEnemy3->Init();
	m_vecObject.push_back(pEnemy3);
	m_vecEnemyLeader.push_back(pEnemy3);*/
}

void cObjectManager::Update(float deltaTime)
{
	//m_player->Update(deltaTime);
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->Update(deltaTime);
	}
}

void cObjectManager::Render()
{
	//LPD3DXFRAME test = new D3DXFRAME;
	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		if(FRUSTUM->IsIn(m_vecObject[i]->GetCharacterEntity()->Pos()))m_vecObject[i]->Render();
	}
}

void cObjectManager::Release()
{
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		delete m_vecObject[i];
	}
	m_vecObject.clear();
}

void cObjectManager::AddEntity(IEntity * entity)
{
	m_vecEntity.push_back(entity);
}

void cObjectManager::AddObject(cObject * object)
{
	m_vecObject.push_back(object);
}


