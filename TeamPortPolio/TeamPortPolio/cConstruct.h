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
	vector<D3DXVECTOR3> m_vecVertex;
public:
	cConstruct();
	~cConstruct();

	void Setup(char* szFolder, char* szFile, bool isChecked);
	void Update();
	void Render();

	void Create(int sIndex);
	void Destroy();
	void SetVertex(vector<D3DXVECTOR3> v) { m_vecVertex = v; }
	vector<D3DXVECTOR3> GetVectorVertex() { return m_vecVertex; }
	vector<ST_LINE_VERTEX> GetTranfromedVector(vector<D3DXVECTOR3> d);

};