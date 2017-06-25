#include "stdafx.h"
#include "cLog.h"

void cLog::AddLog(string mapData)
{
	int index = m_mapLog.size();
	m_mapLog[index] = mapData;
}

void cLog::DeleteLog(string mapData)
{
	for (map<int, string>::iterator it = m_mapLog.begin(); it != m_mapLog.end();)
	{
		if ((*it).second == mapData) it = m_mapLog.erase(it);
		else it++;
	}
}

void cLog::Setup()
{
	m_mapLog = {};
}

void cLog::Update()
{
	if (INPUT->IsKeyDown(VK_F12)) Render();
}

void cLog::Render()
{ 
	cout << " [ cLog 데이터 출력 시작 ]" << endl << endl;
	for (map<int, string>::iterator it = m_mapLog.begin(); it != m_mapLog.end(); it++)
	{
		cout << (*it).first << ' : ' << (*it).second << endl;
	}
	cout << " [ cLog 데이터 출력 종료 ]" << endl << endl;
}