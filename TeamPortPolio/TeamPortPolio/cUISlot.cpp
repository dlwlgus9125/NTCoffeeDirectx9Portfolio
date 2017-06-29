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
		D3DXIMAGE_INFO imageInfo;
		LPDIRECT3DTEXTURE9 texture = TEXTURE->GetTexture(m_vecShownData[i]->imagePath, imageInfo);
		SetRect(&rc, 0, 0, imageInfo.Width, imageInfo.Height);
		pSprite->Draw(texture, &rc, &D3DXVECTOR3(0, 0, 0), &(m_vecSlotInfo[i].imagePos), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
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
	m_vecSlotData.clear();

	cUIObject::Destroy();
}

void cUISlot::Setup_Slot(int col, int slotCount, D3DXVECTOR3 rectPos, ST_SIZEN rectSize, 
	D3DXVECTOR3 imagePos, ST_SIZEN imageSize, D3DXVECTOR3 textPos, ST_SIZEN textSize, FONT_TAG eFont)
{
	for (int i = 0; i < slotCount / col; i++)
	{
		for (int k = 0; k < col; k++)
		{
			D3DXVECTOR3 currentRect = D3DXVECTOR3(rectSize.nWidth * k, rectSize.nHeight * i, rectPos.z);
			D3DXVECTOR3 currentImagePos = currentRect + imagePos;
			D3DXVECTOR3 currentTextPos = m_vPosition + currentRect+ textPos;
			ST_SLOT slot = ST_SLOT(currentRect, rectSize, currentImagePos, imageSize, currentTextPos, textSize);
			m_vecSlotInfo.push_back(slot);
		}
	}	
	m_eFont = eFont;
}

void cUISlot::AddSlotData(int itemID, string name, string imagePath, string info, int cost)
{
	D3DXIMAGE_INFO imageinfo;
	LPDIRECT3DTEXTURE9 texture = TEXTURE->GetTexture(imagePath, imageinfo);
	
	ST_SLOTDATA* data = new ST_SLOTDATA(itemID, name, imagePath, info, cost);
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

int cUISlot::GetClickedItemID()
{
	if (m_isHidden) return -1;

	if (INPUT->IsMouseDown(MOUSE_RIGHT))		
	{
		for (int i = 0; i < m_vecShownData.size(); i++)
		{
			if (MATH->IsCollided(INPUT->GetMousePosVector2(), m_vecSlotInfo[i].LeftTop(), m_vecSlotInfo[i].RightBottom()))
			{
				return m_vecShownData[i]->itemID;
			}
		}		
	}
	return -1;
}