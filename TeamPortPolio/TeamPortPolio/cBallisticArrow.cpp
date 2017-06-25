#pragma once
#include"stdafx.h"
#include "cBallisticArrow.h"

cBallisticArrow::cBallisticArrow(D3DXVECTOR3 pos, D3DXVECTOR3 vtarget, D3DXVECTOR3 forward, float radius, float mass, float maxSpeed)
{
	pos.y += 1.0f;
	m_CharacterEntity = new ISteeringEntity(pos, radius, forward,0,0);
	m_pArrow = new BallisticMotion(m_CharacterEntity, pos, vtarget, forward, radius);
	m_CollideSphere.fRadius =radius;
	m_vTarget = vtarget;
	m_vDir = forward;
	SetID(C_C_ARROW_ARROW);
	Init();
	m_isHit = false;
}

cBallisticArrow::~cBallisticArrow()
{
	SAFE_RELEASE(m_pMeshSphere)
	SAFE_DELETE(m_CharacterEntity);
	SAFE_DELETE(m_pArrow);
}

BallisticMotion * cBallisticArrow::Shoot()
{
	return m_pArrow;
}

void cBallisticArrow::Init()
{
	m_CollideSphere.vCenter = m_pArrow->Entity()->Pos();
	D3DXCreateSphere(D3DDevice, m_CharacterEntity->Radius(), 10, 10, &m_pMeshSphere, NULL);
	
	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	cCharacter::Init();
}


void cBallisticArrow::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	D3DXMatrixTranslation(&mat, m_CollideSphere.vCenter.x, m_CollideSphere.vCenter.y, m_CollideSphere.vCenter.z);

	D3DDevice->SetTransform(D3DTS_WORLD, &mat);
	D3DDevice->SetMaterial(&m_stMtlSphere);

	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	if(g_showColider)m_pMeshSphere->DrawSubset(0);
	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//cCharacter::Render();
	if (FRUSTUM->IsIn(m_pSkinnedMesh->GetBoundingSphere()))
	{
		m_pSkinnedMesh->UpdateAndRender(m_isDeath);
	}
}

void cBallisticArrow::ArrowUpdate()
{
	if (m_isDeath != true)
	{//m_CollideSphere.vCenter = m_pArrow->Entity()->Pos();
		cCharacter::Update(TIME->DeltaTime());

		float y = 0.0f;
		MAP->GetHeight(m_CharacterEntity->Pos().x, y, m_CharacterEntity->Pos().z);

		if (m_CharacterEntity->Pos().y <= y)
		{
			SOUND->Play("ArrowHitGround");
			this->SetDeath(true);
		}

		m_pSkinnedMesh->SetPosition(m_pArrow->Entity()->Pos(), m_pArrow->Entity()->Forward());
		for (int i = 0; i < OBJECT->GetCharacter().size(); i++)
		{
			if (m_isHit == false && OBJECT->GetCharacter()[i]->GetCharacterEntity()->IsDeath() == false && OBJECT->GetCharacter()[i]->GetCamp() != m_camp&&MATH->IsCollided(OBJECT->GetCharacter()[i]->GetSphere(), m_CollideSphere))
			{
				OBJECT->GetCharacter()[i]->SetAnimHit();

				this->Fight(this, OBJECT->GetCharacter()[i]);
				m_isHit = true;
			}

		}
	}




}
