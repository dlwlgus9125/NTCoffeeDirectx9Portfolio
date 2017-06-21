#include "stdafx.h"
#include "cConstruct.h"
#include "cObject.h"
#include "cMtlTex.h"
#include "cObjLoader.h"

cConstruct::cConstruct()
	: m_pObjMesh(NULL)
	, m_vScale(0.5f, 0.5f, 0.5f)
	, m_fRotX(0.0f), m_fRotY(0.0f), m_fRotZ(0.0f)
	, m_vPosition(0.0f, 0.0f, 0.0f)
{
}

  
cConstruct::~cConstruct()
{
}

void cConstruct::Setup(char* szFolder, char* szFile, bool isChecked)
{
	cObjLoader	l;
	if (isChecked == true)			m_pObjMesh = l.LoadMesh( m_vecObjMtlTex, szFolder, szFile, true);
	else if (isChecked == false)	m_pObjMesh = l.LoadMesh( m_vecObjMtlTex, szFolder, szFile);
}

void cConstruct::Update()
{

	D3DXMATRIXA16	matS, matR, matT;

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, m_fRotY, m_fRotX, m_fRotZ);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS *matR* matT;

	//for (int i = 0; i < vecVertex.size(); i++)
	//{
	//	D3DXVECTOR3 vOut;
	//	D3DXVec3TransformCoord(&vOut, &vecVertex[i].p, &m_matWorld);
	//	m_vecTranslatedVertex.push_back(vOut);
	//}
	//

	D3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	
		
//for (int i = 1; i < m_vecTranslatedVertex.size(); i++)
//{
//	m_vecLineVertex.push_back(ST_LINE_VERTEX(m_vecTranslatedVertex[i-1], m_vecTranslatedVertex[i]));
//}
//
//
//for (size_t i = 0; i <m_vecTranslatedVertex.size(); i++)
//{
//	if (m_vecTranslatedVertex[i].x < m_vMin.x) m_vMin.x = m_vecTranslatedVertex[i].x;
//	if (m_vecTranslatedVertex[i].x > m_vMax.x) m_vMax.x = m_vecTranslatedVertex[i].x;
//	
//	if (m_vecTranslatedVertex[i].z < m_vMin.z) m_vMin.z = m_vecTranslatedVertex[i].z;
//	if (m_vecTranslatedVertex[i].z > m_vMax.z) m_vMax.z = m_vecTranslatedVertex[i].z;
//}
//m_vMin.y = 0;
//m_vMax.y = 0;
//
//m_stSphere.vCenter = m_vPosition;
//m_stSphere.fRadius = MATH->Distance(m_vMin, m_vMax) / 1.41421f;//·çÆ®2
//
//D3DXCreateSphere(D3DDevice, m_stSphere.fRadius, 10, 10, &m_pMeshSphere, NULL);
//
//ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
//m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
//m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
//m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);



}

void cConstruct::Render()
{
	D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	if (m_nSObjID >= E_S_OBJECTID_H_DW_START && m_nSObjID <= E_S_OBJECTID_H_DW_END ||
		m_nSObjID >= E_S_OBJECTID_P_DW_START && m_nSObjID <= E_S_OBJECTID_P_ETC_END)
	{
		D3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		D3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
		D3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	for (size_t i = 0; i < m_vecObjMtlTex.size(); i++)
	{
		D3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		D3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());
		D3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());

		m_pObjMesh->DrawSubset(i);
	}

	D3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);


	//D3DXMATRIXA16 mat;
	//D3DXMatrixIdentity(&mat);
	//
	//D3DXMatrixTranslation(&mat, m_stSphere.vCenter.x, m_stSphere.vCenter.y, m_stSphere.vCenter.z);
	//
	//D3DDevice->SetTransform(D3DTS_WORLD, &mat);
	//D3DDevice->SetMaterial(&m_stMtlSphere);
	//
	//D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//m_pMeshSphere->DrawSubset(0);
	//D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void cConstruct::Create(int sIndex)
{
	char* folder = OBJECTDB->GetMapObject(sIndex)->szFolder;
	char* file = OBJECTDB->GetMapObject(sIndex)->szFile;

	m_nSObjID = sIndex;

	if (sIndex >= E_S_OBJECTID_P_DW_START && sIndex <= E_S_OBJECTID_P_ETC_END
		|| sIndex >= E_S_OBJECTID_N_H_START && sIndex <= E_S_OBJECTID_N_O_END)
		Setup(folder, file, false);
	else Setup(folder, file, true);

	Update();
}

void cConstruct::Destroy()
{
	SAFE_RELEASE(m_pObjMesh);
	for each(auto p in m_vecObjMtlTex)
	{
		SAFE_RELEASE(p);
	}

	// delete this;
}

void cConstruct::SetTranfromedVector(vector<D3DXVECTOR3> d)
{
	vector<D3DXVECTOR3> a;
	D3DXVECTOR3 vec1;
	D3DXVECTOR3 vec2;



}
