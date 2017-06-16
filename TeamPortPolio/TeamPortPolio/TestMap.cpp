#include "stdafx.h"
#include "TestMap.h"

void TestMap::Set_Light()
{
	D3DLIGHT9 stLight;
	{
		ZeroMemory(&stLight, sizeof(D3DLIGHT9));
		stLight.Type = D3DLIGHT_DIRECTIONAL;
		stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		D3DXVECTOR3 vDir(1.0f, -1.0f, 1.0f);
		D3DXVec3Normalize(&vDir, &vDir);
		stLight.Direction = vDir;
		D3DDevice->SetLight(0, &stLight);
	}

	D3DDevice->LightEnable(0, true);
}


void TestMap::Setup()
{
	Set_Light();
	gridSetup();
}

void TestMap::Render()
{
			gridRender();
}

void TestMap::gridSetup(int nNumHalfTile, float fInterval)
{
	float fMax = nNumHalfTile * fInterval;
	float fMin = -nNumHalfTile * fInterval;

	ST_PC_VERTEX v;

	for (int i = 1; i <= nNumHalfTile; ++i)
	{
		if (i % 5 == 0)
			v.c = D3DCOLOR_XRGB(255, 255, 255);
		else
			v.c = D3DCOLOR_XRGB(128, 128, 128);

		v.p = D3DXVECTOR3(fMin, 0, i * fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i * fInterval); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i * fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i * fInterval); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(i * fInterval, 0, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(i * fInterval, 0, fMax); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i * fInterval, 0, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, fMax); m_vecVertex.push_back(v);
	}

	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(fMin, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, fMin, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, fMax, 0); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0, 0, fMin); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax); m_vecVertex.push_back(v);

	cPyramid* pPyramid = NULL;
	D3DXMATRIXA16 matR;

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(255, 0, 0), matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	pPyramid->Setup(D3DCOLOR_XRGB(0, 255, 0), matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(0, 0, 255), matR);
	m_vecPyramid.push_back(pPyramid);
}

void TestMap::gridRender()
{
	D3DDevice->SetRenderState(D3DRS_LIGHTING, false); // << : 13.

	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	D3DDevice->SetTransform(D3DTS_WORLD, &matI);
	// : 이번 제외 g_pD3DDevice->SetTexture(0, NULL);
	D3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	D3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex.size() / 2,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));

	for each(auto p in m_vecPyramid)
	{
		p->Render();
	}
}


cPyramid::cPyramid()
{
}


cPyramid::~cPyramid()
{
}

void cPyramid::Setup(D3DXCOLOR c, D3DXMATRIXA16& mat)
{
	/// >> : 13.
	{	/// : material 설정
		ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
		m_stMtl.Ambient = c;
		m_stMtl.Diffuse = c;
		m_stMtl.Specular = c;
	}
	/// << : 13. 


	m_matR = mat;

	///ST_PC_VERTEX v;	// << : 13.
	///v.c = c;	// << : 
	ST_PN_VERTEX v;	// << : 13.


	v.p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, 1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, 1); m_vecVertex.push_back(v);

	// >> : 
	for (int i = 0; i < m_vecVertex.size(); i += 3)
	{
		D3DXVECTOR3 v01 = m_vecVertex[i + 1].p - m_vecVertex[i].p;
		D3DXVECTOR3 v02 = m_vecVertex[i + 2].p - m_vecVertex[i].p;
		D3DXVECTOR3 n;

		D3DXVec3Cross(&n, &v01, &v02);
		D3DXVec3Normalize(&n, &n);

		m_vecVertex[i].n = n;
		m_vecVertex[i + 1].n = n;
		m_vecVertex[i + 2].n = n;
	}
	/// << : 
}

void cPyramid::Render()
{
	D3DXMATRIXA16 matWorld, matS;
	D3DXMatrixScaling(&matS, 0.1f, 2.0f, 0.1f);

	matWorld = matS * m_matR;

	/// >> :
	D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DDevice->SetMaterial(&m_stMtl);
	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	D3DDevice->SetFVF(ST_PN_VERTEX::FVF);	// << : 13. 
	D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PN_VERTEX));
}