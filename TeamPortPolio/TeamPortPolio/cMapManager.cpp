#include "stdafx.h"
#include "cMapManager.h"
#include "cShadowManager.h"

cMapManager::cMapManager()
{
}


cMapManager::~cMapManager()
{
}

void cMapManager::Init(int sceneID)
{
	char* folderPath = NULL;
	char* filePath = NULL;
	int nCellPerRow = 0;
	float fCellSpace = 0.0f;

	m_pSkyBox = new cSkyBox();
	switch (sceneID)
	{
	case SCENE_TOWN_HUMAN:  
		folderPath = "map";
		filePath = strdup("TOWNHUMAN.txt");
		break;

	case SCENE_TOWN_ORC:
		folderPath = "map";
		filePath = strdup("TOWNORC.txt");
		break;

	case SCENE_BATTLE_HUMAN:
		folderPath = "map";
		filePath = strdup("BATTLEHUMAN.txt");
		break;

	case SCENE_BATTLE_ORC:
		folderPath = "map";
		filePath = strdup("BATTLEORC.txt");
		break;
	}

	m_pMap = new cHeightMap();
	cObjLoader loader;
	vector<cMtlTex*> vecMtlTex;
	vector<ST_PNT_VERTEX> vecVertex;
	vector<DWORD> vecIndex;
	
	LPD3DXMESH pMesh = loader.LoadMesh_Map(vecMtlTex, vecVertex, vecIndex, nCellPerRow, fCellSpace, m_vecConstruct, folderPath, filePath, false);

	m_stWeather = ST_WEATHER();
	m_stWeather = loader.GetWeatherInfo();
	m_stShadow = ST_SHADOW();
	m_stShadow = loader.GetShadowInfo();
	SHADOW->SetAlpha(m_stShadow.GetShadowDiffuseAlpha());
	m_vecStNPC = loader.GetNPCInfo();
	NPC->Init(m_vecStNPC);
	m_pMap->Setup(nCellPerRow, fCellSpace, vecVertex, vecIndex);
	m_pMap->SetMesh(pMesh);
	m_pMap->SetVecMtlTex(vecMtlTex);

	int cellPerRow = nCellPerRow * fCellSpace;
	
	switch (sceneID)
	{
	case SCENE_TOWN_HUMAN:
		m_pSkyBox->Setup(cellPerRow / 2, cellPerRow / 2, cellPerRow / 2, "map/SkyBox/Town_Human", "png");
		break;

	case SCENE_TOWN_ORC:
		m_pSkyBox->Setup(cellPerRow / 2, cellPerRow / 2, cellPerRow / 2, "map/SkyBox/Town_Orc", "png");
		break;

	case SCENE_BATTLE_HUMAN:
		m_pSkyBox->Setup(cellPerRow / 2, cellPerRow / 2, cellPerRow / 2, "map/SkyBox/Battle_Human", "png");
		break;

	case SCENE_BATTLE_ORC:
		m_pSkyBox->Setup(cellPerRow / 2, cellPerRow / 2, cellPerRow / 2, "map/SkyBox/Battle_Orc", "png");
		break;
	}
	// << 
	//position , fRotY, scale , ID
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
	
	
	SetConstructSize();
	// >> : 그림자 세팅

	SHADOW->Setup(m_vecConstruct);
}

void cMapManager::Update()
{
	if (m_pSkyBox) m_pSkyBox->Update(CAMERA->GetCamera());
	NPC->Update(m_vecStNPC);
}

void cMapManager::Render()
{
	if (m_pSkyBox) m_pSkyBox->Render();

	if (m_pMap) m_pMap->Render();
	
	if (m_vecStNPC.size() > 0)
		NPC->Render();

	SHADOW->Render();
	for (int i = 0; i < m_vecConstruct.size(); i++)
	{
		m_vecConstruct[i]->Render();
	}
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

void cMapManager::SetConstructSize()
{
	if ((SCENE_TAG)SCENE->GetCurrentSceneTag() == SCENE_TOWN_HUMAN)
	{
		m_vecConstruct[0]->SetRadius(0);
		m_vecConstruct[1]->SetRadius(0);
		m_vecConstruct[2]->SetRadius(0);
		m_vecConstruct[3]->SetRadius(0);
		m_vecConstruct[4]->SetRadius(6);

		m_vecConstruct[5]->SetRadius(6);
		m_vecConstruct[6]->SetRadius(6);
		m_vecConstruct[7]->SetRadius(6);
		m_vecConstruct[8]->SetRadius(6);
		m_vecConstruct[9]->SetRadius(6);

		m_vecConstruct[10]->SetRadius(6);
		m_vecConstruct[11]->SetRadius(6);
		m_vecConstruct[12]->SetRadius(6);
		m_vecConstruct[13]->SetRadius(6);
		m_vecConstruct[14]->SetRadius(6);

		m_vecConstruct[15]->SetRadius(6);
		m_vecConstruct[16]->SetRadius(3);
		m_vecConstruct[17]->SetRadius(3);
		m_vecConstruct[18]->SetRadius(3);
		m_vecConstruct[19]->SetRadius(3);

		m_vecConstruct[20]->SetRadius(3);
		m_vecConstruct[21]->SetRadius(3);
		m_vecConstruct[22]->SetRadius(3);
		m_vecConstruct[23]->SetRadius(3);
		m_vecConstruct[24]->SetRadius(6);

		m_vecConstruct[25]->SetRadius(6);
		m_vecConstruct[26]->SetRadius(6);
		m_vecConstruct[27]->SetRadius(6);
		m_vecConstruct[28]->SetRadius(6);
		m_vecConstruct[29]->SetRadius(3);

		m_vecConstruct[30]->SetRadius(3);
		m_vecConstruct[31]->SetRadius(4);
		m_vecConstruct[32]->SetRadius(4);
		m_vecConstruct[33]->SetRadius(4);
		m_vecConstruct[34]->SetRadius(4);

		m_vecConstruct[35]->SetRadius(2);
		m_vecConstruct[36]->SetRadius(2);
		m_vecConstruct[37]->SetRadius(2);
		m_vecConstruct[38]->SetRadius(2);
		m_vecConstruct[39]->SetRadius(2);

		m_vecConstruct[40]->SetRadius(2);
		m_vecConstruct[41]->SetRadius(2);
		m_vecConstruct[42]->SetRadius(2);
		m_vecConstruct[43]->SetRadius(3);
		m_vecConstruct[44]->SetRadius(2);

		m_vecConstruct[45]->SetRadius(2);
		m_vecConstruct[46]->SetRadius(2);
		m_vecConstruct[47]->SetRadius(2);
		m_vecConstruct[48]->SetRadius(2);
	}
	if ((SCENE_TAG)SCENE->GetCurrentSceneTag() == SCENE_TOWN_ORC)
	{
		m_vecConstruct[0]->SetRadius(6);
		m_vecConstruct[1]->SetRadius(6);
		m_vecConstruct[2]->SetRadius(6);
		m_vecConstruct[3]->SetRadius(4);
		m_vecConstruct[4]->SetRadius(4);

		m_vecConstruct[5]->SetRadius(6);
		m_vecConstruct[6]->SetRadius(6);
		m_vecConstruct[7]->SetRadius(4);
		m_vecConstruct[8]->SetRadius(4);
		m_vecConstruct[9]->SetRadius(4);

		m_vecConstruct[10]->SetRadius(4);
		m_vecConstruct[11]->SetRadius(4);
		m_vecConstruct[12]->SetRadius(4);
		m_vecConstruct[13]->SetRadius(4);
		m_vecConstruct[14]->SetRadius(4);

		m_vecConstruct[15]->SetRadius(4);
		m_vecConstruct[16]->SetRadius(4);
		m_vecConstruct[17]->SetRadius(4);
		m_vecConstruct[18]->SetRadius(4);
		m_vecConstruct[19]->SetRadius(4);

		m_vecConstruct[20]->SetRadius(4);
		m_vecConstruct[21]->SetRadius(4);
		m_vecConstruct[22]->SetRadius(4);
		m_vecConstruct[23]->SetRadius(4);
		m_vecConstruct[24]->SetRadius(4);
									 
		m_vecConstruct[25]->SetRadius(2);
		m_vecConstruct[26]->SetRadius(2);
		m_vecConstruct[27]->SetRadius(2);
		m_vecConstruct[28]->SetRadius(2);
		m_vecConstruct[29]->SetRadius(2);
	}

	if ((SCENE_TAG)SCENE->GetCurrentSceneTag() == SCENE_BATTLE_ORC)
	{
		m_vecConstruct[0]->SetRadius(13);
		m_vecConstruct[1]->SetRadius(5);
		m_vecConstruct[2]->SetRadius(5);
		m_vecConstruct[3]->SetRadius(5);
		m_vecConstruct[4]->SetRadius(5);

		m_vecConstruct[5]->SetRadius(5);
		m_vecConstruct[6]->SetRadius(5);
		m_vecConstruct[7]->SetRadius(5);
		m_vecConstruct[8]->SetRadius(5);
		m_vecConstruct[9]->SetRadius(5);

		m_vecConstruct[10]->SetRadius(5);
		m_vecConstruct[11]->SetRadius(5);
		m_vecConstruct[12]->SetRadius(5);
		m_vecConstruct[13]->SetRadius(5);
		m_vecConstruct[14]->SetRadius(5);

		m_vecConstruct[15]->SetRadius(5);
		m_vecConstruct[16]->SetRadius(5);
		m_vecConstruct[17]->SetRadius(5);
		m_vecConstruct[18]->SetRadius(5);
		m_vecConstruct[19]->SetRadius(5);

		m_vecConstruct[20]->SetRadius(2);
		m_vecConstruct[21]->SetRadius(2);
		m_vecConstruct[22]->SetRadius(2);
		m_vecConstruct[23]->SetRadius(2);
		m_vecConstruct[24]->SetRadius(2);

		m_vecConstruct[25]->SetRadius(2);
		m_vecConstruct[26]->SetRadius(2);
		m_vecConstruct[27]->SetRadius(2);
		m_vecConstruct[28]->SetRadius(2);
		m_vecConstruct[29]->SetRadius(2);
	
	
		m_vecConstruct[30]->SetRadius(2);
		m_vecConstruct[31]->SetRadius(2);
		m_vecConstruct[32]->SetRadius(2);
		m_vecConstruct[33]->SetRadius(2);
		m_vecConstruct[34]->SetRadius(2);

		m_vecConstruct[35]->SetRadius(2);
		m_vecConstruct[36]->SetRadius(2);
		m_vecConstruct[37]->SetRadius(2);
		m_vecConstruct[38]->SetRadius(2);
		m_vecConstruct[39]->SetRadius(2);
	
		m_vecConstruct[40]->SetRadius(2);
		m_vecConstruct[41]->SetRadius(2);
		m_vecConstruct[42]->SetRadius(2);
		m_vecConstruct[43]->SetRadius(2);
		m_vecConstruct[44]->SetRadius(2);

		m_vecConstruct[45]->SetRadius(2);
		m_vecConstruct[46]->SetRadius(2);
		m_vecConstruct[47]->SetRadius(2);
		m_vecConstruct[48]->SetRadius(2);

	
	}

	if ((SCENE_TAG)SCENE->GetCurrentSceneTag() == SCENE_BATTLE_HUMAN)
	{
		m_vecConstruct[0]->SetRadius(3);
		m_vecConstruct[1]->SetRadius(4);
		m_vecConstruct[2]->SetRadius(3);
		m_vecConstruct[3]->SetRadius(7);
		m_vecConstruct[4]->SetRadius(2);
		m_vecConstruct[5]->SetRadius(2);
		m_vecConstruct[6]->SetRadius(2);
		m_vecConstruct[7]->SetRadius(2);
		m_vecConstruct[8]->SetRadius(2);
		m_vecConstruct[9]->SetRadius(5);

		m_vecConstruct[10]->SetRadius(2);
		m_vecConstruct[11]->SetRadius(2);
		m_vecConstruct[12]->SetRadius(2);
		m_vecConstruct[13]->SetRadius(2);
		m_vecConstruct[14]->SetRadius(2);
		m_vecConstruct[15]->SetRadius(2);
		m_vecConstruct[16]->SetRadius(2);
		m_vecConstruct[17]->SetRadius(2);
		m_vecConstruct[18]->SetRadius(2);
		m_vecConstruct[19]->SetRadius(2);
	
		m_vecConstruct[20]->SetRadius(7);
		m_vecConstruct[21]->SetRadius(7);
		m_vecConstruct[22]->SetRadius(7);
		m_vecConstruct[23]->SetRadius(7);
		m_vecConstruct[24]->SetRadius(7);
		m_vecConstruct[25]->SetRadius(7);
		m_vecConstruct[26]->SetRadius(7);
		m_vecConstruct[27]->SetRadius(7);
		m_vecConstruct[28]->SetRadius(7);
		m_vecConstruct[29]->SetRadius(7);
	
	
		m_vecConstruct[30]->SetRadius(3);
		m_vecConstruct[31]->SetRadius(3);
		m_vecConstruct[32]->SetRadius(3);
		m_vecConstruct[33]->SetRadius(3);
		m_vecConstruct[34]->SetRadius(3);
		m_vecConstruct[35]->SetRadius(3);
		m_vecConstruct[36]->SetRadius(3);
		m_vecConstruct[37]->SetRadius(3);
		m_vecConstruct[38]->SetRadius(3);
		m_vecConstruct[39]->SetRadius(3);

		m_vecConstruct[40]->SetRadius(3);
		m_vecConstruct[41]->SetRadius(3);
		m_vecConstruct[42]->SetRadius(3);
		m_vecConstruct[43]->SetRadius(3);
		m_vecConstruct[44]->SetRadius(3);
		m_vecConstruct[45]->SetRadius(3);
		m_vecConstruct[46]->SetRadius(3);
		m_vecConstruct[47]->SetRadius(3);
		m_vecConstruct[48]->SetRadius(3);
		m_vecConstruct[49]->SetRadius(3);
	
		m_vecConstruct[50]->SetRadius(2);
		m_vecConstruct[51]->SetRadius(2);
		m_vecConstruct[52]->SetRadius(2);
		m_vecConstruct[53]->SetRadius(2);
		m_vecConstruct[54]->SetRadius(2);
		m_vecConstruct[55]->SetRadius(2);
		m_vecConstruct[56]->SetRadius(2);
		m_vecConstruct[57]->SetRadius(2);
		m_vecConstruct[58]->SetRadius(2);
		m_vecConstruct[59]->SetRadius(2); 
		m_vecConstruct[60]->SetRadius(3);
		m_vecConstruct[61]->SetRadius(2);
		m_vecConstruct[62]->SetRadius(2);
		m_vecConstruct[63]->SetRadius(2);
		m_vecConstruct[64]->SetRadius(2);
		m_vecConstruct[65]->SetRadius(2);
		m_vecConstruct[66]->SetRadius(2);
		m_vecConstruct[67]->SetRadius(2);
		m_vecConstruct[68]->SetRadius(2);
		m_vecConstruct[69]->SetRadius(2); 
		m_vecConstruct[70]->SetRadius(3);
		m_vecConstruct[71]->SetRadius(2);
		m_vecConstruct[72]->SetRadius(2);
		m_vecConstruct[73]->SetRadius(2);
		m_vecConstruct[74]->SetRadius(2);
		m_vecConstruct[75]->SetRadius(2);
		m_vecConstruct[76]->SetRadius(2);
		m_vecConstruct[77]->SetRadius(2);
		m_vecConstruct[78]->SetRadius(2);
		m_vecConstruct[79]->SetRadius(2); 
		m_vecConstruct[80]->SetRadius(3);
		m_vecConstruct[81]->SetRadius(2);
		m_vecConstruct[82]->SetRadius(2);
		m_vecConstruct[83]->SetRadius(2);
		m_vecConstruct[84]->SetRadius(2);
		m_vecConstruct[85]->SetRadius(2);
		m_vecConstruct[86]->SetRadius(2);
		m_vecConstruct[87]->SetRadius(2);
		m_vecConstruct[88]->SetRadius(2);
		m_vecConstruct[89]->SetRadius(2); 
		m_vecConstruct[90]->SetRadius(3);
		m_vecConstruct[91]->SetRadius(2);
		m_vecConstruct[92]->SetRadius(2);
		m_vecConstruct[93]->SetRadius(2);
		m_vecConstruct[94]->SetRadius(2);
		m_vecConstruct[95]->SetRadius(2);
		m_vecConstruct[96]->SetRadius(2);
		m_vecConstruct[97]->SetRadius(2);
		m_vecConstruct[98]->SetRadius(2);
		m_vecConstruct[99]->SetRadius(2);
	
	
		m_vecConstruct[100]->SetRadius(3);
		m_vecConstruct[101]->SetRadius(3);
		m_vecConstruct[102]->SetRadius(3);
		m_vecConstruct[103]->SetRadius(3);
		m_vecConstruct[104]->SetRadius(3);
		m_vecConstruct[105]->SetRadius(3);
		m_vecConstruct[106]->SetRadius(3);
		m_vecConstruct[107]->SetRadius(3);
		m_vecConstruct[108]->SetRadius(3);
	

	
	
	
	
	

	
	
	
	
	

	}

	for (int i = 0; i < m_vecConstruct.size(); i++)
	{
		D3DXCreateSphere(D3DDevice, m_vecConstruct[i]->GetRadius(), 10, 10, &m_vecConstruct[i]->m_pMeshSphere, NULL);
		ZeroMemory(&m_vecConstruct[i]->m_stMtlSphere, sizeof(D3DMATERIAL9));
		m_vecConstruct[i]->m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		m_vecConstruct[i]->m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		m_vecConstruct[i]->m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

		D3DDevice->SetTransform(D3DTS_WORLD, &m_vecConstruct[i]->m_matWorld);
	}
}

void cMapManager::Destroy()
{
	m_vecPosOfNode.clear();
	SAFE_DELETE(m_pMap);
	for (int i = 0; i < m_vecConstruct.size(); i++)
	{
		m_vecConstruct[i]->Destroy();
		SAFE_DELETE(m_vecConstruct[i]);
	}
	m_vecConstruct.clear();
	NPC->Release();
}

D3DXVECTOR2 cMapManager::GetPlayerPos_RateBased(float x, float z)
{
	return m_pMap->GetPlayerPos_RateBased(x, z);
}