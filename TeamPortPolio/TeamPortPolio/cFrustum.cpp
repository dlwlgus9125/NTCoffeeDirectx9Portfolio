#include "stdafx.h"
#include "cFrustum.h"


cFrustum::cFrustum()
{
}


cFrustum::~cFrustum()
{
}

void cFrustum::Setup()
{
	for (int i = 0; i < 6; i++)
	{
		D3DXPLANE n_plane;
		m_vecPlane.push_back(n_plane);
	}
	PlaneSetup();
}

void cFrustum::Update()
{
	PlaneSetup();

	// Normalize planes
	for (int i = 0; i < m_vecPlane.size(); i++)
	{
		D3DXPlaneNormalize(&m_vecPlane[i], &m_vecPlane[i]);
	}
}

bool cFrustum::IsIn(MeshSpere pShere)
{
	// 각 면에 loop
	// 안에있는지 밖에잇는지 걸쳐있는지 
	// 그려줄지 말지 결정
	// D3DXPlaneDotCoord(면, 정점, 벡터) = > 거리
	for (int i = 0; i < m_vecPlane.size(); i++)
	{
		if (D3DXPlaneDotCoord(&m_vecPlane[i], &pShere.m_vCenter) + pShere.m_radius < 0)
		{
			// Outside the frustum, reject it!
			return false;
		}
	}
	return true;
}

bool cFrustum::IsIn(ST_SPHERE* pSphere)
{
	for each(D3DXPLANE p in m_vecPlane)
	{
		if (D3DXPlaneDotCoord(&p, &pSphere->vCenter) > pSphere->fRadius)
			return false;
	}
	return true;
}

bool cFrustum::IsIn(D3DXVECTOR3 vec3)
{
	// 각 면에 loop
	// 안에있는지 밖에잇는지 걸쳐있는지 
	// 그려줄지 말지 결정
	// D3DXPlaneDotCoord(면, 정점, 벡터) = > 거리
	for (int i = 0; i < m_vecPlane.size(); i++)
	{
		if (D3DXPlaneDotCoord(&m_vecPlane[i], &vec3)  < 0)
		{
			// Outside the frustum, reject it!
			return false;
		}
	}
	return true;
}


void cFrustum::PlaneSetup()
{
	D3DXMATRIXA16 matView, matProj;
	D3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMATRIX viewProjection;
	D3DXMatrixMultiply(&viewProjection, &matView, &matProj);

	// Left plane
	m_vecPlane[0].a = viewProjection._14 + viewProjection._11;
	m_vecPlane[0].b = viewProjection._24 + viewProjection._21;
	m_vecPlane[0].c = viewProjection._34 + viewProjection._31;
	m_vecPlane[0].d = viewProjection._44 + viewProjection._41;

	// Right plane
	m_vecPlane[1].a = viewProjection._14 - viewProjection._11;
	m_vecPlane[1].b = viewProjection._24 - viewProjection._21;
	m_vecPlane[1].c = viewProjection._34 - viewProjection._31;
	m_vecPlane[1].d = viewProjection._44 - viewProjection._41;

	// Top plane
	m_vecPlane[2].a = viewProjection._14 - viewProjection._12;
	m_vecPlane[2].b = viewProjection._24 - viewProjection._22;
	m_vecPlane[2].c = viewProjection._34 - viewProjection._32;
	m_vecPlane[2].d = viewProjection._44 - viewProjection._42;

	// Bottom plane
	m_vecPlane[3].a = viewProjection._14 + viewProjection._12;
	m_vecPlane[3].b = viewProjection._24 + viewProjection._22;
	m_vecPlane[3].c = viewProjection._34 + viewProjection._32;
	m_vecPlane[3].d = viewProjection._44 + viewProjection._42;

	// Near plane
	m_vecPlane[4].a = viewProjection._13;
	m_vecPlane[4].b = viewProjection._23;
	m_vecPlane[4].c = viewProjection._33;
	m_vecPlane[4].d = viewProjection._43;

	// Far plane
	m_vecPlane[5].a = viewProjection._14 - viewProjection._13;
	m_vecPlane[5].b = viewProjection._24 - viewProjection._23;
	m_vecPlane[5].c = viewProjection._34 - viewProjection._33;
	m_vecPlane[5].d = viewProjection._44 - viewProjection._43;
}
