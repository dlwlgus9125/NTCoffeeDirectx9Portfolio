#pragma once
#include "Singleton.h"

class cSkinnedMesh;

#define TEXTURE cTextureManager::Instance() 

class cTextureManager :
	public Singleton<cTextureManager>
{
private:
	map<string, LPDIRECT3DTEXTURE9> m_mapTexture;
	map<string, D3DXIMAGE_INFO> m_mapImageInfo;
	map<string, cSkinnedMesh*> m_mapCharacterResource;
public:
	void                Init();
	LPDIRECT3DTEXTURE9	GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9	GetTexture(string& sFullPath);
	cSkinnedMesh*       GetCharacterResource(char * folder, char* filename);
	cSkinnedMesh*       GetCharacterResource(string& folder, string& filename);
	void                SetTexture(char* szFullPath);
	void                SetTexture(string& sFullPath);
	void                Destroy();

	LPDIRECT3DTEXTURE9	GetTexture(char* szFullPath, D3DXIMAGE_INFO* pImageInfo);
	LPDIRECT3DTEXTURE9	GetTexture(string szFullPath, OUT D3DXIMAGE_INFO& pImageInfo);
};

