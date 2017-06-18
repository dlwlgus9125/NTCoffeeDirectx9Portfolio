#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter()
{
	m_targetObject = NULL;
}


cCharacter::~cCharacter()
{
	//SAFE_DELETE( m_pSkinnedMesh);
}

void cCharacter::Init()
{
	m_isAnimDeath = false;
	m_currentMode = DEFENDING_MODE;
	m_AttackCollideSphere.fRadius = 0.5f;
	D3DXCreateSphere(D3DDevice, m_CollideSphere.fRadius, 10, 10, &m_MeshSphere.m_pMeshSphere, NULL);
	ZeroMemory(&m_MeshSphere.m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_MeshSphere.m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_MeshSphere.m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_MeshSphere.m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	//D3DXCreateSphere(D3DDevice, m_arrangeCollideSphere.m_radius, 10, 10, &m_arrangeCollideSphere.m_pMeshSphere, NULL);
	//ZeroMemory(&m_arrangeCollideSphere.m_stMtlSphere, sizeof(D3DMATERIAL9));
	//m_arrangeCollideSphere.m_stMtlSphere.Ambient = D3DXCOLOR(255.0f, 0.7f, 255.0f, 1.0f);
	//m_arrangeCollideSphere.m_stMtlSphere.Diffuse = D3DXCOLOR(255.0f, 0.7f, 255.0f, 1.0f);
	//m_arrangeCollideSphere.m_stMtlSphere.Specular = D3DXCOLOR(255.0f, 0.7f, 255.0f, 1.0f);
	m_currentIndex = 0;
	m_isDeath = false;

	m_Status = new ST_Character(*CHARACTERDB->GetMapCharacter(m_ID));

	m_pSkinnedMesh = NULL;
	//m_pSkinnedMesh = new cSkinnedMesh();
	m_pSkinnedMesh = new cSkinnedMesh(TEXTURE->GetCharacterResource(m_Status->m_szPath, m_Status->m_szFileName));
}

void cCharacter::Update(float deltaTime)
{

	m_CollideSphere.vCenter = m_CharacterEntity->Pos();
	m_arrangeCollideSphere.vCenter = m_CharacterEntity->Pos();

	if (m_Status->m_HP <= 0.0f&&m_isDeath==false)SetAnimDeath();
}

void cCharacter::Render()
{
	if (m_pSkinnedMesh)
	{

		D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		D3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		D3DDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		D3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		D3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		D3DDevice->SetRenderState(D3DRS_STENCILREF, 0x0);
		D3DDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
		D3DDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
		D3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
		D3DDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		D3DDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

		D3DXPLANE groundPlane(0.0f, -1.0f, 0.0f, GetCharacterEntity()->Pos().y + 0.001f);

		D3DXVECTOR4 lightTest(0.707f, -0.707f, 0.707f, 0.0f);

		D3DXMATRIX S;
		D3DXMatrixShadow(
			&S,
			&lightTest,
			&groundPlane);

		D3DXMATRIX T;
		D3DXMatrixTranslation(
			&T,
			GetCharacterEntity()->Pos().x, GetCharacterEntity()->Pos().y, GetCharacterEntity()->Pos().z);

		D3DXMATRIXA16 matS;

		D3DXMatrixScaling(&matS, 0.4f, 0.2f, 0.4f);

		D3DXMATRIX W = matS *T * S;

		D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		D3DDevice->SetTransform(D3DTS_WORLD, &W);
		D3DMATERIAL9 mtrl;
		mtrl.Ambient.r = 0; mtrl.Ambient.g = 0; mtrl.Ambient.b = 0;
		mtrl.Diffuse.r = 0; mtrl.Diffuse.g = 0; mtrl.Diffuse.b = 0;
		mtrl.Specular.r = 0; mtrl.Specular.g = 0; mtrl.Diffuse.b = 0;
		mtrl.Emissive.r = 0; mtrl.Emissive.g = 0; mtrl.Emissive.b = 0;
		mtrl.Power = 0.0f;
		mtrl.Diffuse.a = 0.3f;
		D3DDevice->SetMaterial(&mtrl);
		D3DDevice->SetTexture(0, 0);

		m_MeshSphere.m_pMeshSphere->DrawSubset(0);

		D3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		D3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		D3DDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
		D3DDevice->SetRenderState(D3DRS_LIGHTING, false);


		if (FRUSTUM->IsIn(m_pSkinnedMesh->GetBoundingSphere()))
		{
			m_pSkinnedMesh->UpdateAndRender(m_isDeath);

			//SetAttackColliderPos();
			D3DXMATRIXA16 matT;
			D3DXMatrixIdentity(&matT);

			D3DXMatrixTranslation(&matT, m_CollideSphere.vCenter.x, m_CollideSphere.vCenter.y, m_CollideSphere.vCenter.z);

			D3DDevice->SetTransform(D3DTS_WORLD, &matT);
			D3DDevice->SetMaterial(&m_MeshSphere.m_stMtlSphere);

			D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		//	m_MeshSphere.m_pMeshSphere->DrawSubset(0);
			D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
	}

	RenderSphere();		



}

void cCharacter::RenderSphere()
{
	
}

void cCharacter::SetAttackColliderPos()
{
	m_AttackCollideSphere.vCenter = D3DXVECTOR3(0, 0, 0);
	
	D3DXVec3TransformCoord(&m_AttackCollideSphere.vCenter, &m_AttackCollideSphere.vCenter, &m_pSkinnedMesh->GetAttackBoneMat());
}

FIGHT_STATE cCharacter::Fight(cCharacter * attacker, cCharacter * defender)
{

	int randCount = rand() % 10+1;

	if (randCount <= defender->m_Status->m_defence)
	{
		return FIGHT_BLOCK;
	}

	defender->m_Status->SetHP(-attacker->m_Status->m_Damage);
	return FIGHT_HIT;
}

