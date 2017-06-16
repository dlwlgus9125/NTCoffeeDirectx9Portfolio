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
	cSkyBox*				m_pSkyBox;
	cHeightMap*			    m_pMap;
	vector<cConstruct*>		m_vecConstruct;
	vector<D3DXVECTOR3>     m_vecPosOfNode;
	int                     m_CellPerRow;
	float                   m_fCellSpace;

	ST_PNT_VERTEX           m_vPositionVertex;
	
public:
	cMapManager();
	~cMapManager();

	void Init(string fileName);
	void Update();
	void Render();

	bool GetHeight(IN float x, OUT float&y, IN float z);
	LPD3DXMESH GetMesh();
	float GetMaxX();
	float GetMinX();

	void Destroy();

	cHeightMap* GetMap() { return m_pMap; }

	
};

