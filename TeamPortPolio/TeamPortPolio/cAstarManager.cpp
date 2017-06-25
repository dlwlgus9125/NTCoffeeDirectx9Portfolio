#include "stdafx.h"
#include "cAstarManager.h"
#include "cRay.h"
#include "cObject.h"
#include "cPlayer.h"
#include "cLeader.h"
#include "cUnit.h"




void cAstarManager::Init()
{
	m_PathGraph = m_graph = NULL;
}

void cAstarManager::Setup(vector<D3DXVECTOR3> vecPosOfNode)
{
	m_vecPosOfNode = vecPosOfNode;

	m_graph = new cGraph(m_vecPosOfNode.size());
	int col = sqrt(m_vecPosOfNode.size());
	for (int i = 0; i < m_vecPosOfNode.size(); i++)
	{
		m_graph->GetNode(i)->SetActive(false);

		D3DXVECTOR3 pos;//<-여기에 heightmap연산해서 좌표넣기
		//그렇게하면 높이값까지 코스트로 적용이 가능하기때문에 오히려 자연스러움

		m_graph->GetNode(i)->SetPos(m_vecPosOfNode[i]);
		int index = 0;
		MAP->GetMap()->GetIndex(m_vecPosOfNode[i].x, m_vecPosOfNode[i].z, index);
		m_graph->GetNode(i)->SetID(index);
	}
	for (int i = 0; i < m_vecPosOfNode.size(); i++)
	{
		if (m_vecPosOfNode[i].y == 0.0f || m_vecPosOfNode[i].y == 1.0f || m_vecPosOfNode[i].y == 2.0f || m_vecPosOfNode[i].y == 3.0f || m_vecPosOfNode[i].y == 4.0f)
		{
			m_graph->GetNode(i)->SetActive(true);
		}
	}
	for (int i = 0; i < m_vecPosOfNode.size(); i++)
	{
		int x = i % col;	// 열 번호
		int z = i / col;	// 줄 번호	

		AddEdge(i, x - 1, z + 0);//해당 엣지를 만들때 높이에따라서 엣지추가여부 연산
		AddEdge(i, x + 1, z + 0);
		AddEdge(i, x + 0, z - 1);//엣지는 일단 노드 포지션을 전부 맞춘후
		AddEdge(i, x + 0, z + 1);
		AddEdge(i, x - 1, z - 1);
		AddEdge(i, x - 1, z + 1);
		AddEdge(i, x + 1, z - 1);
		AddEdge(i, x + 1, z + 1);
	}
	SetupGraph();
	THREAD->CreateFindIndexThread(HANDLE_ASTAR_FINDINDEX);
	//THREAD->CreateFindPathThread(HANDLE_ATSTAR_FINDPATH);
}

void cAstarManager::DestroyForChangeScene()
{
	THREAD->TerminateThreadByKey(HANDLE_ASTAR_FINDINDEX);
	THREAD->TerminateThreadByKey(HANDLE_ATSTAR_FINDPATH);
	//
}

void cAstarManager::SetupGraph()
{
	m_PathGraph = new cGraph(m_vecPosOfNode.size());
	int col = sqrt(m_vecPosOfNode.size());
	for (int i = 0; i < m_vecPosOfNode.size(); i++)
	{
		m_PathGraph->GetNode(i)->SetActive(false);

		D3DXVECTOR3 pos;//<-여기에 heightmap연산해서 좌표넣기
						//그렇게하면 높이값까지 코스트로 적용이 가능하기때문에 오히려 자연스러움

		m_PathGraph->GetNode(i)->SetPos(m_vecPosOfNode[i]);
		int index = 0;
		MAP->GetMap()->GetIndex(m_vecPosOfNode[i].x, m_vecPosOfNode[i].z, index);
		m_PathGraph->GetNode(i)->SetID(index);
	}
	for (int i = 0; i < m_vecPosOfNode.size(); i++)
	{
		if (m_vecPosOfNode[i].y == 0.0f || m_vecPosOfNode[i].y == 1.0f || m_vecPosOfNode[i].y == 2.0f || m_vecPosOfNode[i].y == 3.0f || m_vecPosOfNode[i].y == 4.0f)
		{
			m_PathGraph->GetNode(i)->SetActive(true);
		}
	}
	for (int i = 0; i < m_vecPosOfNode.size(); i++)
	{
		int x = i % col;	// 열 번호
		int z = i / col;	// 줄 번호	

		AddEdgeInPathGraph(i, x - 1, z + 0);//해당 엣지를 만들때 높이에따라서 엣지추가여부 연산
		AddEdgeInPathGraph(i, x + 1, z + 0);
		AddEdgeInPathGraph(i, x + 0, z - 1);//엣지는 일단 노드 포지션을 전부 맞춘후
		AddEdgeInPathGraph(i, x + 0, z + 1);
		AddEdgeInPathGraph(i, x - 1, z - 1);
		AddEdgeInPathGraph(i, x - 1, z + 1);
		AddEdgeInPathGraph(i, x + 1, z - 1);
		AddEdgeInPathGraph(i, x + 1, z + 1);
	}
}

void cAstarManager::AddEdge(int from, int col, int row)
{
	if (col >= 0 && col < sqrt(m_vecPosOfNode.size()) && row >= 0 && row < sqrt(m_vecPosOfNode.size()))
	{
		int to = col + row *  sqrt(m_vecPosOfNode.size());
		D3DXVECTOR3 fromPos = m_graph->GetNode(from)->Pos();//get노드로 처리해서 엣지추가여부 결정하기
		D3DXVECTOR3 toPos = m_graph->GetNode(to)->Pos();

		if (abs(fromPos.y - toPos.y) <= 1.0f&&m_graph->GetNode(from)->Active() == true && m_graph->GetNode(to)->Active() == true)
		{
			D3DXVECTOR3 length = toPos - fromPos;

			m_graph->AddEdge(from, to, sqrt(pow(length.x, 2) + pow(length.z, 2)));
		}
	}
}

void cAstarManager::AddEdgeInPathGraph(int from, int col, int row)
{
	if (col >= 0 && col < sqrt(m_vecPosOfNode.size()) && row >= 0 && row < sqrt(m_vecPosOfNode.size()))
	{
		int to = col + row *  sqrt(m_vecPosOfNode.size());
		D3DXVECTOR3 fromPos = m_graph->GetNode(from)->Pos();//get노드로 처리해서 엣지추가여부 결정하기
		D3DXVECTOR3 toPos = m_graph->GetNode(to)->Pos();

		if (abs(fromPos.y - toPos.y) <= 1.0f&&m_graph->GetNode(from)->Active() == true && m_graph->GetNode(to)->Active() == true)
		{
			D3DXVECTOR3 length = toPos - fromPos;

			m_PathGraph->AddEdge(from, to, sqrt(pow(length.x, 2) + pow(length.z, 2)));
		}
	}
}


vector<int> cAstarManager::GetPath(int chrindex, int targetIndex)
{
	if (chrindex != targetIndex)
	{
		/*	cGraph* pGraph = SetupGraph();*/
		cAstar as(m_PathGraph, chrindex, targetIndex);
		if (as.Search())
		{
			return as.GetPath();
		}
		/*SAFE_DELETE(pGraph);*/
	}
	return vector<int>();
}

void cAstarManager::Update()
{
	if (TIME->UpdateOneSecond())
	{
		SetObjectIndex();
		SetTargetOfLeader();
		//cout << "player index : " <<OBJECT->GetPlayer()->GetIndex()<< endl;
	}
}

void cAstarManager::PathUpdate()
{
	SetLeaderPath();
	THREAD->SuspendThreadByKey(HANDLE_ATSTAR_FINDPATH);
}

void cAstarManager::Release()
{
	THREAD->TerminateThreadByKey(HANDLE_ASTAR_FINDINDEX);
	THREAD->TerminateThreadByKey(HANDLE_ATSTAR_FINDPATH);
	m_isMapLoadingComplete = false;
	if (m_PathGraph)SAFE_DELETE(m_PathGraph);
	m_PathGraph = NULL;
	if (m_graph)SAFE_DELETE(m_graph);
	m_graph = NULL;
	m_vecPosOfNode.clear();
}

void cAstarManager::Render()
{
	if (m_graph)m_graph->Render();
}

bool cAstarManager::GetCursorIndex(int & TargetIndex)
{
	if (m_graph)
	{
		int cellIndex = -1;	// 메쉬 충돌 없으면 인덱스는 -1. 아니라면 해당 인덱스 나올 것임.

		D3DXVECTOR3 posOnMap = D3DXVECTOR3(-1000, -1000, -1000);	//	쓰레기값 넣어두기. 맵 범위 내 찍지 않았으면 이 쓰레기값 그대로 나옴.

		float minX = MAP->GetMinX();	// IsCollidedWithMesh의 예외처리를 위한 변수
		float maxX = MAP->GetMaxX();	// IsCollidedWithMesh의 예외처리를 위한 변수

		cRay::IsCollidedWithMesh(INPUT->GetMousePosVector2(), MAP->GetMesh(), cellIndex, posOnMap, minX, maxX);
		//cout << "posOnMap.x : " << posOnMap.x << "posOnMap.z : " << posOnMap.z<< endl;
		if (cellIndex != -1 && m_graph->GetNode(cellIndex)->Active() != false) { cout << "Active !! cellindex : " << cellIndex << endl; TargetIndex = cellIndex; return true; }
		else { cout << "Non-Active !!" << endl; return false; }

	}
	return false;
}

void cAstarManager::SetObjectIndex()
{
	for (int i = 0; i < OBJECT->GetLeader().size(); i++)
	{
		D3DXVECTOR3 pos = OBJECT->GetLeader()[i]->GetCharacterEntity()->Pos();
		int index = 0;
		MAP->GetMap()->GetIndex(pos.x, pos.z, index);
		if (OBJECT->GetLeader()[i]->GetIndex() != index)OBJECT->GetLeader()[i]->SetIndex(index);
	}
	D3DXVECTOR3 pos = OBJECT->GetPlayer()->GetCharacterEntity()->Pos();
	int index = 0;
	MAP->GetMap()->GetIndex(pos.x, pos.z, index);
	if (OBJECT->GetPlayer()->GetIndex() != index)OBJECT->GetPlayer()->SetIndex(index);
}

void cAstarManager::SetLeaderPath()
{
	for (int i = 0; i < OBJECT->GetLeader().size(); i++)
	{
		if (OBJECT->GetLeader()[i]->GetPath().size() <= 0 && OBJECT->GetLeader()[i]->GetIndex() != OBJECT->GetLeader()[i]->GetTargetIndex())
		{
			OBJECT->GetLeader()[i]->PathClear();
			OBJECT->GetLeader()[i]->SetPath(this->GetPath(OBJECT->GetLeader()[i]->GetIndex(), OBJECT->GetLeader()[i]->GetTargetIndex()));
		//	cout << "path size : " << OBJECT->GetLeader()[i]->GetPath().size() << endl;
		}
	}
}

void cAstarManager::SetLeaderPath(cLeader* pLeader)
{


}

//...ㅋㅋㅋㅋㅋㅋㅋ
void cAstarManager::SetTargetOfLeader()
{
	for (int thisLeader = 0; thisLeader < OBJECT->GetLeader().size(); thisLeader++)
	{
		if (OBJECT->GetLeader()[thisLeader]->IsDeath() == false)
		{
			for (int anotherLeader = 0; anotherLeader < OBJECT->GetLeader().size(); anotherLeader++)
			{
				if (OBJECT->GetLeader()[anotherLeader]->IsDeath() == false)
				{
					if (OBJECT->GetLeader()[thisLeader]->GetCamp() != OBJECT->GetLeader()[anotherLeader]->GetCamp())
					{
						if (MATH->IsCollided(OBJECT->GetLeader()[thisLeader]->GetArrangeSphere(), OBJECT->GetLeader()[anotherLeader]->GetArrangeSphere()))
						{
							if (OBJECT->GetLeader()[thisLeader]->GetTargetObject() != OBJECT->GetLeader()[anotherLeader])
							{
								OBJECT->GetLeader()[thisLeader]->SetTargetObject(OBJECT->GetLeader()[anotherLeader]);
								break;
							}
						}

					}
				}
			}
		}
	}
}
