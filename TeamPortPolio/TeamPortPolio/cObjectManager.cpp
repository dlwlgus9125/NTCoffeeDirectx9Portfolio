#include "stdafx.h"
#include "cObjectManager.h"
#include "cTextureManager.h"
#include "cBallisticArrow.h"
#include "cCharacter.h"
#include "cObject.h"
#include "cPlayer.h"
#include "cLeader.h"
#include "cUnit.h"
#include "BallisticMotion.h"



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
	
	m_player = NULL;
	
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
	D3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	int count = 0;
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		
			/*if ((((cCharacter*)m_vecObject[i])->GetID() == C_C_HUMAN_MALE || ((cCharacter*)m_vecObject[i])->GetID() == C_C_ORC_MALE)||FRUSTUM->IsIn(&((cCharacter*)m_vecObject[i])->GetSphere()))
			{*/
				m_vecObject[i]->Render(); count++;
		//	}
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

	m_vecCharacter.clear();
	m_vecEntity.clear();
	m_vecObject.clear();
	for each(auto c in m_vecLeader)
	{
		if (((cCharacter*)c)->GetCamp() == CAMP_PLAYER) { c = NULL; }
		else { SAFE_DELETE(c); }
	}
	m_vecLeader.clear();
	SAFE_DELETE(m_player);
	m_player = NULL;
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

vector<int> cObjectManager::GetEquipment()
{
	return m_player->GetEquipment();
}

void cObjectManager::SellItem(int itemSID)
{
	m_player->SellItem(itemSID);
}

void cObjectManager::BuyItem(int itemSID)
{
	m_player->BuyItem(itemSID);
}

void cObjectManager::PutOnItem(int itemSID)
{
	m_player->PutOnItem(itemSID);
}

void cObjectManager::PutOffItem(int itemSID)
{
	m_player->PutOffItem(itemSID);
}

int cObjectManager::GetPlayerID() 
{ 
	return m_player->GetID();
}

void cObjectManager::ClearToChangeScene()
{
	m_vecCharacter.clear();
	m_vecEntity.clear();
	m_vecObject.clear();
	for each(auto c in m_vecLeader)
	{
		if (((cCharacter*)c)->GetCamp()== CAMP_PLAYER) { c = NULL; }
		else { SAFE_DELETE(c);  }
	}
	m_vecLeader.clear();
	ClearArrow();
}

void cObjectManager::SetCurrentLeader(LEADER_TYPE leaderType)
{
	m_player->SetCurrentLeader(leaderType);
	switch (leaderType)
	{
	case LEADER_MELEE:
		cout << "보병" << endl;
		break;
	case LEADER_BOW:
		cout << "궁병" << endl;
		break;
	case LEADER_CAVALRY:
		cout << "기병" << endl;
		break;
	}
}

int cObjectManager::GetCurrentLeaderType()
{
	return m_player->GetCurrentLeaderType();
}

float cObjectManager::GetPlayerHPRate()
{
	ST_Character* stat = m_player->GetStatus();
	return  (stat->m_HP) / (stat->m_MaxHP);
}

D3DXVECTOR2 cObjectManager::GetPlayerPosV2()
{
	if (!m_player) return D3DXVECTOR2(-2000, -2000);

	return D3DXVECTOR2(m_player->GetCharacterEntity()->Pos().x, m_player->GetCharacterEntity()->Pos().z);
}

D3DXVECTOR2 cObjectManager::GetUnitLeaderPosV2()
{
	D3DXVECTOR2 pos = D3DXVECTOR2(-2000, -2000);

	vector<cLeader*> vecLeader = GetLeader();
	for (int i = 0; i < vecLeader.size(); i++)
	{
		if (vecLeader[i]->GetCamp() == CAMP_PLAYER)
		{
			pos = D3DXVECTOR2(vecLeader[i]->GetCharacterEntity()->Pos().x, vecLeader[i]->GetCharacterEntity()->Pos().z);
		}
	}

	return pos;
}

D3DXVECTOR2 cObjectManager::GetEnemyLeaderPosV2()
{
	D3DXVECTOR2 pos = D3DXVECTOR2(-2000, -2000);

	vector<cLeader*> vecLeader = GetLeader();
	for (int i = 0; i < vecLeader.size(); i++)
	{
		if (vecLeader[i]->GetCamp() == CAMP_ENEMY1)
		{
			pos = D3DXVECTOR2(vecLeader[i]->GetCharacterEntity()->Pos().x, vecLeader[i]->GetCharacterEntity()->Pos().z);
		}
	}

	return pos;
}