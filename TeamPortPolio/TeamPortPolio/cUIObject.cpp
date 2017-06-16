#include "stdafx.h"
#include "cUIObject.h"


cUIObject::cUIObject() : m_vPosition(0,0,0), m_pParent(NULL), m_stSize(0,0), m_isHidden(true), m_nTag(0), m_nAlpha(255)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cUIObject::~cUIObject()
{
}

void cUIObject::Setup(D3DXVECTOR3 pos, int tag)
{
	m_vPosition = pos;

	m_nTag = tag;

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixTranslation(&m_matWorld, m_vPosition.x, m_vPosition.y, m_vPosition.z);
}

void cUIObject::Update(float deltaTime)
{
	if (m_isHidden) return;

	for each (auto p in m_vecChild)
	{
		p->Update(deltaTime);
	}
}

void cUIObject::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	for each(auto child in m_vecChild)
	{
		child->Render(pSprite);
	}
}

void cUIObject::Destroy()
{
	for each(auto child in m_vecChild)
	{
		child->Destroy();
	}

	delete this;
}

void cUIObject::AddChild(cUIObject* pChild)
{
	m_vecChild.push_back(pChild);
	pChild->SetParent(this);

	pChild->SetPosition(pChild->GetPosition() + m_vPosition);

	pChild->m_matWorld._41 += m_matWorld._41;
	pChild->m_matWorld._42 += m_matWorld._42;
	pChild->m_matWorld._43 += m_matWorld._43;
}

void cUIObject::SetHiddenAll(bool isHidden)
{
	m_isHidden = isHidden;

	for each(auto child in m_vecChild)
	{
		child->SetHidden(isHidden);
	}
}

D3DXVECTOR2 cUIObject::LeftTop()
{
	D3DXVECTOR2 leftTop;
	leftTop.x = m_vPosition.x;
	leftTop.y = m_vPosition.y;

	return leftTop;
}

D3DXVECTOR2 cUIObject::LeftVCenter()
{
	D3DXVECTOR2 leftVCenter;
	leftVCenter.x = m_vPosition.x;
	leftVCenter.y = m_vPosition.y + m_stSize.nHeight * 0.5f;

	return leftVCenter;
}

D3DXVECTOR2 cUIObject::RightBottom()
{
	D3DXVECTOR2 rightBottom;
	rightBottom.x = m_vPosition.x + m_stSize.nWidth;
	rightBottom.y = m_vPosition.y + m_stSize.nHeight;
	return rightBottom;
}

D3DXVECTOR2 cUIObject::RightVCenter()
{
	D3DXVECTOR2 rightVCenter;
	rightVCenter.x = m_vPosition.x + m_stSize.nWidth;
	rightVCenter.y = m_vPosition.y + m_stSize.nHeight * 0.5f;
	return rightVCenter;
}