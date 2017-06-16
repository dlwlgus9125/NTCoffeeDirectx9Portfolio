#pragma once
#include "cFrustum.h"
class GraphNode
{
	bool m_active;
	int m_id;
	D3DXVECTOR3 m_pos;
	ST_SPHERE   m_sphere;

public:
	GraphNode(int id = 0) { m_sphere.fRadius = 0.1f; }

	bool Active() { return m_active; }
	int Id() { return m_id; }
	void SetID(int id) { m_id = id; }
	D3DXVECTOR3 Pos() { return m_pos; }
	void SetActive(bool active) { m_active = active; }
	void SetPos(D3DXVECTOR3 pos) 
	{ 
		m_pos = pos;
		m_sphere.vCenter = m_pos;
	}
	ST_SPHERE GetSphere() { return m_sphere; }
};

class GraphEdge
{
	int m_from;
	int m_to;
	float m_cost;
	
public:
	GraphEdge(int from, int to, float cost) : m_from(from), m_to(to), m_cost(cost){}

	void SetCost(float cost) { m_cost = cost; }

	int From() { return m_from; }
	int To() { return m_to; }
	float Cost() { return m_cost; }

	bool operator > (const GraphEdge& edge) const { return m_cost > edge.m_cost; }
	bool operator < (const GraphEdge& edge) const { return m_cost < edge.m_cost; }
	
};

class cGraph
{
	typedef vector<GraphNode*>			NodeVector;
	typedef list<GraphEdge*>			EdgeList;
	typedef list<GraphEdge*>::iterator	EdgeListIter;
	typedef vector<EdgeList>			EdgeListVector;
	LPD3DXLINE m_line;
	NodeVector m_nodes;
	EdgeListVector m_edges;
public:
	cGraph(int nodeCount);

	~cGraph();

	int NodeCount();

	bool IsValid(int nodeIndex);

	GraphNode* GetNode(int index);

	EdgeList GetEdgeList(int index)
	{
		if (IsValid(index)) { return m_edges[index]; }
		return EdgeList();
	}

	GraphEdge* GetEdge(int from, int to);

	void AddEdge(int from, int to, float cost = 0);

	void RemoveEdge(int from, int to);
	void Render();
	/*void Render()
	{
	for (int i = 0; i < m_nodes.size(); i++)
	{
	if (m_nodes[i]->Active())
	{
	RENDER->FillCircle(m_nodes[i]->Pos(), 5, ColorF::Green);

	EdgeList list = GetEdgeList(i);
	for (EdgeListIter it = list.begin(); it != list.end(); it++)
	{
	GraphNode* pFromNode = GetNode((*it)->From());
	GraphNode* pToNode = GetNode((*it)->To());
	if (pToNode->Active())
	{
	RENDER->DrawLine(pFromNode->Pos(), pToNode->Pos(), ColorF::Green);
	}
	}
	}
	}
	}*/
};