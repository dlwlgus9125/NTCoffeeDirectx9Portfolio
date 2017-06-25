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
	m_vecSkin.clear();
	m_vecST.clear();
	// >> : Font
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

	m_vecSkin.resize(m_vecNpc.size());
	LoadSkinnedMesh();
	SetupFont();
	SetMtrl();
}

void cNpcManager::Render()
{

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
		switch (m_vecNpc[i].nSID)
		{
		case N_C_HUMAN_WEAPON:
			m_vecSkin[i]->SetPosition(m_vecNpc[i].pos, D3DXVECTOR3(0, 0, -1));
			break;
		case N_C_HUMAN_ARMOR:
			m_vecSkin[i]->SetPosition(m_vecNpc[i].pos, D3DXVECTOR3(0, 0, -1));
			break;
		case N_C_HUMAN_STUFF:
			m_vecSkin[i]->SetPosition(m_vecNpc[i].pos, D3DXVECTOR3(0.548698f, 0, 0.836021f));
			break;
		case N_C_HUMAN_INN:
			m_vecSkin[i]->SetPosition(m_vecNpc[i].pos, D3DXVECTOR3(0, 0, 1));
			break;
		case N_C_HUMAN_RECRUIT:
			m_vecSkin[i]->SetPosition(m_vecNpc[i].pos, D3DXVECTOR3(0, 0, -1));
			break;
		case N_C_ORC_WEAPON:
			m_vecSkin[i]->SetPosition(m_vecNpc[i].pos, D3DXVECTOR3(-0.746783f, 0, -0.665067f));
			break;
		case N_C_ORC_ARMOR:
			m_vecSkin[i]->SetPosition(m_vecNpc[i].pos, D3DXVECTOR3(0, 0, -1));;
			break;
		case N_C_ORC_STUFF:
			m_vecSkin[i]->SetPosition(m_vecNpc[i].pos, D3DXVECTOR3(0, 0, -1));
			break;
		case N_C_ORC_INN:
			m_vecSkin[i]->SetPosition(m_vecNpc[i].pos, D3DXVECTOR3(-1, 0, 0.5));
			break;
		case N_C_ORC_RECRUIT:
			m_vecSkin[i]->SetPosition(m_vecNpc[i].pos, D3DXVECTOR3(0, 0, -1));;
			break;
		default:
			::MessageBox(0, 0, 0, 0);
			break;
		}
	}
}

void cNpcManager::Release()
{
	SAFE_RELEASE(m_pMesh);

	for each(auto s in m_vecSkin)
	{
		SAFE_DELETE(s);
	}
	m_vecSkin.clear();
	for each(auto f in m_vecFont)
	{
		f->Release();
		//SAFE_DELETE(f);
	}
	m_vecFont.clear();

}

void cNpcManager::SetMtrl()
{
	ZeroMemory(&m_mtrl, sizeof(D3DMATERIAL9));
	m_mtrl.Diffuse = D3DXCOLOR(255, 255, 0.0F, 1.0F);
	m_mtrl.Specular = D3DXCOLOR(0.0F, 0.0F, 0.0F, 1.0F);
	m_mtrl.Ambient = D3DXCOLOR(255, 255, 0.0F, 1.0F);
	m_mtrl.Emissive = D3DXCOLOR(0.0F, 0.0F, 0.0F, 1.0F);
	m_mtrl.Power = 5.0f;
}

void cNpcManager::LoadSkinnedMesh()
{
	for (int i = 0; i < m_vecNpc.size(); i++)
	{
		m_vecSkin[i] = new cSkinnedMesh(TEXTURE->GetCharacterResource(NPCDB->GetMapNpc(m_vecNpc[i].nSID)->m_szPath, NPCDB->GetMapNpc(m_vecNpc[i].nSID)->m_szFileName));
	}
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
	m_lf.lfWeight = 800;
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
		case N_C_HUMAN_WEAPON:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Claude", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case N_C_HUMAN_ARMOR:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Alex", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case N_C_HUMAN_STUFF:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Aime", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case N_C_HUMAN_INN:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Bella", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case N_C_HUMAN_RECRUIT:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Daniel", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;

		case N_C_ORC_WEAPON:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Adken", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case N_C_ORC_ARMOR:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Braddock", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case N_C_ORC_STUFF:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Ackerman", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case N_C_ORC_INN:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Oakden", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
			break;
		case N_C_ORC_RECRUIT:
			D3DXCreateText(D3DDevice, m_vechdc[i],
				"Daron", 0.001f, 0.01f, &m_vecFont[i], 0, 0);
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
		if (m_vecNpc[i].nSID > 127)
		{
			D3DXMatrixTranslation(&matT, m_vecNpc[i].pos.x, m_vecNpc[i].pos.y + 1.3f, m_vecNpc[i].pos.z);
		}
		else
		{
			D3DXMatrixTranslation(&matT, m_vecNpc[i].pos.x, m_vecNpc[i].pos.y + 1.1f, m_vecNpc[i].pos.z);
		}
		D3DXMatrixRotationY(&matR, rotY);
		matWorld = matS* matR* matT;
		D3DDevice->SetTexture(0, NULL);
		D3DDevice->SetMaterial(&m_mtrl);
		D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		m_vecFont[i]->DrawSubset(0);
	}
}

vector<ST_SPHERE>& cNpcManager::GetSphere()
{
	return m_vecSphere;
}
