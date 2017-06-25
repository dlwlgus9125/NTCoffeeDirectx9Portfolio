#include "stdafx.h"
#include "cThreadManager.h"


unsigned __stdcall Thread_Astar_Update(LPVOID lpParam)
{
	while (1)
	{
		EnterCriticalSection(&THREAD->GetCritical_Section());
		if (OBJECT->GetPlayer() != NULL)ASTAR->Update();
		LeaveCriticalSection(&THREAD->GetCritical_Section());
	}
	return 0;
}

unsigned __stdcall Thread_Astar_FindPath(LPVOID lpParam)
{

	EnterCriticalSection(&THREAD->GetCritical_Section());
	if (OBJECT->GetPlayer() != NULL)ASTAR->PathUpdate();//OBJECT->AddArmy();
	LeaveCriticalSection(&THREAD->GetCritical_Section());

	return 0;
}

void cThreadManager::Init()
{
	m_mapHandle[HANDLE_ASTAR_FINDINDEX].m_dwThl = 0;
	m_mapHandle[HANDLE_ASTAR_FINDINDEX].m_handle = NULL;

	m_mapHandle[HANDLE_ATSTAR_FINDPATH].m_dwThl = 0;
	m_mapHandle[HANDLE_ATSTAR_FINDPATH].m_handle = NULL;

	InitializeCriticalSection(&m_cs);

	/*m_mapHandle[HANDLE_ASTAR_FINDINDEX].m_handle=
		(HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall *)(void*))Thread_Astar_Update, NULL, 0, (unsigned*)& m_mapHandle[HANDLE_ASTAR_FINDINDEX].m_dwThl);
	m_mapHandle[HANDLE_ATSTAR_FINDPATH].m_handle =
		(HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall *)(void*))Thread_Astar_FindPath, NULL, CREATE_SUSPENDED, (unsigned*)& m_mapHandle[HANDLE_ATSTAR_FINDPATH].m_dwThl);
*/
}

void cThreadManager::CreateFindPathThread(int key)
{
	m_mapHandle[key].m_handle =
		(HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall *)(void*))Thread_Astar_FindPath, NULL, 0, (unsigned*)& m_mapHandle[key].m_dwThl);

}
void cThreadManager::CreateFindIndexThread(int key)
{
	m_mapHandle[key].m_handle =
		(HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall *)(void*))Thread_Astar_Update, NULL, 0, (unsigned*)& m_mapHandle[key].m_dwThl);

}
void cThreadManager::TerminateThreadByKey(int key)
{
	if (TerminateThread(m_mapHandle[key].m_handle, 0))
	{
		CloseHandle(m_mapHandle[key].m_handle);
	}

}

void cThreadManager::SuspendThreadByKey(int key)
{
	SuspendThread(m_mapHandle[key].m_handle);
}

bool cThreadManager::IsReCreateFindPathThread(int key)
{
	static bool isFirstResume = false;

	if (GetStillThread(key) != STILL_ACTIVE)
	{
		CreateFindPathThread(key);
		return false;
	}
	else if (isFirstResume == false)
	{
		isFirstResume = true;
		ResumeThread(m_mapHandle[key].m_handle);
		return true;
	}
	else
	{
		return true;
	}
}

void cThreadManager::Destroy()
{
	for each(auto c in m_mapHandle)
	{
		TerminateThreadByKey(c.first);
	}
}

void cThreadManager::CloseThreadManager()
{
	HANDLE* handles;
	int size = 0;

	THREAD->TerminateThreadByKey(HANDLE_ASTAR_FINDINDEX);
	THREAD->TerminateThreadByKey(HANDLE_ATSTAR_FINDPATH);
}

DWORD cThreadManager::GetStillThread(int key)
{
	DWORD exitCode;
	GetExitCodeThread(m_mapHandle[key].m_handle, &exitCode);
	return exitCode;
}
