#pragma once
#include <d3dx9tex.h>
#include <d3dx9math.h>

class cCamera;

enum SKYBOX_FACE
{
	SKYBOX_FACE_TOP,
	SKYBOX_FACE_BOTTOM,
	SKYBOX_FACE_LEFT,
	SKYBOX_FACE_RIGHT,
	SKYBOX_FACE_FRONT,
	SKYBOX_FACE_BACK,
};

enum SKYBOX_TYPE
{
	SKYBOX_TYPE_A,
};


class cSkyBox
{
public:
	cSkyBox();
	~cSkyBox();

	// object에 관한 함수

	// 초기화 + render state 설정
	void Setup(float sizeX, float sizeY, float sizeZ, char* szFolder, char* szExtension);
	void Setup_Texture(char* szFolder, char* szExtension);

	// Projection, View, World Matrix에 관한 처리
	void Update(cCamera* pCamera);

	// Render
	void Render();

	// Type을 가지고 와서 태그값 변경
	void SetSkyType(int type);

protected:
	vector<ST_PT_VERTEX>	m_vecVertex;
	vector<DWORD>			m_vecIndex;

	map<SKYBOX_FACE, LPDIRECT3DTEXTURE9>			m_mapCurrentTexture;
	map <int, map<SKYBOX_FACE, LPDIRECT3DTEXTURE9>> m_mapWholeTexture;

};
