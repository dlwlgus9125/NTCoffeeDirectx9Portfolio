#pragma once

#define FRUSTUM cFrustum::Instance()
class cFrustum : public Singleton<cFrustum>
{
public:
	cFrustum();
	~cFrustum();

private:
	vector<D3DXPLANE>   m_vecPlane;

public:
	void Setup();
	void Update();
	bool IsIn(MeshSpere pShere/**/);
	bool IsIn(ST_SPHERE* pSphere);
	bool IsIn(D3DXVECTOR3 vec3);

	void PlaneSetup();

};

