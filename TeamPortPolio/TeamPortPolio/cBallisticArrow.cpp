#pragma once
#include"stdafx.h"
#include "cBallisticArrow.h"

cBallisticArrow::cBallisticArrow(D3DXVECTOR3 pos, D3DXVECTOR3 vtarget, D3DXVECTOR3 forward, float radius, float mass, float maxSpeed)
{
	pEntity = new IEntity(pos, radius, forward);
	m_pArrow = new BallisticMotion(pEntity, pos, vtarget, forward, radius);
	m_ArrowSphere.fRadius =radius;
	m_vTarget = vtarget;
	m_vDir = forward;
	Init();
}

cBallisticArrow::~cBallisticArrow()
{
	SAFE_DELETE(pEntity);
	SAFE_DELETE(m_pArrow);
}

BallisticMotion * cBallisticArrow::Shoot()
{
	return m_pArrow;
}

void cBallisticArrow::Init()
{
	m_ArrowSphere.vCenter = m_pArrow->Entity()->Pos();
	D3DXCreateSphere(D3DDevice, pEntity->Radius(), 10, 10, &m_pMeshSphere, NULL);
	
	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}


void cBallisticArrow::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	D3DXMatrixTranslation(&mat, m_ArrowSphere.vCenter.x, m_ArrowSphere.vCenter.y, m_ArrowSphere.vCenter.z);

	D3DDevice->SetTransform(D3DTS_WORLD, &mat);
	D3DDevice->SetMaterial(&m_stMtlSphere);

	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pMeshSphere->DrawSubset(0);
	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);



}

void cBallisticArrow::ArrowUpdate()
{
	m_ArrowSphere.vCenter = m_pArrow->Entity()->Pos();
}
