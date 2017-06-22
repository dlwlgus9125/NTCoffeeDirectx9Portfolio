#include "stdafx.h"
#include "cTimeManager.h"


void cTimeManager::Init(int fps)
{
	// 초당 주파수 계산
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);

	// 주파수당 시간 계산
	m_frequencyTime = 1.0 / m_frequency;

	// 시작 카운트 계산
	QueryPerformanceCounter((LARGE_INTEGER*)&m_startCount);
	m_currentCount = m_startCount;
	m_previousCount = m_startCount;

	// 프레임당 시간 계산
	m_fps = fps;
	m_frameTime = 1.0 / fps;

	m_dwLastUpdateTime = GetTickCount();

	m_oneSecond = 0.0f;
}

int cTimeManager::FPS() { return m_fps; }
float cTimeManager::StartTime() { return m_startCount * m_frequencyTime; }
float cTimeManager::CurrentTime() { return m_currentCount * m_frequencyTime; }
float cTimeManager::DeltaTime() { return m_deltaTime; }

bool cTimeManager::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_currentCount);

	m_deltaTime = (m_currentCount - m_previousCount) * m_frequencyTime;

	DWORD dwCurrentTime = GetTickCount();
	m_fEllapsedTime = (dwCurrentTime - m_dwLastUpdateTime);
	m_dwLastUpdateTime = dwCurrentTime;

	if (m_deltaTime > m_frameTime)
	{
		m_previousCount = m_currentCount;


		if (m_oneSecond > 1.0f)
		{
			m_oneSecond = 0.0f;
		}
		m_oneSecond += m_deltaTime;

		return true;
	}
	return false;
}

bool cTimeManager::UpdateOneSecond()
{	
	if (m_oneSecond >=0.9f)
	{
		return true;
	}
	return false;
}

void cTimeManager::ElapsedUpdate()
{
	DWORD dwCurrentTime = GetTickCount();
	m_fEllapsedTime = (dwCurrentTime - m_dwLastUpdateTime) / 1000.f;
	m_dwLastUpdateTime = dwCurrentTime;
}

float cTimeManager::GetElapsedTime()
{
	return m_fEllapsedTime/1000.0f;
}

float cTimeManager::GetLastUpdateTime()
{
	return m_dwLastUpdateTime / 1000.f;
}
