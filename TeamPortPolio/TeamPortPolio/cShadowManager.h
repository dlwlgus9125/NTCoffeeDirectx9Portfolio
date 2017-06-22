#pragma once
class cObject;
class cMtlTex;
class cConstruct;
class cPlayer;
#define SHADOW cShadowManager::GetInstance()

class cShadowManager
{
protected:
	vector<cConstruct*>      m_vecConstruct;
	float                    m_alpha;
	D3DXVECTOR3              m_shadowLight;
	D3DXMATRIXA16            m_matWorld;

	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);
public:
	SINGLETONE(cShadowManager);

	void Setup(std::vector<cConstruct*>& vecList);
	void SetLightDir(D3DXVECTOR3 dir);
	void Render();
	void SetAlpha(float alpha);
	void Destroy();
	void Init();
};

