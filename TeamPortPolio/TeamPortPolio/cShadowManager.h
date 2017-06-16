#pragma once
class cObject;
class cMtlTex;
class cConstruct;
#define SHADOW cShadowManager::GetInstance()

class cShadowManager
{
protected:
	vector<cConstruct*>      m_vecConstruct;
	D3DLIGHT9				 m_light;
	D3DXMATRIXA16            m_matWorld;

	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);
public:
	SINGLETONE(cShadowManager);

	void Setup(std::vector<cConstruct*> vecList);
	void Render();
	void Destroy();
	void SetLight();
};

