#include "stdafx.h"
#include "cNpcManager.h"
#include "cSkinnedMesh.h"
#include "cCharacter.h"
#include "cPlayer.h"

cNpcManager::cNpcManager()
{
	m_vecSphere = {};
}


cNpcManager::~cNpcManager()
{
}

void cNpcManager::FirstInit()
{
	m_vecSphere.clear();
	m_vecNpc.clear();
	m_pMesh = NULL;
	m_mtrl = D3DMATERIAL9();
	m_vecSkin.clear();
	m_vecST.clear();
	// >> : Font
	m_lf = LOGFONT();
	m_vechdc.clear();
	m_vechFont.clear();
	m_vechFontOld.clear();
	m_vecFont.clear();
}

void cNpcManager::Init(std::vector<ST_NPC_INFO> vecNpc)
{
	m_vecNpc = vecNpc;
	m_vecSphere.resize(m_vecNpc.size());
	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		m_vecSphere[i].fRadius = 0.7f;
		m_vecSphere[i].vCenter = m_vecNpc[i].pos;
		m_vecSphere[i].isPicked = false;
	}
	D3DXCreateSphere(D3DDevice, 0.7f, 10, 10, &m_pMesh, NULL);
	SetMtrl();

	m_vecSkin.resize(m_vecNpc.size());
	LoadSkinnedMesh();
	SetupFont();
}

void cNpcManager::Render()
{
	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, m_vecSphere[i].vCenter.x, m_vecSphere[i].vCenter.y + 0.7f, m_vecSphere[i].vCenter.z);
		D3DDevice->SetTransform(D3DTS_WORLD, &matT);
		D3DDevice->SetTexture(0, NULL);
		D3DDevice->SetFVF(ST_PN_VERTEX::FVF);
		D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		if (i == 0 || i == 1 || i == 3 || i == 4)
		{
			m_mtrl.Ambient = D3DXCOLOR(1.0F, 0.0F, 0.0F, 1.0F);
			D3DDevice->SetMaterial(&m_mtrl);
		}
		else
		{
			m_mtrl.Ambient = D3DXCOLOR(0.0F, 1.0F, 0.0F, 1.0F);
			D3DDevice->SetMaterial(&m_mtrl);
		}
		//m_pMesh->DrawSubset(0);
	}

	for (int i = 0; i < m_vecSkin.size(); i++)
	{
		m_vecSkin[i]->UpdateAndRender(false);
	}

	Render_Text();
}

void cNpcManager::Update(std::vector<ST_NPC_INFO> vecNpc)
{
	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		m_vecSphere[i].vCenter = m_vecNpc[i].pos;
	}

	for (int i = 0; i < m_vecNpc.size(); i++)
	{
		m_vecSkin[i]->SetPosition(m_vecNpc[i].pos, D3DXVECTOR3(0, 0, 1));
	}
}

void cNpcManager::Release()
{
	//if(m_pMesh)SAFE_DELETE(m_pMesh);
	for each(auto s in m_vecSkin)
	{
		SAFE_DELETE(s);
	}
	for each(auto f in m_vecFont)
	{
		SAFE_RELEASE(f);
	}
}

void cNpcManager::SetMtrl()
{
	ZeroMemory(&m_mtrl, sizeof(D3DMATERIAL9));
	m_mtrl.Diffuse = D3DXCOLOR(1.0F, 0.0F, 0.0F, 1.0F);
	m_mtrl.Specular = D3DXCOLOR(1.0F, 0.0F, 0.0F, 1.0F);
}

void cNpcManager::LoadSkinnedMesh()
{
	for (int i = 0; i < m_vecNpc.size(); i++)
	{

		m_vecSkin[i] = new cSkinnedMesh(TEXTURE->GetCharacterResource(NPCDB->GetMapNpc(m_vecNpc[i].nSID)->m_szPath, NPCDB->GetMapNpc(m_vecNpc[i].nSID)->m_szFileName));

	}
	//cSkinnedMesh* pSkinnedMesh = TEXTURE->GetCharacterResource(NPCDB->GetMapNpc(m_vecNpc[0].nSID)->m_szPath, NPCDB->GetMapNpc(m_vecNpc[0].nSID)->m_szFileName);
	//pSkinnedMesh->SetPosition(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 1));   // >> : ¾÷µ¥ÀÌÆ®
	//pSkinnedMesh->UpdateAndRender(false);  // >> : ·»´õ
}

void cNpcManager::SetupFont()
{
	m_vechdc.resize(m_vecNpc.size());

	m_vecFont.resize(m_vecNpc.size());
	m_vechFont.resize(m_vecNpc.size());
	m_vechFontOld.resize(m_vecNpc.size());

	for (int i = 0; i < m_vecNpc.size(); i++)
	{
		m_vechdc[i] = CreateCompatibleDC(0);
	}
	ZeroMemory(&m_lf, sizeof(LOGFONT));
	m_lf.lfHeight = 25;
	m_lf.lfWidth = 12;
	m_lf.lfWeight = FW_NORMAL;
	m_lf.lfItalic = false;
	m_lf.lfUnderline = false;
	m_lf.lfStrikeOut = false;
	m_lf.lfCharSet = HANGEUL_CHARSET;
	_tcscpy(m_lf.lfFaceName, "±¼¸²Ã¼");

	for (int i = 0; i < m_vechFont.size(); i++)
	{
		m_vechFont[i] = CreateFontIndirect(&m_lf);
		m_vechFontOld[i] = (HFONT)SelectObject(m_vechdc[i], m_vechFont[i]);
	}
	//m_hFont = CreateFontIndirect(&m_lf);
	//m_hFontOld = (HFONT)SelectObject(m_hdc, m_hFont);

	SetText();
}

void cNpcManager::SetText()
{

	for (int i = 0; i < m_vechFont.size(); i++)
	{
		switch (m_vecNpc[i].nSID)
		{
		case 117:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"weapon", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 118:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Armor", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 119:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Stuff", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 120:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Inn", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 121:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Recruit", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 122:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Resident1", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 123:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Resident2", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 124:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Resident3", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 125:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Resident4", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;

		case 128:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Weapon", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 129:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Armor", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 130:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Stuff", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 131:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Inn", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 132:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Recruit", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 133:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Resident1", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 134:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Resident2", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case 135:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Resident2", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		default:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Default", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		}
		SelectObject(m_vechdc[i], m_vechFontOld[i]);
	}


}

void cNpcManager::Render_Text()
{
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);

	D3DXVECTOR3 c_pos = CAMERA->GetEye();

	for (int i = 0; i < m_vecFont.size(); i++)
	{
		D3DXVECTOR3 rot = c_pos - m_vecNpc[i].pos;
		D3DXVec3Normalize(&rot, &rot);
		float rotY = MATH->GetRotY(rot);
		D3DXMatrixTranslation(&matT, m_vecNpc[i].pos.x, m_vecNpc[i].pos.y + 1.0f, m_vecNpc[i].pos.z);
		D3DXMatrixRotationY(&matR, rotY);
		matWorld = matS* matR* matT;
		D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		m_vecFont[i]->DrawSubset(0);
	}
}

vector<ST_SPHERE>& cNpcManager::GetSphere()
{
	return m_vecSphere;
}
