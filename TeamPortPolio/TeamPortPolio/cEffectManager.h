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
	ST_WEATHER	m_stWeather;

public:
	void Init();
	void OnEnter(ST_WEATHER weather);
	void OnUpdate();
	void Render_Begin();
	void Render_End();
	void Release();
};

