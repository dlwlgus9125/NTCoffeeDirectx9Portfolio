#pragma once

class cCamera;

class cFog
{
	ID3DXEffect*		m_pFogEffect;
	ID3DXBuffer*		m_pErrorBuffer;
	D3DXHANDLE			m_fogTechHandle;

public:
	cFog();
	~cFog();

	void Setup(char* sFullPath);
	void Update(cCamera* pCamera);
	void Destroy();

	void Render_Begin(int passIndex);
	void Render_End();
};

