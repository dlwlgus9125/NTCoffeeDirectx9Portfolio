#pragma once
#include "cObject.h"

class cMtlTex;
class cObjLoader;

class cConstruct : public cObject
{
private:

	SYNTHESIZE(LPD3DXMESH, m_pObjMesh, ObjMesh);
	SYNTHESIZE(vector<cMtlTex*>, m_vecObjMtlTex, VecObjMtlTex);

	SYNTHESIZE(int, m_nSObjID, SObjID);
	SYNTHESIZE(D3DXVECTOR3, m_vScale, Scale);
	SYNTHESIZE(float, m_fRotX, RotationX);
	SYNTHESIZE(float, m_fRotY, RotationY);
	SYNTHESIZE(float, m_fRotZ, RotationZ);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);

	SYNTHESIZE(vector<ST_PNT_VERTEX>, m_vecVertex,VecVertex);
	SYNTHESIZE(float, m_fRadius, Radius);

public:
	cConstruct();
	~cConstruct();

	void Setup(char* szFolder, char* szFile, bool isChecked);
	void Update();
	void Render();

	void Create(int sIndex);
	void Destroy();

	D3DXMATRIXA16		m_matWorld;
	LPD3DXMESH       m_pMeshSphere;
	D3DMATERIAL9    m_stMtlSphere;

};