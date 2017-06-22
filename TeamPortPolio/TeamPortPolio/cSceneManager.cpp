#include "stdafx.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
{
	m_current = -1;
	m_currentScene = NULL;
	m_isSoundPlayed = false;
}

cSceneManager::~cSceneManager()
{

}

void cSceneManager::StartScene(int tag)
{
	if (m_scenes.find(tag) == m_scenes.end())
	{
		::MessageBox(0, "StartScene error - Can't Found Scene ", 0, 0);
	}
	m_current = tag;
	cIScene* currentScene = GetScene(m_current);
	currentScene->OnEnter();
}

void cSceneManager::Register(int tag, cIScene * pScene)
{
	if (m_scenes.find(tag) == m_scenes.end())
	{
		m_scenes[tag] = pScene;
		m_scenes[tag]->SetTag(tag);
	}
}

void cSceneManager::ChangeScene(int tag)
{
	m_current = tag;
}

void cSceneManager::Update()
{
	if (m_currentScene == NULL || m_current != m_currentScene->Tag())
	{
		if (m_currentScene != NULL)
			m_currentScene->OnExit();
		m_currentScene = GetScene(m_current);
		if (m_currentScene != NULL)
		{
			D3DDevice->Clear(NULL,
				NULL,
				D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
				D3DCOLOR_XRGB(47, 121, 112),
				1.0f, 0);
			m_currentScene->OnEnter();
		}
	}

	if (m_currentScene != NULL) m_currentScene->OnUpdate();
}

void cSceneManager::Render()
{	
	if (m_currentScene != NULL) 
		m_currentScene->OnRender();
	else
		::MessageBox(0, TEXT("Render error - currentScene == NULL"), 0, 0);
	
}

void cSceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_current < 0) return;

	cIScene* currentScene = GetScene(m_current);
	if (currentScene != NULL)
		currentScene->WndProc(hWnd, message, wParam, lParam);
	else
		::MessageBox(0, TEXT("WndProc error - currentScene == NULL"), 0, 0);
}

int cSceneManager::Current()
{
	return m_current;
}

cIScene * cSceneManager::GetScene(int tag)
{
	if (m_scenes.find(tag) == m_scenes.end())
	{
		::MessageBox(0, TEXT("GetScene error"), 0, 0);
		return NULL;
	}

	return m_scenes[tag];
}
