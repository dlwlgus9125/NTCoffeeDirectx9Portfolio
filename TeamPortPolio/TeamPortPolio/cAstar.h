#pragma once
#include "cGraph.h"

class cAstar
{
	cGraph* m_pGraph;

	int m_source;
	int m_target;

	vector<float> m_cost;
	vector<bool> m_visit;
	vector<int> m_route;

public:
	cAstar(cGraph* pGraph, int source, int target) :
		m_cost(pGraph->NodeCount(), 999999.9f),
		m_visit(pGraph->NodeCount(), false),
		m_route(pGraph->NodeCount(), -1)
	{
		m_pGraph = pGraph;
		m_source = source;
		m_target = target;
		if (m_target < 0)m_target = source;
	}

	bool Search();

	vector<int> GetRoute();

	vector<int> GetPath();
};