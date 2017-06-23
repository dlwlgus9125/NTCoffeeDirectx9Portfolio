#include "stdafx.h"
#include "cObjLoader.h"
#include "cMtlTex.h"	
#include "cConstruct.h"

cObjLoader::cObjLoader()
{
	m_stWeather = ST_WEATHER();
	m_stShadow = ST_SHADOW();
}

cObjLoader::~cObjLoader()
{
}

void cObjLoader::LoadMtlLib(char* szFolder, char* szFile)
{
	string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE *fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	string sMtlName;
	int nCnt = 0;

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
			continue;

		if (szTemp[0] == 'n')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = string(szMtlName);
			if (m_mapMtlTex.find(sMtlName) == m_mapMtlTex.end())
			{
				m_mapMtlTex[sMtlName] = new cMtlTex;
				m_mapMtlTex[sMtlName]->SetAttrID(nCnt);
				nCnt++;
			}
		}
		else if (szTemp[0] == 'K')
		{
			if (szTemp[1] == 'a')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.r = r * 0.4;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.g = g * 0.4;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.b = b * 0.4;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.a = 1.0f;
			}
			else if (szTemp[1] == 'd')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.a = 1.0f;
			}
			else if (szTemp[1] == 's')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.a = 1.0f;
			}
		}
		else if (szTemp[0] == 'd')
		{
			float d;
			sscanf_s(szTemp, "%*s %f", &d);
			m_mapMtlTex[sMtlName]->GetMaterial().Power = d;
		}
		else if (szTemp[0] == 'm')
		{
			char szTexFile[1024];
			sscanf_s(szTemp, "%*s %s", szTexFile, 1024);
			sFullPath = string(szFolder);
			sFullPath += (string("/") + string(szTexFile));

			LPDIRECT3DTEXTURE9 pTexture = TEXTURE->GetTexture(sFullPath);
			m_mapMtlTex[sMtlName]->SetTexture(pTexture);
		}
	}

	fclose(fp);

}
LPD3DXMESH cObjLoader::LoadMesh(OUT vector<cMtlTex*> &vecMtlTex, IN char* szFolder, IN char* szFile)
{
	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;
	vector<D3DXVECTOR3> vecVN;
	vector<ST_PNT_VERTEX> vecVertex;
	vector<DWORD>		vecAttrBuf;

	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	FILE *fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	string sMtlName;

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
			continue;

		if (szTemp[0] == 'm')
		{
			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024);
			LoadMtlLib(szFolder, szMtlFile);
		}
		else if (szTemp[0] == 'g')
		{
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szTemp[1] == 't')
			{
				float u, v;
				sscanf_s(szTemp, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = string(szMtlName);
		}
		else if (szTemp[0] == 'f')
		{
			int nIndex[3][3];
			sscanf_s(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
				&nIndex[1][0], &nIndex[1][1], &nIndex[1][2],
				&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]
			);

			for (int i = 0; i < 3; i++)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[nIndex[i][0] - 1];
				v.t = vecVT[nIndex[i][1] - 1];
				v.n = vecVN[nIndex[i][2] - 1];
				vecVertex.push_back(v);
			}

			vecAttrBuf.push_back(m_mapMtlTex[sMtlName]->GetAttrID());
		}
	}

	fclose(fp);

	vecMtlTex.resize(m_mapMtlTex.size());
	for each(auto it in m_mapMtlTex)
	{
		vecMtlTex[it.second->GetAttrID()] = it.second;
	}

	LPD3DXMESH pMesh = NULL;
	D3DXCreateMeshFVF(vecAttrBuf.size(), vecVertex.size(), D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF, D3DDevice, &pMesh);

	ST_PNT_VERTEX*	pV = NULL;

	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	WORD*	pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (int i = 0; i < vecVertex.size(); i++)
	{
		pI[i] = i;
	}
	pMesh->UnlockIndexBuffer();

	DWORD*	pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttrBuf[0], vecAttrBuf.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	vector<DWORD>	vecAdj(vecVertex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);

	pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0], 0, 0, 0);

	m_mapMtlTex.clear();

	return pMesh;
}

LPD3DXMESH cObjLoader::LoadMesh(OUT vector<cMtlTex*> &vecMtlTex, IN char* szFolder, IN char* szFile, bool newon)
{
	ST_PNT_VERTEX		vertex = ST_PNT_VERTEX();
	vector<DWORD>		vecAttrBuf;
	vector<ST_PNT_VERTEX> vecVertex;
	vector<DWORD> vecIndex;

	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	FILE *fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	string sMtlName;

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
			continue;

		if (szTemp[0] == 'm')
		{
			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024);
			LoadMtlLib(szFolder, szMtlFile);
		}
		else if (szTemp[0] == 'g')
		{
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vertex.p = D3DXVECTOR3(x, y, z);
			}
			else if (szTemp[1] == 't')
			{
				float u, v;
				sscanf_s(szTemp, "%*s %f %f %*f", &u, &v);
				vertex.t = D3DXVECTOR2(u, v);
			}
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vertex.n = D3DXVECTOR3(x, y, z);
				vecVertex.push_back(vertex);
			}
		}
		else if (szTemp[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = string(szMtlName);
		}
		else if (szTemp[0] == 'f')
		{
			int nIndex[3];
			sscanf_s(szTemp, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&nIndex[0], &nIndex[1], &nIndex[2]);

			vecIndex.push_back(nIndex[0] - 1);
			vecIndex.push_back(nIndex[1] - 1);
			vecIndex.push_back(nIndex[2] - 1);

			vecAttrBuf.push_back(m_mapMtlTex[sMtlName]->GetAttrID());
		}
	}

	fclose(fp);

	vecMtlTex.resize(m_mapMtlTex.size());
	for each(auto it in m_mapMtlTex)
	{
		vecMtlTex[it.second->GetAttrID()] = it.second;
	}

	LPD3DXMESH pMesh = NULL;
	D3DXCreateMeshFVF(vecIndex.size() / 3, vecVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF, D3DDevice, &pMesh);

	ST_PNT_VERTEX *pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	pMesh->UnlockIndexBuffer();

	DWORD*	pA = NULL;
	pMesh->LockAttributeBuffer(0, (DWORD**)&pA);
	memcpy(pA, &vecAttrBuf[0], vecAttrBuf.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	vector<DWORD>	vecAdj(vecIndex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);

	pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0], 0, 0, 0);

	m_mapMtlTex.clear();

	return pMesh;
}

LPD3DXMESH cObjLoader::LoadMesh_Map(OUT vector<cMtlTex*> &vecMtlTex, OUT vector<ST_PNT_VERTEX> &vecVertex, OUT vector<DWORD>& vecIndex,
								OUT int& cellPerRow, OUT float& cellSpace,
								OUT vector<cConstruct*>& vecConstruct,
								IN char* szFolder, IN char* szFile, bool doOptimizeInplace)
{
	ST_PNT_VERTEX		vertex = ST_PNT_VERTEX();
	vector<DWORD>		vecAttrBuf;
	ST_NPC_INFO npcInfo;
	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	FILE *fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	string sMtlName;

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
			continue;

		if (szTemp[0] == 'm')
		{
			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024);
			LoadMtlLib(szFolder, szMtlFile);
		}
		else if (szTemp[0] == 'g')
		{
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vertex.p = D3DXVECTOR3(x, y, z);
			}
			else if (szTemp[1] == 't')
			{
				float u, v;
				sscanf_s(szTemp, "%*s %f %f %*f", &u, &v);
				vertex.t=D3DXVECTOR2(u, v);
			}
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vertex.n = D3DXVECTOR3(x, y, z);
				vecVertex.push_back(vertex);
			}
		}
		else if (szTemp[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = string(szMtlName);
		}
		else if (szTemp[0] == 'f')
		{
			int nIndex[3];
			sscanf_s(szTemp, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&nIndex[0], &nIndex[1], &nIndex[2]);

			vecIndex.push_back(nIndex[0] - 1);
			vecIndex.push_back(nIndex[1] - 1);
			vecIndex.push_back(nIndex[2] - 1);

			vecAttrBuf.push_back(m_mapMtlTex[sMtlName]->GetAttrID());
		}
		else if (szTemp[0] == 'c')
		{
			if (szTemp[1] == 's')
			{
				sscanf_s(szTemp, "%*s %f", &cellSpace);
			}
			if (szTemp[1] == 'r')
			{
				sscanf_s(szTemp, "%*s %d", &cellPerRow);
			}
		}
		else if (szTemp[0] == 'w')
		{
			if (szTemp[1] == 's')
			{
				int isOn;
				int count;
				float move;
				float speed;
				sscanf_s(szTemp, "%*s %d %d %f %f", &isOn, &count, &move, &speed);
				m_stWeather.SetSnowOn(isOn);
				m_stWeather.SetCount_Snow(count);
				m_stWeather.SetMove_Snow(move);
				m_stWeather.SetSpeed_Snow(speed);
			}
			if (szTemp[1] == 'r')
			{
				int isOn;
				int count;
				float move;
				float speed;
				sscanf_s(szTemp, "%*s %d %d %f %f", &isOn, &count, &move, &speed);
				m_stWeather.SetRainOn(isOn);
				m_stWeather.SetCount_Rain(count);
				m_stWeather.SetMove_Rain(move);
				m_stWeather.SetSpeed_Rain(speed);
			}
			if (szTemp[1] == 'f')
			{
				int isOn;
				int index;
				sscanf_s(szTemp, "%*s %d %d", &isOn, &index);
				m_stWeather.SetFogOn(isOn);
				m_stWeather.SetFogPassIndex(index);
			}
		}
		else if (szTemp[0] == 'e')
		{
			if (szTemp[1] == 's')
			{
				int isOn;
				float diffuseAlpha;
				sscanf_s(szTemp, "%*s %d %f", &isOn, &diffuseAlpha);
				m_stShadow.SetShadowOn(isOn);
				m_stShadow.SetShadowDiffuseAlpha(diffuseAlpha);
			}
		}
		else if (szTemp[0] == 'o')
		{
			int nSID = -1;
			D3DXVECTOR3 vPos = D3DXVECTOR3(0,0,0);
			D3DXVECTOR3 vScale = D3DXVECTOR3(0, 0, 0);
			float fRotX = 0.0f;
			float fRotY = 0.0f;
			float fRotZ = 0.0f;

			sscanf_s(szTemp, "%*s %d %f %f %f %f %f %f %f %f %f",
				&nSID,
				&vPos.x, &vPos.y, &vPos.z,
				&vScale.x, &vScale.y, &vScale.z,
				&fRotX, &fRotY, &fRotZ);

			cConstruct* pConstruct = new cConstruct;
			pConstruct->SetScale(vScale);
			pConstruct->SetRotationX(fRotX);
			pConstruct->SetRotationY(fRotY);
			pConstruct->SetRotationZ(fRotZ);
			pConstruct->SetPosition(vPos);
			bool createMesh = true;

			for (int i = 0; i < vecConstruct.size(); i++)
			{
				if (vecConstruct[i]->GetSObjID() == nSID)
				{
					pConstruct->SetObjMesh(vecConstruct[i]->GetObjMesh());
					pConstruct->SetVecObjMtlTex(vecConstruct[i]->GetVecObjMtlTex());
					pConstruct->SetSObjID(nSID);
					createMesh = false;
					
					pConstruct->Update();
				}
			}
			if (createMesh == true)		pConstruct->Create(nSID);

			pConstruct->SetVecVertex(vecVertex);
			vecConstruct.push_back(pConstruct);
		}
		else if (szTemp[0] == 'p')
		{
			int nSID = -1;
			D3DXVECTOR3 vPos = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 vScale = D3DXVECTOR3(0, 0, 0);
			float fRotX = 0.0f;
			float fRotY = 0.0f;
			float fRotZ = 0.0f;

			sscanf_s(szTemp, "%*s %d %f %f %f %f %f %f %f %f %f",
				&nSID,
				&vPos.x, &vPos.y, &vPos.z,
				&vScale.x, &vScale.y, &vScale.z,
				&fRotX, &fRotY, &fRotZ);

			npcInfo = ST_NPC_INFO(nSID, vPos, vScale, fRotX, fRotY, fRotZ);
			m_vecStNPC.push_back(npcInfo);
		}
	}

	fclose(fp);

	vecMtlTex.resize(m_mapMtlTex.size());
	for each(auto it in m_mapMtlTex)
	{
		vecMtlTex[it.second->GetAttrID()] = it.second;
	}
	



	LPD3DXMESH pMesh = NULL;
	D3DXCreateMeshFVF(vecIndex.size() / 3, vecVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF, D3DDevice, &pMesh);

	ST_PNT_VERTEX *pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();
	
	DWORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	pMesh->UnlockIndexBuffer();
	
	DWORD*	pA = NULL;
	pMesh->LockAttributeBuffer(0, (DWORD**)&pA);
	memcpy(pA, &vecAttrBuf[0], vecAttrBuf.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();
	
	vector<DWORD>	vecAdj(vecIndex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);

	if(doOptimizeInplace) pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0], 0, 0, 0);

	m_mapMtlTex.clear();

	return pMesh;
}

ST_WEATHER& cObjLoader::GetWeatherInfo()
{
	return m_stWeather;
}

ST_SHADOW& cObjLoader::GetShadowInfo()
{
	return m_stShadow;
}

vector<ST_NPC_INFO>& cObjLoader::GetNPCInfo()
{
	return m_vecStNPC;
}