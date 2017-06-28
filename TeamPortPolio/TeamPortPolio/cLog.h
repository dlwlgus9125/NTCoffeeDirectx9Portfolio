#pragma once

#include "Singleton.h"

class cLog : public Singleton<cLog>
{
	map<int, string> m_mapLog;
public:
	void AddLog(string mapData);
	void DeleteLog(string mapData);

	void Setup();
	void Update();
	void Render();
};

