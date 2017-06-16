#include "stdafx.h"
#include "cUITab.h"


cUITab::cUITab() : m_pTexture_Body(NULL)
{
}


cUITab::~cUITab()
{
}

void cUITab::Setup_Tap(string sPath_idle_title, string sPath_selected_title, ST_SIZEN titleSize, string sPath_body, D3DXVECTOR3 pos_body, ST_SIZEN bodySize, FONT_TAG eFont)
{
	m_mapTexture_Title[UI_IDLE] = TEXTURE->GetTexture(sPath_idle_title);
	m_mapTexture_Title[UI_SELECTED] = TEXTURE->GetTexture(sPath_selected_title);
	m_stTitleSize = titleSize;

	m_pTexture_Body = TEXTURE->GetTexture(sPath_body);
	m_vPos_Body = pos_body;
	m_stBodySize = bodySize;

	m_eFont_Tab = eFont;
}

void cUITab::AddTitle(string title, D3DXVECTOR3 pos_title)
{
	D3DXVECTOR3 translated_pos_title = m_vPosition + pos_title;
	ST_TAB tab = ST_TAB(title, translated_pos_title, UI_IDLE);
	m_vecTabInfo.push_back(tab);
}

void cUITab::Update(float deltaTime)
{
	if (m_isHidden) return;

	// >> 탭 켜질 때, 첫번째 메뉴가 보이도록
	for (int i = 0; i < m_vecTabInfo.size(); i++)
	{
		if (m_vecTabInfo[i].state == UI_SELECTED) break;
		if (i == m_vecTabInfo.size() - 1) m_vecTabInfo[0].state = UI_SELECTED;
	}
	// << 
	// >> 탭의 타이틀 클릭 시 모든 탭 타이틀의 상태 바꿔주는 부분
	if (INPUT->IsMouseDown(MOUSE_LEFT))
	{
		for (int i = 0; i < m_vecTabInfo.size(); i++)
		{
			D3DXVECTOR2 lt = D3DXVECTOR2(m_vecTabInfo[i].pos.x, m_vecTabInfo[i].pos.y);
			D3DXVECTOR2 rb = D3DXVECTOR2(m_vecTabInfo[i].pos.x + m_stTitleSize.nWidth, m_vecTabInfo[i].pos.y + m_stTitleSize.nHeight);
			if (MATH->IsCollided(INPUT->GetMousePosVector2(), lt, rb))
			{
				for (int k = 0; k < m_vecTabInfo.size(); k++)
				{
					if (k == i) m_vecTabInfo[i].state = UI_SELECTED;
					else m_vecTabInfo[k].state = UI_IDLE;
				}
				break;
			}
		}
	}	
	// <<

	cUIObject::Update(deltaTime);
}

void cUITab::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	RECT rc;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);

	// >> 타이틀 렌더
	for (int i = 0; i < m_vecTabInfo.size(); i++)
	{
		SetRect(&rc, 0, 0, m_stTitleSize.nWidth, m_stTitleSize.nHeight);
		pSprite->Draw(m_mapTexture_Title[m_vecTabInfo[i].state], &rc, &D3DXVECTOR3(0, 0, 0), &m_vecTabInfo[i].pos, D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	}
	// << 

	// >> 바디 렌더
	SetRect(&rc, 0, 0, m_stBodySize.nWidth, m_stBodySize.nHeight);
	pSprite->Draw(m_pTexture_Body, &rc, &D3DXVECTOR3(0, 0, 0), &m_vPos_Body, D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	// << 

	// >> 슬롯 이미지
	for (int i = 0; i < m_vecShownData.size(); i++)
	{
		SetRect(&rc, 0, 0, m_vecSlotInfo[i].imageSize.nWidth, m_vecSlotInfo[i].imageSize.nHeight);
		pSprite->Draw(m_vecShownData[i]->texture, &rc, &D3DXVECTOR3(0, 0, 0), &(m_vecSlotInfo[i].imagePos), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	}
	// << 

	pSprite->End();

	// >> 타이틀 글씨 인쇄
	for (int i = 0; i < m_vecTabInfo.size(); i++)
	{
		LPD3DXFONT pFont = FONT->GetFont(m_eFont_Tab);
		SetRect(&rc, m_vecTabInfo[i].pos.x, m_vecTabInfo[i].pos.y, m_vecTabInfo[i].pos.x + m_stTitleSize.nWidth, m_vecTabInfo[i].pos.y + m_stTitleSize.nHeight);
		pFont->DrawText(NULL, m_vecTabInfo[i].text.c_str(), m_vecTabInfo[i].text.length(), &rc, DT_CENTER | DT_VCENTER,
			m_vecTabInfo[i].state == UI_IDLE ? D3DCOLOR_XRGB(255, 255, 255) : D3DCOLOR_XRGB(255, 255, 0));
	}
	// << 

	// >> 품명, 설명 인쇄
	for (int i = 0; i < m_vecShownData.size(); i++)
	{
		LPD3DXFONT pFont = FONT->GetFont(m_eFont_Slot);
		SetRect(&rc, m_vecSlotInfo[i].textPos.x, m_vecSlotInfo[i].textPos.y,
			m_vecSlotInfo[i].textPos.x + m_vecSlotInfo[i].textSize.nWidth, m_vecSlotInfo[i].textPos.y + m_vecSlotInfo[i].textSize.nHeight);

		string text = m_vecShownData[i]->name + "\n" + m_vecShownData[i]->info;
		pFont->DrawText(NULL, text.c_str(), text.length(), &rc, DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));
	}
	// << 

	cUIObject::Render(pSprite);
}

void cUITab::Destroy()
{
	// >> 탭
	SAFE_RELEASE(m_pTexture_Body);
	for each(auto p in m_mapTexture_Title)
	{
		SAFE_RELEASE(p.second);
	}
	// << 

	// >> 슬롯
	for each(auto p in m_vecSlotData)
	{
		SAFE_DELETE(p);
	}
	// << 

	delete this;
}

void cUITab::Setup_Slot(D3DXVECTOR3 vSlotStartPos, int col, int slotCount, D3DXVECTOR3 rectPos, ST_SIZEN rectSize,
	D3DXVECTOR3 imagePos, ST_SIZEN imageSize, D3DXVECTOR3 textPos, ST_SIZEN textSize, FONT_TAG eFont)
{
	m_vSlotStartPos = vSlotStartPos;

	for (int i = 0; i < slotCount / col; i++)
	{
		for (int k = 0; k < col; k++)
		{
			D3DXVECTOR3 currentRect = vSlotStartPos + D3DXVECTOR3(rectSize.nWidth * k, rectSize.nHeight * i, rectPos.z);
			D3DXVECTOR3 currentImagePos = vSlotStartPos + currentRect + imagePos;
			D3DXVECTOR3 currentTextPos = m_vPosition + vSlotStartPos + currentRect + textPos;
			ST_SLOT slot = ST_SLOT(currentRect, rectSize, currentImagePos, imageSize, currentTextPos, textSize);
			m_vecSlotInfo.push_back(slot);
		}
	}
	m_eFont_Slot = eFont;
}

void cUITab::AddSlotData(int itemID, string name, LPDIRECT3DTEXTURE9 texture, string info)
{
	ST_SLOTDATA* data = new ST_SLOTDATA(itemID, name, texture, info);
	m_vecSlotData.push_back(data);
}

void cUITab::SetShownData(int startIndex)
{
	m_vecShownData.clear();
	for (int i = startIndex; i < m_vecSlotInfo.size(); i++)
	{
		if (startIndex + i >= m_vecSlotData.size()) break;

		m_vecShownData.push_back(m_vecSlotData[i]);
	}
}

// 현재 탭의 아이디와, 선택된 아이템 아이디를 반환하는 함수
void cUITab::GetClickedItemID(OUT int& eventID, OUT int& itemID)
{
	if (m_isHidden) return;

	eventID = -1;
	itemID = -1;

	if (INPUT->IsMouseDown(MOUSE_RIGHT))
	{
		for (int i = 0; i < m_vecShownData.size(); i++)
		{
			if (MATH->IsCollided(INPUT->GetMousePosVector2(), m_vecSlotInfo[i].LeftTop(), m_vecSlotInfo[i].RightBottom()))
			{
				eventID = m_eEventID;
				itemID = m_vecShownData[i]->itemID;
			}
		}
	}
}