#pragma once

#define NPC cNpcManager::Instance()

class cNpcManager : public Singleton<cNpcManager>
{
protected:
	std::vector<ST_SPHERE>   m_vecSphere;
	std::vector<ST_NPC_INFO> m_vecNpc;
	LPD3DXMESH               m_pMesh;
	D3DMATERIAL9             m_mtrl;

public:
	cNpcManager();
	~cNpcManager();

	void Init(std::vector<ST_NPC_INFO> vecNpc);
	void Render();
	void Update(std::vector<ST_NPC_INFO> vecNpc);
	void Release();
	void SetMtrl();
};

