#include "stdafx.h"
#include "cNonPlayerCharacter.h"



cNonPlayerCharacter::cNonPlayerCharacter(D3DXVECTOR3 pos, float moveSpeed, float rot, NPC_KINDS kind)
{
	m_vPosition = pos;
	m_speed = moveSpeed;
	m_fRotY = rot;
	m_state = NPC_IDLE;
	m_isPicked = false;
	m_kind = kind;
	m_pSphere.fRadius = 5.0f;
	m_pSphere.vCenter = m_vPosition;
	m_pSphere.isPicked = false;
}


cNonPlayerCharacter::~cNonPlayerCharacter()
{
	
}

void cNonPlayerCharacter::Init()
{
	
}

void cNonPlayerCharacter::Update(float deltaTime)
{

}

void cNonPlayerCharacter::Render()
{

}

void cNonPlayerCharacter::MovePosition(D3DXVECTOR3 pos, float speed)
{

}

void cNonPlayerCharacter::SetPath(D3DXVECTOR3 pos)
{
	m_path.push_back(pos);
}

void cNonPlayerCharacter::AutoMoveAI(vector<D3DXVECTOR3> path)
{
	
}
