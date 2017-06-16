#pragma once
#include "Singleton.h"
#include "cFog.h"
#include "cWeather.h"
#include "cCamera.h"

#define EFFECT cEffectManager::Instance()

class cEffectManager : public Singleton<cEffectManager>
{
	cFog*		m_pFog;
	cWeather*	m_pSnow;
	cWeather*	m_pRain;

	int			m_nFogPassIndex;

public:
	void Init(bool isFogOn, int fogPassIndex, bool isSnowOn, bool isRainOn);
	void Update();
	void Render();
	void Render_Fog_Begin();
	void Render_Fog_End();
	void Release();
};

