#include "stdafx.h"
#include "cUISlot.h"


cUISlot::cUISlot()
{
}


cUISlot::~cUISlot()
{
}

void cUISlot::Update(float deltaTime)
{
	if (m_isHidden) return;

	cUIObject::Update(deltaTime);
}

void cUISlot::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	RECT rc;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);

	// >> 이미지
	for (int i = 0; i < m_vecShownData.size(); i++)
	{
		SetRect(&rc, 0, 0, m_vecSlotInfo[i].imageSize.nWidth, m_vecSlotInfo[i].imageSize.nHeight);
		pSprite->Draw(m_vecShownData[i]->texture, &rc, &D3DXVECTOR3(0, 0, 0), &(m_vecSlotInfo[i].imagePos), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	}
	// << 

	pSprite->End();

	// >> 품명, 설명 인쇄
	for (int i = 0; i < m_vecShownData.size(); i++)
	{
		LPD3DXFONT pFont = FONT->GetFont(m_eFont);
		SetRect(&rc, m_vecSlotInfo[i].textPos.x, m_vecSlotInfo[i].textPos.y, 
			m_vecSlotInfo[i].textPos.x + m_vecSlotInfo[i].textSize.nWidth, m_vecSlotInfo[i].textPos.y + m_vecSlotInfo[i].textSize.nHeight);

		string text = m_vecShownData[i]->name + "\n" + m_vecShownData[i]->info;
		pFont->DrawText(NULL, text.c_str(), text.length(), &rc, DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));
	}
	// << 

	cUIObject::Render(pSprite);
}

void cUISlot::Destroy()
{
	for each(auto p in m_vecSlotData)
	{
		SAFE_DELETE(p);
	}
	cUIObject::Destroy();
}

void cUISlot::Setup_Slot(int col, int slotCount, D3DXVECTOR3 imagePos_first, ST_SIZEN imageSize, D3DXVECTOR3 textPos_first, ST_SIZEN textSize, FONT_TAG eFont)
{
	for (int i = 0; i < slotCount / col; i++)
	{
		for (int k = 0; k < col; k++)
		{
			D3DXVECTOR3 imagePos = D3DXVECTOR3(imagePos_first.x * (k + 1) + imageSize.nWidth * k + textSize.nWidth * k,
				imagePos_first.y * (i + 1) + imageSize.nHeight * i,
				imagePos_first.z);
			D3DXVECTOR3 textPos = D3DXVECTOR3(textPos_first.x * (k + 1) + textSize.nWidth * k, 
				textPos_first.y * (i + 1) + textSize.nHeight * i,
				textPos_first.z);
			ST_SLOT slot = ST_SLOT(imagePos, imageSize, textPos, textSize);
			m_vecSlotInfo.push_back(slot);
		}
	}	
	m_eFont = eFont;
}

void cUISlot::AddSlotData(string name, LPDIRECT3DTEXTURE9 texture, string info)
{
	ST_SLOTDATA* data = new ST_SLOTDATA(name, texture, info);
	m_vecSlotData.push_back(data);
}

void cUISlot::SetShownData(int startIndex)
{
	m_vecShownData.clear();
	for (int i = startIndex; i < m_vecSlotInfo.size(); i++)
	{
		if (startIndex + i >= m_vecSlotData.size()) break;

		m_vecShownData.push_back(m_vecSlotData[i]);
	}
}