#include "stdafx.h"
#include "cHeightMap.h"
#include "cMtlTex.h"
#include "cSkyBox.h"


cHeightMap::cHeightMap() : m_pMesh(NULL)
{
}


cHeightMap::~cHeightMap()

{
	SAFE_RELEASE(m_pMesh);
	for each(auto p in m_vecMtlTex)
	{
		SAFE_DELETE(p);
	}
}

// Load 후에 초기화 해주는 함수
void cHeightMap::Setup(int cellPerRow, float cellSpace, vector<ST_PNT_VERTEX> vecVertex, vector<DWORD> vecIndex)
{
	SetWire(false);

	m_fCellSpace = cellSpace;

	D3DXVECTOR3 startPos = D3DXVECTOR3(cellPerRow * 0.5f * -1, 0.0f, cellPerRow * 0.5f * -1);

	int nNumVertex = pow(cellPerRow + 1, 2);

	int nRow = cellPerRow + 1;
	int nCol = nRow;
	int nTileN = nRow - 1;
	m_nCellPerRow = cellPerRow;

	m_vecVertex = vecVertex;
	m_vecIndex = vecIndex;

	m_nVertPerRow = m_nCellPerRow + 1;
	m_fMinX = (float)m_nCellPerRow * 0.5f * m_fCellSpace * -1;
	m_fMaxX = (float)m_nCellPerRow * 0.5f * m_fCellSpace * +1;
	m_fMinZ = (float)m_nCellPerRow * 0.5f * m_fCellSpace * -1;
	m_fMaxZ = (float)m_nCellPerRow * 0.5f * m_fCellSpace * +1;
}

void cHeightMap::Update()
{

}


bool cHeightMap::GetHeight(IN float x, OUT float&y, IN float z)
{
	// 맵 밖으로 나갔을 경우 중단
	if (x < m_fMinX || z < m_fMinX || x > m_fMaxX || z > m_fMaxZ)
	{
		y = 0;
		return false;
	}

	// 맵 폴리곤의 버텍스는 minx, minz부터 좌측으로 순차적으로 생김
	// cell 갯수 +1 만큼 채워지면 z에 1이 더해짐

	int nX = x;
	int nZ = z;

	float fDeltaX = x - nX;
	float fDeltaZ = z - nZ;

	/*		1 ㅡ 2			높이 계산을 위한 버텍스 계산 순서
			ㅣ / ㅣ			
			0 ㅡ 3
	*/
	
	int nCol = nX + m_nCellPerRow / m_fCellSpace * 0.5f;
	int nRow = nZ + m_nCellPerRow / m_fCellSpace * 0.5f;

	int _0 = (nRow + 1) * m_nVertPerRow + nCol + 0;
	int _1 = (nRow + 0) * m_nVertPerRow + nCol + 0;
	int _2 = (nRow + 0) * m_nVertPerRow + nCol + 1;
	int _3 = (nRow + 1) * m_nVertPerRow + nCol + 1;

	if (_0 > m_vecVertex.size() ||
		_1 > m_vecVertex.size() ||
		_2 > m_vecVertex.size() ||
		_3 > m_vecVertex.size())
	{
		y = 0.0f;
		return false;
	}

	if (fDeltaZ - fDeltaX > 0.0f)
	{
		D3DXVECTOR3   v10 = m_vecVertex[_0].p - m_vecVertex[_1].p;
		D3DXVECTOR3   v12 = m_vecVertex[_2].p - m_vecVertex[_1].p;
		y = m_vecVertex[_1].p.y + (v10 * fDeltaZ + v12 * fDeltaX).y;         // 좌 하단
	}
	else
	{
		fDeltaX = 1.0f - fDeltaX;
		fDeltaZ = 1.0f - fDeltaZ;
		D3DXVECTOR3   v30 = m_vecVertex[_0].p - m_vecVertex[_3].p;
		D3DXVECTOR3   v32 = m_vecVertex[_2].p - m_vecVertex[_3].p;

		y = m_vecVertex[_3].p.y + (v30 * fDeltaX + v32 * fDeltaZ).y;
	}

	return true;
}

bool cHeightMap::GetIndex(IN float x, IN float z, OUT int& index)
{
	// 맵 밖으로 나갔을 경우 중단
	if (x < m_fMinX || z < m_fMinX || x > m_fMaxX || z > m_fMaxZ)
	{
		index = -1;
		return false;
	}

	// 맵 폴리곤의 버텍스는 minx, minz부터 좌측으로 순차적으로 생김
	// cell 갯수 +1 만큼 채워지면 z에 1이 더해짐

	int nX = x;
	int nZ = z;

	float fDeltaX = x - nX;
	float fDeltaZ = z - nZ;

	/*		1 ㅡ 2			높이 계산을 위한 버텍스 계산 순서
	ㅣ / ㅣ
	0 ㅡ 3
	*/

	int nCol = nX + m_nCellPerRow / m_fCellSpace * 0.5f;
	int nRow = nZ + m_nCellPerRow / m_fCellSpace * 0.5f;

	index = nRow * m_nCellPerRow + nCol;
	return true;
}

void cHeightMap::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	if(m_drawWired) D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DDevice->SetMaterial(&(m_vecMtlTex[0]->GetMaterial()));
	D3DDevice->SetTexture(0, m_vecMtlTex[0]->GetTexture());
	m_pMesh->DrawSubset(0);

	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

D3DXVECTOR2 cHeightMap::GetPlayerPos_RateBased(float x, float z)
{
	float fX = (x - m_fMinX) / (m_fMaxX - m_fMinX);
	float fZ = (z - m_fMinZ) / (m_fMaxZ - m_fMinZ);

	return D3DXVECTOR2(fX, fZ);
}