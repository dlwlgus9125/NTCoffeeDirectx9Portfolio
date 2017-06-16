#pragma once

class cObject;
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


public:
	cConstruct();
	~cConstruct();

	void Setup(char* szFolder, char* szFile, bool isChecked);
	void Update();
	void Render();

	void Create(int sIndex);
	void Destroy();
};