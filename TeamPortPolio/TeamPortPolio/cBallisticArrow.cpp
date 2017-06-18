#pragma once
#include"stdafx.h"
#include "cBallisticArrow.h"

cBallisticArrow::cBallisticArrow(D3DXVECTOR3 pos, D3DXVECTOR3 vtarget, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed)
{
	//pos.y += 1.0f;
	m_CharacterEntity = new ISteeringEntity(pos, 0.5f, D3DXVECTOR3(), mass, maxSpeed);
	//m_CharacterEntity->SetForward(m_CharacterEntity->Forward());
	m_pArrow = new BallisticMotion(m_CharacterEntity, pos, vtarget, D3DXVECTOR3());
	m_isPlayer = false;
	

	
}
//생성까진 문제없음 이제 출력하고 충돌하게 하기
cBallisticArrow::~cBallisticArrow()
{
	SAFE_DELETE(m_pArrow);
}

BallisticMotion * cBallisticArrow::Shoot()
{
	return m_pArrow;
}

void cBallisticArrow::Init()
{
	m_CollideSphere.fRadius = 0.1f;
	m_CollideSphere.vCenter = m_CharacterEntity->Pos();

	m_arrangeCollideSphere.fRadius = 0.1f;
	m_arrangeCollideSphere.vCenter = m_CharacterEntity->Pos();

	D3DXCreateSphere(D3DDevice, m_CollideSphere.fRadius, 10, 10, &m_MeshSphere.m_pMeshSphere, NULL);
	ZeroMemory(&m_MeshSphere.m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_MeshSphere.m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_MeshSphere.m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_MeshSphere.m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	//>>화살 텍스쳐 로딩할 부분
	m_isHit = false;
	m_Status = new ST_Character(*CHARACTERDB->GetMapCharacter(C_C_ARROW_ARROW));
	cCharacter::Init();
}

void cBallisticArrow::Update(float deltaTime)
{
	if (m_isDeath == false)
	{
		/*switch (m_isPlayer)
		{
		case true: 	Shoot()->Update_with_dir(); break;
		default: Shoot()->Update_with_targetpos(); break;
		}*/
		Shoot()->Update_with_targetpos();
		m_pSkinnedMesh->SetPosition(m_pArrow->Entity()->Pos(),D3DXVECTOR3(0,0,0));
		cCharacter::Update(deltaTime);

		




		//for (int i = 0; i < OBJECT->GetCharacter().size(); i++)
		//{
		//	if (m_isHit == false &&this->GetCamp()!= OBJECT->GetCharacter()[i]->GetCamp()&& MATH->IsCollided(OBJECT->GetCharacter()[i]->GetSphere(), this->GetSphere()))
		//	{
		//		//OBJECT->GetCharacter()[i]->SetAnimHit();

		//		//m_isHit = true;
		//	}
		//}
		
		D3DXVECTOR3 pos = m_CharacterEntity->Pos();
		float n_height = 0.0f;
		MAP->GetHeight(pos.x, n_height, pos.z);
		if (n_height >= pos.y)
		{
			m_isDeath = true;
		}
	}
}

void cBallisticArrow::Render()
{
	if (m_pSkinnedMesh)
	{
		if (FRUSTUM->IsIn(m_pSkinnedMesh->GetBoundingSphere()))
		{
			m_pSkinnedMesh->UpdateAndRenderForArrow(m_isDeath);

			//SetAttackColliderPos();
			D3DXMATRIXA16 matT;
			D3DXMatrixIdentity(&matT);

			D3DXMatrixTranslation(&matT, m_CollideSphere.vCenter.x, m_CollideSphere.vCenter.y, m_CollideSphere.vCenter.z);

			D3DDevice->SetTransform(D3DTS_WORLD, &matT);
			D3DDevice->SetMaterial(&m_MeshSphere.m_stMtlSphere);

			D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
				m_MeshSphere.m_pMeshSphere->DrawSubset(0);
			D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
	}
}
