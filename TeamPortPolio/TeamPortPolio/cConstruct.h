#pragma once
#include "cObject.h"

class cMtlTex;
class cObjLoader;

class cConstruct : public cObject
{
private:
	D3DXMATRIXA16		m_matWorld;

	SYNTHESIZE(LPD3DXMESH, m_pObjMesh, ObjMesh);
	SYNTHESIZE(vector<cMtlTex*>, m_vecObjMtlTex, VecObjMtlTex);

	SYNTHESIZE(int, m_nSObjID, SObjID);
	SYNTHESIZE(D3DXVECTOR3, m_vScale, Scale);
	SYNTHESIZE(float, m_fRotX, RotationX);
	SYNTHESIZE(float, m_fRotY, RotationY);
	SYNTHESIZE(float, m_fRotZ, RotationZ);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(ST_SPHERE, m_stSphere, Sphere);
	
	SYNTHESIZE(vector<ST_PNT_VERTEX>, vecVertex,VecVertexOrigin);
	vector<D3DXVECTOR3> m_vecTranslatedVertex;
	vector<ST_LINE_VERTEX> m_vecLineVertex;

	D3DXVECTOR3 m_vMin;
	D3DXVECTOR3 m_vMax;
public:
	cConstruct();
	~cConstruct();

	void Setup(char* szFolder, char* szFile, bool isChecked);
	void Update();
	void Render();

	void Create(int sIndex);
	void Destroy();
	vector<D3DXVECTOR3> GetVecVertex() { return m_vecTranslatedVertex; }
	vector<ST_LINE_VERTEX> GetLineVertex() { return m_vecLineVertex; }
	LPD3DXMESH      m_pMeshSphere;
	D3DMATERIAL9    m_stMtlSphere;
};