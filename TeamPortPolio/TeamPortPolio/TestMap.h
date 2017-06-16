#pragma once

#define TESTMAP TestMap::Instance() 

class cPyramid;

class TestMap:public Singleton<TestMap>
{

private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	std::vector<cPyramid*>		m_vecPyramid;

public:
	void Setup();
	void Render();
	void Set_Light();
	//>>grid
	void gridSetup(int nNumHalfTile = 15, float fInterval = 1.0f);
	void gridRender();
};


class cPyramid
{
public:
	cPyramid();
	~cPyramid();

	/// >> : 3.
private:
	std::vector<ST_PN_VERTEX>	m_vecVertex;	// << : 13 수정 ST_PN_VERTEX
	D3DXMATRIXA16				m_matR;
	D3DMATERIAL9				m_stMtl;	// << : 13.
public:

	void Setup(D3DXCOLOR c, D3DXMATRIXA16& mat);	// << : 13. 수정 인자
	void Render();
	/// << : 


};

