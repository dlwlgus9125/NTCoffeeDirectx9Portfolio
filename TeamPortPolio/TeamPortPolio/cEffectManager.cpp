#include "stdafx.h"
#include "cEffectManager.h"


void cEffectManager::Init(ST_WEATHER weather)
{
	m_pFog = NULL;
	m_pSnow = NULL; 
	m_pRain = NULL;

	m_stWeather = weather;

	int cellPerRow = MAP->GetMap()->GetCellPerRow();
	int cellSpace = MAP->GetMap()->GetCellSpace();
	int size = cellPerRow * cellSpace;

	if (weather.GetFogOn())
	{
		m_pFog = new cFog();
		m_pFog->Setup("obj/Effect/Fog/fog.txt");
	}

	if (weather.GetSnowOn())
	{
		m_pSnow = new cWeather();
		m_pSnow->Setup(size, size, size, weather.GetCount_Snow());
	}

	if (weather.GetMove_Rain())
	{
		m_pRain = new cWeather();
		m_pRain->Setup(size, size, size, weather.GetCount_Rain());
	}
}

void cEffectManager::Update()
{
	if (m_pFog) m_pFog->Update(CAMERA->GetCamera());
	if (m_pSnow) m_pSnow->Update(m_stWeather.GetMove_Snow(), m_stWeather.GetSpeed_Snow());
	if (m_pRain) m_pRain->Update(m_stWeather.GetMove_Rain(), m_stWeather.GetSpeed_Rain());
}

void cEffectManager::Release()
{
	if (m_pFog) { m_pFog->Destroy(); SAFE_DELETE(m_pFog) };
	if (m_pSnow) { SAFE_DELETE(m_pSnow) };
	if (m_pRain) { SAFE_DELETE(m_pRain) };
}

void cEffectManager::Render_Begin()
{
	if (m_pFog) m_pFog->Render_Begin(m_stWeather.GetFogPassIndex());
	if (m_pSnow) m_pSnow->Render("obj/Effect/Snow/Snow.tga");
	if (m_pRain) m_pRain->Render("obj/Effect/Rain/Rain.tga");
}

void cEffectManager::Render_End()
{
	if (m_pFog) m_pFog->Render_End();
}