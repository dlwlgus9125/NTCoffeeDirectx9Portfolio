#pragma once
#include "Singleton.h"
#include "cGraph.h"
#include "cAstar.h"

#define ASTAR cAstarManager::Instance()


class cAstarManager :
	public Singleton<cAstarManager>
{
	cGraph*            m_graph;
	cGraph*            m_PathGraph;

	vector<D3DXVECTOR3> m_vecPosOfNode;


	bool                    m_isMapLoadingComplete;
public:
	void Init();
	void Setup(vector<D3DXVECTOR3> vecPosOfNode);
	void DestroyForChangeScene();
	void SetupGraph();

	void AddEdge(int from, int col, int row);
	void AddEdgeInPathGraph(int from, int col, int row);
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

