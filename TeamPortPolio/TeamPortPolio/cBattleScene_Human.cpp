#include "stdafx.h"
#include "cBattleScene_Human.h"


cBattleScene_Human::cBattleScene_Human()
{
}


cBattleScene_Human::~cBattleScene_Human()
{
}

void cBattleScene_Human::OnEnter()
{

}
void cBattleScene_Human::OnUpdate()
{

}
void cBattleScene_Human::OnExit()
{

}
void cBattleScene_Human::OnRender()
{

}
void cBattleScene_Human::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

void cBattleScene_Human::Setup_DirLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f); 
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3   vDir(1.0f, 1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	D3DDevice->SetLight(0, &stLight);
	D3DDevice->LightEnable(0, true);
}