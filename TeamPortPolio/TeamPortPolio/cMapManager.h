#pragma once

// >> 
#include "cSkyBox.h"
#include "cHeightMap.h"
#include "cObjLoader.h"
#include "cConstruct.h"
#include "cNonPlayerCharacter.h"
// << 
#define MAP cMapManager::Instance()

class cMapManager : public Singleton<cMapManager>
{
	cSkyBox*				          m_pSkyBox;
	cHeightMap*			              m_pMap;
	vector<cConstruct*>		          m_vecConstruct;

	std::vector<cNonPlayerCharacter*> m_vecNpc;

	vector<D3DXVECTOR3>               m_vecPosOfNode;
	int                               m_CellPerRow;
	float                             m_fCellSpace;

	ST_PNT_VERTEX                     m_vPositionVertex;
	
	ST_WEATHER				          m_stWeather;
	ST_SHADOW				          m_stShadow;
public:
	cMapManager();
	~cMapManager();

	void Init(int sceneID);
	void Update();
	void Render();

	bool GetHeight(IN float x, OUT float&y, IN float z);
	LPD3DXMESH GetMesh();
	float GetMaxX();
	float GetMinX();

	void Destroy();

	cHeightMap* GetMap() { return m_pMap; }

	
};

