#pragma once

#define NPC cNpcManager::Instance()

class cSkinnedMesh;

class cNpcManager : public Singleton<cNpcManager>
{
protected:
	std::vector<ST_SPHERE>     m_vecSphere;
	std::vector<ST_NPC_INFO>   m_vecNpc;
	LPD3DXMESH                 m_pMesh;
	D3DMATERIAL9               m_mtrl;

	std::vector<cSkinnedMesh*> m_vecSkin;
	std::vector<ST_Npc>        m_vecST;
	// >> : Font
	LOGFONT                    m_lf;
	std::vector<HDC>           m_vechdc;
	std::vector<HFONT>         m_vechFont;
	std::vector<HFONT>         m_vechFontOld;
	std::vector<ID3DXMesh*>    m_vecFont;

public:
	cNpcManager();
	~cNpcManager();

	void FirstInit();
	void Init(std::vector<ST_NPC_INFO> vecNpc);
	void Render();
	void Update(std::vector<ST_NPC_INFO> vecNpc);
	void Release();
	void SetMtrl();
	void LoadSkinnedMesh();
	void SetupFont();
	void SetText();
	void Render_Text();

	vector<ST_SPHERE>& GetSphere();
};

