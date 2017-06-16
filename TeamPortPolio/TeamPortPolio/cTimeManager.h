#pragma once
#include <Windows.h>
#include "Singleton.h"

#define TIME	cTimeManager::Instance()

class cTimeManager : public Singleton<cTimeManager>
{
	LONGLONG m_frequency;		// 초당 주파수
	LONGLONG m_startCount;		// 시작 카운트
	LONGLONG m_currentCount;	// 현재 카운트
	LONGLONG m_previousCount;	// 이전 카운트

	float m_frequencyTime;		// 주파수당 시간
	float m_frameTime;			// 프레임당 시간
	float m_deltaTime;
	float m_oneSecond;

	int m_fps;					// 초당 프레임 수

	//>>캐릭터 렌더용
	DWORD m_dwLastUpdateTime;
	float m_fEllapsedTime;

public:
	void Init(int fps);

	int FPS();
	float StartTime();
	float CurrentTime();
	float DeltaTime();

	bool Update();

	bool UpdateOneSecond();


	//>>캐릭터 렌더용
	void  ElapsedUpdate();
	float GetElapsedTime();
	float GetLastUpdateTime();
};