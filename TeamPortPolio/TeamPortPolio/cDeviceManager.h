#pragma once

#define DEVICE cDeviceManager::Instance() 
#define D3DDevice	cDeviceManager::Instance()->GetDevice()


class cDeviceManager : public Singleton<cDeviceManager>
{
private:

	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;

public:
	LPDIRECT3DDEVICE9	GetDevice();
	void Init();
	void Destroy();
};

