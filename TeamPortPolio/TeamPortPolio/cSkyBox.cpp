#include "stdafx.h"
#include "cSkyBox.h"
#include "cCamera.h"


cSkyBox::cSkyBox()
{
}


cSkyBox::~cSkyBox()
{
}

void cSkyBox::Setup(float sizeX, float sizeY, float sizeZ, char* szFolder, char* szExtension)
{
	// Vertex 처리

	vector<ST_PT_VERTEX> vecVertex;
	vecVertex.resize(8);

	vecVertex[0].p.x = -1.0f * sizeX;
	vecVertex[0].p.y = 0.0f; // -1.0f * sizeY;
	vecVertex[0].p.z = -1.0f * sizeZ;

	vecVertex[1].p.x = -1.0f * sizeX;
	vecVertex[1].p.y = 1.0f * sizeY;
	vecVertex[1].p.z = -1.0f * sizeZ;

	vecVertex[2].p.x = 1.0f * sizeX;
	vecVertex[2].p.y = 1.0f * sizeY;
	vecVertex[2].p.z = -1.0f * sizeZ;

	vecVertex[3].p.x = 1.0f * sizeX;
	vecVertex[3].p.y = 0.0f; // -1.0f * sizeY;
	vecVertex[3].p.z = -1.0f * sizeZ;


	vecVertex[4].p.x = -1.0f * sizeX;
	vecVertex[4].p.y = 0.0f; // -1.0f * sizeY;
	vecVertex[4].p.z = 1.0f * sizeZ;

	vecVertex[5].p.x = -1.0f * sizeX;
	vecVertex[5].p.y = 1.0f * sizeY;
	vecVertex[5].p.z = 1.0f * sizeZ;

	vecVertex[6].p.x = 1.0f * sizeX;
	vecVertex[6].p.y = 1.0f * sizeY;
	vecVertex[6].p.z = 1.0f * sizeZ;

	vecVertex[7].p.x = 1.0f * sizeX;
	vecVertex[7].p.y = 0.0f; // -1.0f * sizeY;
	vecVertex[7].p.z = 1.0f * sizeZ;

	// Index 처리 -> 반시계 방향
	
	// Near(Front)
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(0);

	m_vecIndex.push_back(3);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(1);

	// Far(Back)
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(7);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(6);

	// Left
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(4);

	m_vecIndex.push_back(0);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(5);

	// Right
	m_vecIndex.push_back(7);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(3);

	m_vecIndex.push_back(7);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(2);

	// Top
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(1);

	m_vecIndex.push_back(2);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(5);

	// Bottom
	m_vecIndex.push_back(7);
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(4);

	m_vecIndex.push_back(7);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(0);

	m_vecVertex.resize(36);

	for (size_t i = 0; i < m_vecIndex.size(); i += 3)
	{
		m_vecVertex[i + 0] = vecVertex[m_vecIndex[i + 0]];
		m_vecVertex[i + 1] = vecVertex[m_vecIndex[i + 1]];
		m_vecVertex[i + 2] = vecVertex[m_vecIndex[i + 2]];
	}

	// texture 추가
	for (int i = 0; i < m_vecVertex.size(); i += 6)
	{
		m_vecVertex[i + 0].t = D3DXVECTOR2(1.0f, 1.0f);
		m_vecVertex[i + 1].t = D3DXVECTOR2(0.0f, 0.0f);
		m_vecVertex[i + 2].t = D3DXVECTOR2(0.0f, 1.0f);

		m_vecVertex[i + 3].t = D3DXVECTOR2(1.0f, 1.0f);
		m_vecVertex[i + 4].t = D3DXVECTOR2(1.0f, 0.0f);
		m_vecVertex[i + 5].t = D3DXVECTOR2(0.0f, 0.0f);
	}
	
	// map의 typename으로 텍스쳐 설정
	Setup_Texture(szFolder, szExtension);
}

void cSkyBox::Setup_Texture(char* szFolder, char* szExtension)
{
	map<SKYBOX_FACE, LPDIRECT3DTEXTURE9> mapTexture;
	
	mapTexture[SKYBOX_FACE_FRONT] = TEXTURE->GetTexture(szFolder + (string)"/Front." + (string)szExtension);
	mapTexture[SKYBOX_FACE_BACK] = TEXTURE->GetTexture(szFolder + (string)"/Back." + (string)szExtension);
	mapTexture[SKYBOX_FACE_LEFT] = TEXTURE->GetTexture(szFolder + (string)"/Left." + (string)szExtension);
	mapTexture[SKYBOX_FACE_RIGHT] = TEXTURE->GetTexture(szFolder + (string)"/Right." + (string)szExtension);
	mapTexture[SKYBOX_FACE_TOP] = TEXTURE->GetTexture(szFolder + (string)"/Top." + (string)szExtension);
	mapTexture[SKYBOX_FACE_BOTTOM] = TEXTURE->GetTexture(szFolder + (string)"/Bottom." + (string)szExtension);

	m_mapCurrentTexture = mapTexture;
}

void cSkyBox::Update(cCamera* pCamera)
{
	D3DXMATRIXA16	projMat, viewMat, matWorld;
	D3DXMatrixIdentity(&projMat);
	D3DXMatrixIdentity(&viewMat);
	D3DXMatrixIdentity(&matWorld);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMatrixPerspectiveFovLH(&projMat, D3DX_PI / 4.0F, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	D3DDevice->SetTransform(D3DTS_PROJECTION, &projMat);

	D3DXMatrixLookAtLH(&viewMat, &pCamera->GetEye(), &pCamera->GetLookAt(), &pCamera->GetUp());
	D3DDevice->SetTransform(D3DTS_VIEW, &viewMat);

	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
}

void cSkyBox::Render()
{
	D3DDevice->BeginScene();

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	D3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	LPDIRECT3DTEXTURE9 texture;

	texture = m_mapCurrentTexture[SKYBOX_FACE_FRONT];

	D3DDevice->SetTexture(0, texture);
	D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		2,
		&m_vecVertex[0],
		sizeof(ST_PT_VERTEX));

	texture = m_mapCurrentTexture[SKYBOX_FACE_BACK];
	D3DDevice->SetTexture(0, texture);
	D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		2,
		&m_vecVertex[6],
		sizeof(ST_PT_VERTEX));

	texture = m_mapCurrentTexture[SKYBOX_FACE_LEFT];
	D3DDevice->SetTexture(0, texture);
	D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		2,
		&m_vecVertex[12],
		sizeof(ST_PT_VERTEX));

	texture = m_mapCurrentTexture[SKYBOX_FACE_RIGHT];
	D3DDevice->SetTexture(0, texture);
	D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		2,
		&m_vecVertex[18],
		sizeof(ST_PT_VERTEX));

	texture = m_mapCurrentTexture[SKYBOX_FACE_TOP];
	D3DDevice->SetTexture(0, texture);
	D3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		2,
		&m_vecVertex[24],
		sizeof(ST_PT_VERTEX));

	//texture = m_mapCurrentTexture[SKYBOX_FACE_BOTTOM];
	//DEVICE->SetTexture(0, texture);
	//DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
	//	2,
	//	&m_vecVertex[30],
	//	sizeof(ST_PT_VERTEX));

	D3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	D3DDevice->EndScene();
}