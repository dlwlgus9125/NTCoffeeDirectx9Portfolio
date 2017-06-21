#include "stdafx.h"
#include "cObjectManager.h"
#include "cTextureManager.h"
#include "cBallisticArrow.h"
#include "cObject.h"
#include "cPlayer.h"
#include "cLeader.h"
#include "cUnit.h"
#include "BallisticMotion.h"
//#include "IEntity.h"



void cObjectManager::PlayerArrow(cBallisticArrow * pArrow)
{
	m_listPlayerArrow.push_back(pArrow);
}

void cObjectManager::UnitArrow(cBallisticArrow * pArrow)
{
	m_listUnitArrow.push_back(pArrow);
	if (m_listUnitArrow.size() > 1000) ClearArrow();
}

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
	for each (auto p in OBJECT->GetPlayerArrows())
	{
		p->Init();
	}

	for each (auto p in OBJECT->GetUnitArrows())
	{
		p->Init();
	}
	
}

void cObjectManager::Update(float deltaTime)
{
	//m_player->Update(deltaTime);
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->Update(deltaTime);
	}
	ArrowUpdate();
}

void cObjectManager::Render()
{
	//LPD3DXFRAME test = new D3DXFRAME;
	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		if(FRUSTUM->IsIn(m_vecObject[i]->GetCharacterEntity()->Pos()))m_vecObject[i]->Render();
	}	

	for each (auto p in OBJECT->GetPlayerArrows())
	{
		p->Render();
	}

	for each (auto p in OBJECT->GetUnitArrows())
	{
		p->Render();
	}
}

void cObjectManager::Release()
{

	for (int i = 0; i < m_vecObject.size(); i++)
	{
		delete m_vecObject[i];
	}
	m_vecObject.clear();
	ClearArrow();
}

void cObjectManager::AddEntity(IEntity * entity)
{
	m_vecEntity.push_back(entity);
}

void cObjectManager::AddObject(cObject * object)
{
	m_vecObject.push_back(object);
}



list<cBallisticArrow*> cObjectManager::GetPlayerArrows()
{
	return m_listPlayerArrow;
}

list<cBallisticArrow*> cObjectManager::GetUnitArrows()
{
	return m_listUnitArrow;
}

void cObjectManager::AddPlayerArrow(IEntity * pos, D3DXVECTOR3 forward)
{
	cBallisticArrow* pArrow = new cBallisticArrow(pos->Pos(), D3DXVECTOR3(), forward);
	pArrow->SetCamp(CAMP_PLAYER);
	//pArrow->SetID(C_C_ARROW_ARROW);
	PlayerArrow(pArrow);

}

void cObjectManager::AddUnitArrow(D3DXVECTOR3 PosOrigin, D3DXVECTOR3 PosTarget, CAMP_STATE camp)
{
	//cout << PosTarget.x << "  " << PosTarget.y << " " << PosTarget.z << endl;
	PosTarget.x=  PosTarget.x+ (-5.0f + (rand() % 10)+1.0f) / 5.0f;
	PosTarget.z= PosTarget.z + (-5.0f+(rand() % 10)+1.0f) / 5.0f;
	PosTarget.y = PosTarget.y + (-5.0f + (rand() % 10) + 1.0f) / 5.0f;
	cBallisticArrow* pArrow = new cBallisticArrow(PosOrigin, PosTarget, D3DXVECTOR3());
	pArrow->SetCamp(camp);
	
	UnitArrow(pArrow);
}

void cObjectManager::ArrowUpdate()
{
	for each(auto p in m_listUnitArrow)
	{
		p->Shoot()->Update_with_targetpos();
		p->ArrowUpdate();
	}

	for each(auto p in m_listPlayerArrow)
	{
		p->Shoot()->Update_with_dir();
		p->ArrowUpdate();
	}
}

void cObjectManager::ClearArrow()
{
	while (!m_listPlayerArrow.empty())
	{
		SAFE_DELETE(m_listPlayerArrow.front());
		m_listPlayerArrow.pop_front();
	}

	while (!m_listUnitArrow.empty())
	{
		SAFE_DELETE(m_listUnitArrow.front());
		m_listUnitArrow.pop_front();
	}
}

vector<int> cObjectManager::GetInventory()
{
	return m_player->GetInventory();
}

void cObjectManager::SellItem(int itemSID)
{
	m_player->SellItem(itemSID);
}

void cObjectManager::BuyItem(int itemSID)
{
	m_player->ByuItem(itemSID);
}

void cObjectManager::PutOnItem(int itemSID)
{
	m_player->PutOnItem(itemSID);
}

void cObjectManager::PutOffItem(int itemSID)
{
	m_player->PutOffItem(itemSID);
}