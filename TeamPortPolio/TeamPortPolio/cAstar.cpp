#include "stdafx.h"
#include "cAstar.h"


bool cAstar::Search()
{
	priority_queue<GraphEdge, vector<GraphEdge>, greater<GraphEdge>> edgeQue;

	edgeQue.push(GraphEdge(m_source, m_source, 0));
	m_cost[m_source] = 0;

	while (edgeQue.size() > 0)
	{
		GraphEdge edge = edgeQue.top();
		edgeQue.pop();

		m_visit[edge.To()] = true;
		m_route[edge.To()] = edge.From();

		if (edge.To() == m_target) return true;

		list<GraphEdge*> edgeList = m_pGraph->GetEdgeList(edge.To());
		list<GraphEdge*>::iterator it;
		for (it = edgeList.begin(); it != edgeList.end(); it++)
		{
			GraphNode* pNode = m_pGraph->GetNode((*it)->To());
			GraphNode* pTargetNode = m_pGraph->GetNode(m_target);
			if (pNode->Active() && !m_visit[pNode->Id()])
			{
				GraphEdge* pEdge = *it;
				float gCost = m_cost[pEdge->From()] + pEdge->Cost();
				D3DXVECTOR3 length = pTargetNode->Pos() - pNode->Pos();
				float hCost = pow(length.x, 2) + pow(length.z, 2);
				float totalCost = gCost*0.5f + hCost;
				if (totalCost < m_cost[pEdge->To()])
				{
					m_cost[pEdge->To()] = totalCost;
					edgeQue.push(GraphEdge(pEdge->From(), pEdge->To(), totalCost));
				}
			}
		}
	}
	return false;
}

vector<int> cAstar::GetRoute()
{
	return m_route;
}

vector<int> cAstar::GetPath()
{
	vector<int> path;
	path.push_back(m_target);
	
	int index = m_target;
	while (m_route[index] != m_source)
	{
		path.push_back(m_route[index]);
		index = m_route[index];
	}
	return path;
}