#pragma once

#define THREAD cThreadManager::Instance()

enum HANDLE_KEY
{
	HANDLE_ASTAR_FINDINDEX,
	HANDlE_ATSTAR_FINDPATH,
};

struct ThreadHandle
{
	HANDLE m_handle;
	DWORD  m_dwThl;
};


class cThreadManager : public Singleton<cThreadManager>
{
	map<int, ThreadHandle> m_mapHandle;
	CRITICAL_SECTION m_cs;
public:
	void Init();
	void CreateFindPathThread(int key);
	void TerminateThreadByKey(int key);
	bool IsReCreateFindPathThread(int key);
	void Destroy();
	void CloseThreadManager();
	CRITICAL_SECTION GetCritical_Section() { return m_cs; }
	DWORD GetStillThread(int key);
};

