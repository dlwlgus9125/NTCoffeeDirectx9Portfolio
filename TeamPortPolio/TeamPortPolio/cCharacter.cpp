#include "stdafx.h"
#include "cCharacter.h"

cCharacter::cCharacter()
{
	m_targetObject = NULL;
	m_isEquiped = false;
}


cCharacter::~cCharacter()
{
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_DELETE(m_Status);
	SAFE_RELEASE(m_MeshSphere.m_pMeshSphere);
}

void cCharacter::Init()
{
	m_isAnimDeath = false;
	m_currentMode = DEFENDING_MODE;
	m_AttackCollideSphere.fRadius = 0.2f;

	m_AttackCollideSphere.vCenter = D3DXVECTOR3(0, -10, 0);
	D3DXCreateSphere(D3DDevice, m_AttackCollideSphere.fRadius, 10, 10, &m_MeshSphere.m_pMeshSphere, NULL);
	ZeroMemory(&m_MeshSphere.m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_MeshSphere.m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_MeshSphere.m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_MeshSphere.m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);


	m_currentIndex = 0;
	m_isDeath = false;

	m_Status = new ST_Character(*CHARACTERDB->GetMapCharacter(m_ID));

	m_pSkinnedMesh = NULL;
	//m_pSkinnedMesh = new cSkinnedMesh();
	m_pSkinnedMesh = new cSkinnedMesh(TEXTURE->GetCharacterResource(m_Status->m_szPath, m_Status->m_szFileName));
}

void cCharacter::Update(float deltaTime)
{
		UpdateNearConstruct();

	m_CollideSphere.vCenter = m_CharacterEntity->Pos();
	m_CollideSphere.vCenter.y = m_CharacterEntity->Pos().y + 0.5f;
	m_arrangeCollideSphere.vCenter = m_CharacterEntity->Pos();

	if (m_Status->m_HP <= 0.0f&&m_isDeath == false)SetAnimDeath();
}

void cCharacter::Render()
{
	if (m_pSkinnedMesh)
	{
		SHADOW->SetAlphaBlendRenderState();

		D3DXPLANE groundPlane = SHADOW->CharacterPlane(GetCharacterEntity()->Pos().y + 0.001f);

		D3DXVECTOR4 light = SHADOW->CharacterLight();

		D3DXMATRIX W ,S, T, matS;
		D3DXMatrixShadow(&S, &light, &groundPlane);

		D3DXMatrixTranslation(&T, GetCharacterEntity()->Pos().x, GetCharacterEntity()->Pos().y, GetCharacterEntity()->Pos().z);

		D3DXMatrixScaling(&matS, 1.0f, 0.6f, 1.0f);

		W = matS *T * S;

		D3DDevice->SetTransform(D3DTS_WORLD, &W);
		D3DMATERIAL9 mtrl = SHADOW->CharacterMtrl();
		D3DDevice->SetMaterial(&mtrl);
		D3DDevice->SetTexture(0, 0);

		//m_MeshSphere.m_pMeshSphere->DrawSubset(0);

		SHADOW->UnSetAlphaBlendRenderState();
	}

	RenderSphere();
}

void cCharacter::RenderSphere()
{

}

void cCharacter::SetAttackColliderPos()
{
	if (m_isEquiped == true)
	{
		m_AttackCollideSphere.vCenter = D3DXVECTOR3(0, 0, 0);

		D3DXVec3TransformCoord(&m_AttackCollideSphere.vCenter, &m_AttackCollideSphere.vCenter, &m_pSkinnedMesh->GetAttackBoneMat());
	}
}

FIGHT_STATE cCharacter::Fight(cCharacter * attacker, cCharacter * defender)
{

	int randCount = rand() % 10 + 1;

	if (randCount <= defender->m_Status->m_defence)
	{
		SOUND->Play("Defenced");
		return FIGHT_BLOCK;
	}
	if (attacker->GetID() == C_C_ARROW_ARROW) { SOUND->Play("ArrowHit"); }
	else { SOUND->Play("DamagedBySword"); }
	if (CHARACTERDB->GetMapCharacter(defender->GetID())->m_raceID == C_R_HUMAN)
	{
		SOUND->Play("HumanHit");
	}
	else
	{
		SOUND->Play("OrcHit");
	}

	defender->m_Status->SetHP(-attacker->m_Status->m_Damage);
	return FIGHT_HIT;
}

void cCharacter::UpdateNearConstruct()
{
	D3DXVECTOR3 movePos = m_CharacterEntity->Pos();

	//cout << MAP->GetvecConstruct().size() << endl;
	for each (cConstruct* p in MAP->GetvecConstruct())
	{
		if (MATH->Distance(movePos, p->GetPosition()) + m_CollideSphere.fRadius - p->GetRadius() < 0)
		{
			D3DXVECTOR3 dir = MATH->Nomalize(movePos - p->GetPosition());

			movePos -= dir*(MATH->Distance(movePos, p->GetPosition()) + m_CollideSphere.fRadius - p->GetRadius());
		}
	}
	if (m_ID != C_C_ARROW_ARROW)
	MAP->GetHeight(movePos.x, movePos.y, movePos.z);



	m_CharacterEntity->SetPos(movePos);
}

