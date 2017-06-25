#pragma once

// >> 
#include "cSkyBox.h"
#include "cHeightMap.h"
#include "cObjLoader.h"
#include "cConstruct.h"
// << 
#define MAP cMapManager::Instance()

class cMapManager : public Singleton<cMapManager>
{
	cSkyBox*				          m_pSkyBox;
	cHeightMap*			              m_pMap;
	vector<cConstruct*>		          m_vecConstruct;

	vector<D3DXVECTOR3>               m_vecPosOfNode;
	int                               m_CellPerRow;
	float                             m_fCellSpace;

	ST_PNT_VERTEX           m_vPositionVertex;
	   
	SYNTHESIZE(ST_WEATHER, m_stWeather, Weather);
	SYNTHESIZE(ST_SHADOW, m_stShadow, Shadow);
	SYNTHESIZE(vector<ST_NPC_INFO>, m_vecStNPC, VecNPC);

public:
	cMapManager();
	~cMapManager();
	void StartMain() { m_pSkyBox = NULL; m_pMap = NULL; }
	void Init(int sceneID);
	void Update();
	void Render();

	bool GetHeight(IN float x, OUT float&y, IN float z);
	LPD3DXMESH GetMesh();
	float GetMaxX();
	float GetMinX();
	void SetConstructSize();
	void Destroy();
	vector<cConstruct*>	GetvecConstruct() { return m_vecConstruct; }
	cHeightMap* GetMap() { return m_pMap; }


	vector<D3DXVECTOR3>     GetVecPosOfNode() { return m_vecPosOfNode; }
	D3DXVECTOR2 GetPlayerPos_RateBased(float x, float z);
};

