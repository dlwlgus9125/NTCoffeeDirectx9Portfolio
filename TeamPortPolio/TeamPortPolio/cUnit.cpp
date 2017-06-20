#include "stdafx.h"
#include "cUnit.h"



cUnit::cUnit()
{
}


cUnit::~cUnit()
{
	SAFE_DELETE(m_CharacterEntity);
	
	//delete m_pLeader;
}

void cUnit::Init()
{
	m_CollideSphere.fRadius = 1.0f;
	m_CollideSphere.vCenter = m_CharacterEntity->Pos();


	cCharacter::Init();

	
}

void cUnit::Update(float deltaTime)
{
		cCharacter::Update(deltaTime);
}

void cUnit::Render()
{
	cCharacter::Render();
}
