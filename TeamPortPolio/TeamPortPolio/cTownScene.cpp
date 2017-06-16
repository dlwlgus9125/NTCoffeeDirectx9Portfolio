#include "stdafx.h"
#include "cTownScene.h"
#include "cPlayer.h"


cTownScene::cTownScene()
{
}


cTownScene::~cTownScene()
{
}

void cTownScene::OnEnter()
{
	D3DXCreateSprite(D3DDevice, &m_pSprite);
	MAP->Init("TESTTOWN.txt");
	UI->Change(SCENE_TOWN);
	Setup_DirLight();

	cPlayer* pPlayer = new cPlayer(D3DXVECTOR3(-8, 0, 30), 1.0f, D3DXVECTOR3(0, 0, 1), 0.5f, 5000);
	pPlayer->Init();
	OBJECT->AddCharacter(pPlayer);
	OBJECT->AddObject(pPlayer);
	OBJECT->SetPlayer(pPlayer);

	EFFECT->Init(false, 0, true, true);

	// >> 테스트용 
	m_pMeshSphere = NULL;
	D3DXCreateSphere(D3DDevice, 1, 10, 10, &m_pMeshSphere, NULL);
	{
		D3DMATERIAL9 m_stMtlNone;
		ZeroMemory(&m_stMtlNone, sizeof(D3DMATERIAL9));
		m_stMtlNone.Ambient = D3DXCOLOR(0.0F, 0.7F, 0.0F, 1.0F);
		m_stMtlNone.Diffuse = D3DXCOLOR(0.0F, 0.7F, 0.0F, 1.0F);
		m_stMtlNone.Specular = D3DXCOLOR(0.0F, 0.7F, 0.0F, 1.0F);

		D3DMATERIAL9 m_stMtlPicked;
		ZeroMemory(&m_stMtlPicked, sizeof(D3DMATERIAL9));
		m_stMtlPicked.Ambient = D3DXCOLOR(0.7F, 0.0F, 0.0F, 1.0F);
		m_stMtlPicked.Diffuse = D3DXCOLOR(0.7F, 0.0F, 0.0F, 1.0F);
		m_stMtlPicked.Specular = D3DXCOLOR(0.7F, 0.0F, 0.0F, 1.0F);

		m_vecMtlSphere.push_back(m_stMtlNone);
		m_vecMtlSphere.push_back(m_stMtlPicked);

		ST_SPHERE sphere1 = ST_SPHERE(D3DXVECTOR3(35, 2, 20), 1);
		ST_SPHERE sphere2 = ST_SPHERE(D3DXVECTOR3(35, 2, 15), 1);
		ST_SPHERE sphere3 = ST_SPHERE(D3DXVECTOR3(10, 2, 10), 1);
		m_vecST_Sphere.push_back(sphere1);
		m_vecST_Sphere.push_back(sphere2);
		m_vecST_Sphere.push_back(sphere3);
	}
	// << 
}

void cTownScene::OnUpdate()
{
	MAP->Update();
	UI->Update(TIME->DeltaTime());
	OBJECT->Update(TIME->DeltaTime());
	EFFECT->Update();

	// >> 테스트용
	if (INPUT->IsMouseDown(MOUSE_LEFT))
	{
		for (int i = 0; i < m_vecST_Sphere.size(); i++)
		{
			m_vecST_Sphere[i].isPicked = cRay::IsPicked(INPUT->GetMousePosVector2(), &m_vecST_Sphere[i]);
		}
	}

	if (m_vecST_Sphere[0].isPicked)
	{
		UI->SetEvent(0);
	}
	//<< 
}

void cTownScene::OnExit()
{
	SAFE_RELEASE(m_pSprite);
	MAP->Destroy();
	UI->Release();

	SAFE_RELEASE(m_pMeshSphere);
}

void cTownScene::OnRender()
{
	MAP->Render();
	EFFECT->Render();
	UI->Render(m_pSprite);
	OBJECT->Render();

	// >> 테스트용
	D3DXMATRIXA16 matWorld;

	D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	D3DDevice->SetTexture(0, 0);
	D3DXMatrixIdentity(&matWorld);

	for (int i = 0; i < m_vecST_Sphere.size(); i++)
	{
		D3DXMatrixIdentity(&matWorld);
		matWorld._41 = m_vecST_Sphere[i].vCenter.x;
		matWorld._42 = m_vecST_Sphere[i].vCenter.y;
		matWorld._43 = m_vecST_Sphere[i].vCenter.z;

		D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		D3DDevice->SetMaterial(m_vecST_Sphere[i].isPicked ? &m_vecMtlSphere[1] : &m_vecMtlSphere[0]);

		m_pMeshSphere->DrawSubset(0);
	}
	// <<
}

void cTownScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void cTownScene::Setup_DirLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);            // 주변에 영향을 받는 것들은 색을 띄게 만듬
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3   vDir(1.0f, 1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	D3DDevice->SetLight(0, &stLight);
	D3DDevice->LightEnable(0, true);
}
