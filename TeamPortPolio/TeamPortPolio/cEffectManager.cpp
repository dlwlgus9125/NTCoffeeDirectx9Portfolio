#include "stdafx.h"
#include "cEffectManager.h"


void cEffectManager::Init(bool isFogOn, int fogPassIndex, bool isSnowOn, bool isRainOn)
{
	int size = MAP->GetMap()->GetCellPerRow() * MAP->GetMap()->GetCellSpace();
	if (isFogOn)
	{
		m_pFog = new cFog();
		m_pFog->Setup("obj/Effect/Fog/fog.txt");
	}

	if (isSnowOn)
	{
		m_pSnow = new cWeather();
		m_pSnow->Setup(size, size, size, 1500);
	}

	if (isRainOn)
	{
		m_pRain = new cWeather();
		m_pRain->Setup(size, size, size, 3000);
	}
}

void cEffectManager::Update()
{
	if (m_pFog) m_pFog->Update(CAMERA->GetCamera());
	if (m_pSnow) m_pSnow->Update(0.1f, 0.1f);
	if (m_pRain) m_pRain->Update(0.1f, 1.0f);
}

void cEffectManager::Render()
{
	if (m_pSnow) m_pSnow->Render("obj/Effect/Snow/Snow.tga");
	if (m_pRain) m_pRain->Render("obj/Effect/Rain/Rain.tga");
}

void cEffectManager::Release()
{
	if (m_pFog) SAFE_DELETE(m_pFog);
	if (m_pSnow) SAFE_DELETE(m_pSnow);
}

void cEffectManager::Render_Fog_Begin()
{
	if (m_pFog) m_pFog->Render_Begin(m_nFogPassIndex);
}

void cEffectManager::Render_Fog_End()
{
	if (m_pFog) m_pFog->Render_End();
}