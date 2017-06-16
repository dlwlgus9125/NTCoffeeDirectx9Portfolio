#pragma once
#include "stdafx.h"

template <typename T>
class IState
{
	int m_id;

public:
	int ID() { return m_id; }
	void SetID(int id) { m_id = id; }

	virtual void OnBegin(T obj) {}
	virtual void OnUpdate(T obj, float deltaTime) {}
	virtual void OnEnd(T obj) {}
};

template <typename T>
class cStateMachine
{
	T m_obj;

	map<int, IState<T>*> m_stateMap;
	IState<T>* m_pCurrentState;
	int m_currentId;

public:
	cStateMachine(T obj) { m_obj = obj; m_pCurrentState = NULL;}
	~cStateMachine()
	{
		/*for each(auto s in m_stateMap)
		{
			SAFE_DELETE(s);
		}
		m_stateMap.clear();*/
	}
	IState<T>* CurrentState() { return m_pCurrentState; }
	int CurrentID() { return m_pCurrentState != NULL ? m_pCurrentState->ID() : -1; }

	void Register(int stateId, IState<T>* pState)
	{
		m_stateMap[stateId] = pState;
		m_stateMap[stateId]->SetID(stateId);		
	}

	void Play(int stateId)
	{
		if (m_stateMap.find(stateId) != m_stateMap.end())
		{
			m_currentId = stateId;
		}
	}

	void Update(float deltaTime)
	{
		if (m_pCurrentState == NULL || m_pCurrentState->ID() != m_currentId)
		{
			if (m_pCurrentState != NULL) m_pCurrentState->OnEnd(m_obj);
			m_pCurrentState = m_stateMap[m_currentId];
			m_pCurrentState->OnBegin(m_obj);
		}

		if (m_pCurrentState != NULL)
		{
			m_pCurrentState->OnUpdate(m_obj, deltaTime);
		}
	}
};