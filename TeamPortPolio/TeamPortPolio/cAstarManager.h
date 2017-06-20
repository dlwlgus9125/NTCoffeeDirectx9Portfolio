#pragma once
#include "Singleton.h"
#include "cGraph.h"
#include "cAstar.h"

#define ASTAR cAstarManager::Instance()


class cAstarManager :
	public Singleton<cAstarManager>
{
	cGraph*            m_graph;
	vector<int> m_path;
	vector<int> vecRoad;

	vector<D3DXVECTOR3> m_vecPosOfNode;


	bool                    m_isMapLoadingComplete;
public:
	void Setup(vector<D3DXVECTOR3> vecPosOfNode);
	void SetupThread();
	cGraph* SetupGraph();

	void AddEdge(int from, int col, int row);
	void AddEdgeTest(cGraph * pGraph, int from, int col, int row);
	vector<int> GetPath(int chrindex, int targetIndex);
	void Release();
	void Update();
	void PathUpdate();
	void Render();
	cGraph* GetGraph() { return m_graph; }


	bool GetCursorIndex(int& TargetIndex);
	void SetMapLoadingComplete(bool complete) { m_isMapLoadingComplete = complete; }
	bool IsLoadingComplete() { return m_isMapLoadingComplete; }

	void SetObjectIndex();
	void SetLeaderPath();
	void SetLeaderPath(cLeader * pLeader);
	void SetTargetOfLeader();

	
	
	

};

