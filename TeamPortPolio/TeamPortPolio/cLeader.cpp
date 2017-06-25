#include "stdafx.h"
#include "cLeader.h"
#include "cMeleeUnit.h"
#include "cBowUnit.h"
#include "cCavalryUnit.h"
#include "cPlayer.h"

cLeader::cLeader(D3DXVECTOR3 pos, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed)

{
	m_CharacterEntity = new ISteeringEntity(pos, 0.5f, forward, mass, maxSpeed);
	m_unitLeader = m_CharacterEntity;
	m_fRotY = 0.0f;
	m_CharacterEntity->SetForward(-m_CharacterEntity->Forward());
	m_targetIndex = m_currentIndex;
	m_camp = CAMP_NONE;
	m_velocity = 0.0f;
}


cLeader::~cLeader()
{
	SAFE_RELEASE(m_meshSphere.m_pMeshSphere);
	for each(auto v in m_vectorUnit)
	{
		SAFE_DELETE(v);
	}
	m_vectorUnit.clear();
	SAFE_DELETE(m_unitLeader);
	SAFE_DELETE(m_pFsm);
}

void cLeader::Init()
{

	m_CollideSphere.fRadius = 0.1f;
	m_CollideSphere.vCenter = m_CharacterEntity->Pos();



	m_arrangeCollideSphere.fRadius = 20.0f;
	m_arrangeCollideSphere.vCenter = m_CharacterEntity->Pos();
	cCharacter::Init();

	for (float z = -2.0f; z <= 1.0f; z++)
	{
		for (float x = 2.0f; x >= -2.0f; x--)
		{
			m_RectOffest.push_back(D3DXVECTOR3(x, 0, z) * 3.0f);
		}
	}
	m_RectOffest.push_back(D3DXVECTOR3(2, 0, 2) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(0, 0, -4.0f) * 3.0f);

	m_TriOffest.push_back(D3DXVECTOR3(0.5f, 0, -3.0f) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(-0.5f, 0, -3.0f) * 3.0f);

	m_TriOffest.push_back(D3DXVECTOR3(0.0f, 0, -2.0f) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(-1.0f, 0, -2.0f) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(1.0f, 0, -2.0f) * 3.0f);


	m_TriOffest.push_back(D3DXVECTOR3(1.5f, 0, -1.0f) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(0.5f, 0, -1.0f) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(-0.5f, 0, -1.0f) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(-1.5f, 0, -1.0f) * 3.0f);

	m_TriOffest.push_back(D3DXVECTOR3(2.0f, 0, 0.0f) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(1.0f, 0, 0.0f) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(0.0f, 0, 0.0f) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(-1.0f, 0, 0.0f) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(-2.0f, 0, 0.0f) * 3.0f);

	m_TriOffest.push_back(D3DXVECTOR3(2.0f, 0, 1.0f) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(1.0f, 0, 1.0f) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(0.0f, 0, 1.0f) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(-1.0f, 0, 1.0f) * 3.0f);
	m_TriOffest.push_back(D3DXVECTOR3(-2.0f, 0, 1.0f) * 3.0f);

	m_pFsm = new cStateMachine<cLeader*>(this);
	SetType();

	m_pFsm->Register(LEADER_STATE_DEFEAT, new Leader_State_Defeat());
	m_pFsm->Play(m_TypeStart);
	m_meshSphere.m_vCenter = m_arrangeCollideSphere.vCenter;
	D3DXCreateSphere(D3DDevice, m_arrangeCollideSphere.fRadius, 10, 10, &m_meshSphere.m_pMeshSphere, NULL);
	ZeroMemory(&m_meshSphere.m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_meshSphere.m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_meshSphere.m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_meshSphere.m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	SetRectOffset();
}

void cLeader::Update(float deltaTime)
{
	if (m_isDeath == true)
	{
		if (m_pFsm->CurrentID() != LEADER_STATE_DEFEAT)m_pFsm->Play(LEADER_STATE_DEFEAT);
	}
	else
	{
		if (GetTargetObject() == NULL&&OBJECT->GetPlayer()->GetCharacterEntity()->IsDeath() == false && m_camp != CAMP_PLAYER&&MATH->IsCollided(OBJECT->GetPlayer()->GetArrangeSphere(), m_arrangeCollideSphere))
		{
			SetTargetObject(OBJECT->GetPlayer());
		}

		cCharacter::Update(deltaTime);
		m_pFsm->Update(deltaTime);

		m_meshSphere.m_vCenter = m_arrangeCollideSphere.vCenter;

		if (TIME->UpdateOneSecond())
		{
			for (int i = 0; i < m_vectorUnit.size(); i++)
			{
				if (m_vectorUnit[i]->IsDeath() == true)
				{
					SetDeath(true);
				}
				else if (m_vectorUnit[i]->IsDeath() == false)
				{
					SetDeath(false);
					break;
				}
			}
			if (m_vectorUnit.size() <= 0)SetDeath(true);
		}
	}



}

void cLeader::Render()
{
	//cCharacter::Render();
	D3DXMATRIXA16 matWorld, matR, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixTranslation(&matT, m_meshSphere.m_vCenter.x, m_meshSphere.m_vCenter.y, m_meshSphere.m_vCenter.z);
	matWorld = matR*matT;


	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	D3DDevice->SetMaterial(&m_meshSphere.m_stMtlSphere);
	//g_pD3DDevice->SetTexture(0, m_pSphere.m_pTexture);
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, D3DFILL_SOLID);

	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//m_meshSphere.m_pMeshSphere->DrawSubset(0);
	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void cLeader::AddUnit(cUnit * pUnit)
{
	pUnit->SetID(m_ID);
	pUnit->Init();
	pUnit->SetCamp(m_camp);
	m_vectorUnit.push_back(pUnit);
	OBJECT->AddObject(pUnit);
	OBJECT->AddCharacter(pUnit);
	OBJECT->AddEntity(pUnit->GetCharacterEntity());
}

bool cLeader::AddUnitInTown(C_C_ID ID)
{
	if (m_vectorUnit.size() < 20)
	{
		cUnit* pUnit;
		switch (ID)
		{
		case C_C_HUMAN_MELEE:case C_C_ORC_MELEE: pUnit = new cMeleeUnit(m_CharacterEntity, D3DXVECTOR3(0, 0, 0)); break;
		case C_C_HUMAN_BOWMAN:case C_C_ORC_BOWMAN: pUnit = new cBowUnit(m_CharacterEntity, D3DXVECTOR3(0, 0, 0)); break;
		case C_C_HUMAN_CAVALRY:case C_C_ORC_CAVALRY: pUnit = new cCavalryUnit(m_CharacterEntity, D3DXVECTOR3(0, 0, 0)); break;
		}

		pUnit->SetID(m_ID);
		pUnit->Init();
		pUnit->SetCamp(m_camp);
		pUnit->GetCharacterEntity()->SetPos(m_CharacterEntity->Pos());
		m_vectorUnit.push_back(pUnit);
		return true;
	}
	return false;
}

void cLeader::AddUnitInManager()
{
	for each (auto c in m_vectorUnit)
	{
		c->GetCharacterEntity()->SetPos(m_CharacterEntity->Pos());
		c->SetIdleState();
		OBJECT->AddObject(c);
		OBJECT->AddCharacter(c);
		OBJECT->AddEntity(c->GetCharacterEntity());
	}	
	SetRectOffset();
}

void cLeader::DeleteDeathUnitInExitScene()
{
	vector<cUnit*> n_vecUnit;
	for each(auto c in m_vectorUnit)
	{
		if (c->IsDeath() == false) { n_vecUnit.push_back(c); }
		else { SAFE_DELETE(c); }
	}
	m_vectorUnit.clear();
	m_vectorUnit = n_vecUnit;
	cout << "살아남은 병사 수 : "<<m_vectorUnit.size() << endl;
}

void cLeader::DeleteUnit(int key)
{

}

void cLeader::SetRectOffset()
{
	int key = 0;
	for (int i = 0; i < m_vectorUnit.size(); i++)
	{
		if (m_vectorUnit[i]->IsDeath() == false)m_vectorUnit[i]->SetOffset(m_RectOffest[key++]);
	}
}

void cLeader::SetTriOffset()
{
	int key = 0;
	for (int i = 0; i < m_vectorUnit.size(); i++)
	{
		if (m_vectorUnit[i]->IsDeath() == false)m_vectorUnit[i]->SetOffset(m_TriOffest[key++]);
	}
}

void cLeader::SetAttackMode()
{
	for (int i = 0; i < m_vectorUnit.size(); i++)
	{
		if (m_vectorUnit[i]->IsDeath() == false)m_vectorUnit[i]->SetIdleState();
	}
}

void cLeader::SetDefendMode()
{
	for (int i = 0; i < m_vectorUnit.size(); i++)
	{
		if (m_vectorUnit[i]->IsDeath() == false)m_vectorUnit[i]->SetDefenceState();
	}
}

void cLeader::SetMeleeType()
{
	m_type = LEADER_MELEE;
	m_pFsm->Register(LEADER_STATE_MELEE_IDLE, new Leader_State_Melee_Idle());
	m_pFsm->Register(LEADER_STATE_MELEE_WALK, new Leader_State_Melee_Walk());
	m_pFsm->Register(LEADER_STATE_MELEE_BATTLE, new Leader_State_Melee_Battle());
	m_pFsm->Register(LEADER_STATE_MELEE_DEFENCE, new Leader_State_Melee_Defence());
	m_TypeStart = LEADER_STATE_MELEE_IDLE;
	//for (int i = 0; i < 20; i++)AddUnit(new cMeleeUnit(m_CharacterEntity, D3DXVECTOR3(0, 0, 0)));
}

void cLeader::SetBowType()
{
	m_type = LEADER_BOW;
	m_pFsm->Register(LEADER_STATE_BOW_IDLE, new Leader_State_Bowman_Idle());
	m_pFsm->Register(LEADER_STATE_BOW_WALK, new Leader_State_Bowman_Walk());
	m_pFsm->Register(LEADER_STATE_BOW_BATTLE, new Leader_State_Bowman_Battle());
	m_TypeStart = LEADER_STATE_BOW_IDLE;
	//for (int i = 0; i < 20; i++)AddUnit(new cBowUnit(m_CharacterEntity, D3DXVECTOR3(0, 0, 0)));
}

void cLeader::SetCavalryType()
{
	m_type = LEADER_CAVALRY;
	m_pFsm->Register(LEADER_STATE_CAVALRY_IDLE, new Leader_State_Cavalry_Idle());
	m_pFsm->Register(LEADER_STATE_CAVALRY_WALK, new Leader_State_Cavalry_Walk());
	m_pFsm->Register(LEADER_STATE_CAVALRY_BATTLE, new Leader_State_Cavalry_Battle());
	m_TypeStart = LEADER_STATE_CAVALRY_IDLE;
	//for (int i = 0; i < 20; i++)AddUnit(new cCavalryUnit(m_CharacterEntity, D3DXVECTOR3(0, 0, 0)));
}

void cLeader::SetType()
{
	switch (m_ID)
	{
	case C_C_HUMAN_MELEE: case C_C_ORC_MELEE: SetMeleeType(); break;
	case C_C_HUMAN_BOWMAN:case C_C_ORC_BOWMAN: SetBowType(); break;
	case C_C_HUMAN_CAVALRY:case C_C_ORC_CAVALRY: SetCavalryType(); break;
	}
}

void cLeader::ClickedButtonOne()
{
	switch (m_type)
	{
	case LEADER_MELEE: m_pFsm->Play(LEADER_STATE_MELEE_IDLE); break;
	case LEADER_BOW:  m_pFsm->Play(LEADER_STATE_BOW_IDLE); break;
	case LEADER_CAVALRY: m_pFsm->Play(LEADER_STATE_CAVALRY_IDLE);  break;
	}
}

void cLeader::ClickedButtonTwo()
{
	switch (m_type)
	{
	case LEADER_MELEE: m_pFsm->Play(LEADER_STATE_MELEE_DEFENCE); break;
	case LEADER_BOW:  m_pFsm->Play(LEADER_STATE_BOW_BATTLE); break;
	case LEADER_CAVALRY: m_pFsm->Play(LEADER_STATE_CAVALRY_BATTLE); break;
	}
}



