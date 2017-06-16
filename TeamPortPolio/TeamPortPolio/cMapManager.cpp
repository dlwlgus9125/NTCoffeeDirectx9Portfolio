#include "stdafx.h"
#include "cMapManager.h"
#include "cShadowManager.h"

cMapManager::cMapManager()
{
}


cMapManager::~cMapManager()
{
}

void cMapManager::Init(string fileName)
{
	// >> 맵 로드
	char* folderPath = "map";
	//string temp = "TESTMAP.txt";
	char* filePath = strdup(fileName.c_str());

	m_pMap = new cHeightMap();
	cObjLoader loader;
	vector<cMtlTex*> vecMtlTex;
	vector<ST_PNT_VERTEX> vecVertex;
	vector<DWORD> vecIndex;
	int nCellPerRow = 0;
	float fCellSpace = 0.0f;
	LPD3DXMESH pMesh = loader.LoadMesh_Map(vecMtlTex, vecVertex, vecIndex, nCellPerRow, fCellSpace, m_vecConstruct, folderPath, filePath, false);
	m_pMap->Setup(nCellPerRow, fCellSpace, vecVertex, vecIndex);
	m_pMap->SetMesh(pMesh);
	m_pMap->SetVecMtlTex(vecMtlTex);
	// << 

	// >> : 포지션 좌표 넣어줌 -> 사용 그림자
	m_vPositionVertex = vecVertex[0];
	// << :

	// >> 노드에 쓸 노드 중점의 위치 만드는 부분
	
	for (int i = 0; i < vecIndex.size(); i += 6)
	{
		D3DXVECTOR3 v0 = vecVertex[vecIndex[i + 0]].p;
		D3DXVECTOR3 v1 = vecVertex[vecIndex[i + 1]].p;
		D3DXVECTOR3 v2 = vecVertex[vecIndex[i + 2]].p;
		D3DXVECTOR3 v5 = vecVertex[vecIndex[i + 5]].p;

		D3DXVECTOR3 pos;
		pos.x = (v0.x + v1.x + v2.x + v5.x) / 4;
		pos.y = (v0.y + v1.y + v2.y + v5.y) / 4;
		pos.z = (v0.z + v1.z + v2.z + v5.z) / 4;

		m_vecPosOfNode.push_back(pos);
	}
	// << 

	// >> 스카이박스 생성
	m_pSkyBox = new cSkyBox();
	m_pSkyBox->Setup(nCellPerRow / 2, nCellPerRow / 2, nCellPerRow / 2);
	// << 
	ASTAR->Setup(m_vecPosOfNode);

	// >> : 그림자 세팅
	SHADOW->Setup(m_vecConstruct);
	// << :
}

void cMapManager::Update()
{
	if (m_pSkyBox) m_pSkyBox->Update(CAMERA->GetCamera());
}

void cMapManager::Render()
{
	static bool test = false;
	if (INPUT->IsKeyDown(VK_TAB))
	{
		if (test == false)
		{
			//test = true;
		}
		else
		{
			//test = false;
		}
	}

	if (test == false)
	{

		if (m_pSkyBox) m_pSkyBox->Render();

		if (m_pMap) m_pMap->Render();

		SHADOW->Render();
		for (int i = 0; i < m_vecConstruct.size(); i++)
		{
			m_vecConstruct[i]->Render();
		}
	}
	else { ASTAR->Render(); }
}

bool cMapManager::GetHeight(IN float x, OUT float & y, IN float z)
{
	if (m_pMap->GetHeight(x, y, z))return true;
	
	return false;
}

LPD3DXMESH cMapManager::GetMesh()
{
	return m_pMap->GetMesh();
}

float cMapManager::GetMaxX()
{
	return m_pMap->GetMaxX();
}

float cMapManager::GetMinX()
{
	return m_pMap->GetMinX();
}

void cMapManager::Destroy()
{
	SAFE_DELETE(m_pSkyBox);
	SAFE_DELETE(m_pMap);
	ASTAR->Release();
	for (int i = 0; i < m_vecConstruct.size(); i++)
	{
		SAFE_DELETE(m_vecConstruct[i]);
	}
	m_vecConstruct.clear();
	
}
