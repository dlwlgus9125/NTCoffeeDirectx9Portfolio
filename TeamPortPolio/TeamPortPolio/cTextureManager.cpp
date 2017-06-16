#include "stdafx.h"
#include "cTextureManager.h"
#include "cSkinnedMesh.h"

void cTextureManager::Init()
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(char * szFullPath)
{
	if (m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFile(D3DDevice, szFullPath,
			&m_mapTexture[szFullPath]);
	}
	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string & sFullPath)
{
	return GetTexture((char*)sFullPath.c_str());

}

cSkinnedMesh* cTextureManager::GetCharacterResource(char * folder, char* filename)
{
	if (m_mapCharacterResource.find(filename) == m_mapCharacterResource.end())
	{
		
		cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh();
		pSkinnedMesh->Load(folder, filename);
		m_mapCharacterResource[filename] = pSkinnedMesh;
	}
	return m_mapCharacterResource[filename];
}

cSkinnedMesh* cTextureManager::GetCharacterResource(string& folder, string& filename)
{
	return GetCharacterResource((char*)folder.c_str(), (char*)filename.c_str());
}

void cTextureManager::SetTexture(char * szFullPath)
{
	if (m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFile(D3DDevice, TEXT("szFullPath"),
			&m_mapTexture[szFullPath]);
	}
}

void cTextureManager::SetTexture(string & sFullPath)
{
	SetTexture((char*)sFullPath.c_str());
}

void cTextureManager::Destroy()
{
}

LPDIRECT3DTEXTURE9	cTextureManager::GetTexture(char* szFullPath, D3DXIMAGE_INFO* pImageInfo)
{
	if (m_mapTexture.find(szFullPath) == m_mapTexture.end() ||
		m_mapImageInfo.find(szFullPath) == m_mapImageInfo.end())
	{
		SAFE_RELEASE(m_mapTexture[szFullPath]);

		D3DXCreateTextureFromFileEx(D3DDevice, szFullPath, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT,
			0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, &m_mapImageInfo[szFullPath], NULL, &m_mapTexture[szFullPath]);
	}

	OUT *pImageInfo = m_mapImageInfo[szFullPath];

	return m_mapTexture[szFullPath];
}