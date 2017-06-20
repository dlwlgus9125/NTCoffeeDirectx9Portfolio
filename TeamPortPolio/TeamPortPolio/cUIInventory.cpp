#include "stdafx.h"
#include "cUIInventory.h"


cUIInventory::cUIInventory()
{
	m_vecShownData.resize(5);
}


cUIInventory::~cUIInventory()
{
}

void cUIInventory::Update(float deltaTime)
{
	m_pBtn_Exit->SetHidden(m_isHidden);
	if (m_isHidden) return;

	// >> 종료버튼 업데이트 및 클릭 시 hidden되도록
	m_pBtn_Exit->Update(deltaTime);
	if (m_pBtn_Exit->GetCurrentState() == UI_CLICKED) m_isHidden = true;
	// << 

	cUIObject::Update(deltaTime);
}

void cUIInventory::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	pSprite->SetTransform(&m_matWorld);
	RECT rc;

	// >> 바디 렌더
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	SetRect(&rc, 0, 0, m_stBodySize.nWidth, m_stBodySize.nHeight);
	pSprite->Draw(m_pTexture_Body, &rc, &D3DXVECTOR3(0, 0, 0), &m_vPos_Body, D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	pSprite->End();
	// << 

	// 종료 버튼 렌더
	pSprite->SetTransform(&m_matWorld);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pBtn_Exit->Render(pSprite);
	pSprite->End();

	//// >> 슬롯 이미지	
	//for (int i = 0; i < m_vecShownData.size(); i++)
	//{
	//	pSprite->SetTransform(&m_matWorld);
	//	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	//
	//	// 테스트용
	//	SetRect(&rc, 0, 0, m_vecSlotInfo[i].rectSize.nWidth, m_vecSlotInfo[i].rectSize.nHeight);
	//	pSprite->Draw(TEXTURE->GetTexture("image/rect/darkgray.png"), &rc, &D3DXVECTOR3(0, 0, 0), &(m_vecSlotInfo[i].imagePos), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	//
	//	D3DXIMAGE_INFO imageInfo;
	//	LPDIRECT3DTEXTURE9 texture = TEXTURE->GetTexture(m_vecShownData[i]->imagePath, imageInfo);
	//	SetRect(&rc, 0, 0, imageInfo.Width, imageInfo.Height);
	//
	//	pSprite->Draw(texture, &rc, &D3DXVECTOR3(0, 0, 0), &(m_vecSlotInfo[i].imagePos), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	//
	//	pSprite->End();
	//}
	//// << 
	//
	//// >> 품명, 설명 인쇄
	//for (int i = 0; i < m_vecShownData.size(); i++)
	//{
	//	pSprite->SetTransform(&m_matWorld);
	//	LPD3DXFONT pFont = FONT->GetFont(m_eFont_Slot);
	//	SetRect(&rc, m_vPosition.x + m_vecSlotInfo[i].textPos.x, m_vPosition.y + m_vecSlotInfo[i].textPos.y,
	//		m_vPosition.x + m_vecSlotInfo[i].textPos.x + m_vecSlotInfo[i].textSize.nWidth, m_vPosition.y + m_vecSlotInfo[i].textPos.y + m_vecSlotInfo[i].textSize.nHeight);
	//
	//	string text = m_vecShownData[i]->name;
	//	pFont->DrawText(NULL, text.c_str(), text.length(), &rc, DT_LEFT | DT_VCENTER, D3DCOLOR_XRGB(255, 255, 255));
	//}
	//// << 

	cUIObject::Render(pSprite);
}

void cUIInventory::Destroy()
{
	for (int i = 0; i < m_vecShownData.size(); i++)
	{
		SAFE_DELETE(m_vecShownData[i]);
	}

	m_pBtn_Exit->Destroy();
}

void cUIInventory::Setup_Tap(string sPath_body, D3DXVECTOR3 pos_body)
{
	D3DXIMAGE_INFO imageInfo;

	m_pTexture_Body = TEXTURE->GetTexture(sPath_body, imageInfo);
	m_vPos_Body = pos_body;
	m_stBodySize = ST_SIZEN(imageInfo.Width, imageInfo.Height);
}

void cUIInventory::Setup_Slot(D3DXVECTOR3 rectPos, ST_SIZEN rectSize, D3DXVECTOR3 imagePos, ST_SIZEN imageSize, D3DXVECTOR3 textPos, ST_SIZEN textSize, FONT_TAG eFont)
{
	ST_SLOT slot = ST_SLOT(rectPos, rectSize, imagePos, imageSize, textPos, textSize);
	m_vecSlotInfo.push_back(slot);

	m_eFont_Slot = eFont;
}

void cUIInventory::AddShownData(int itemSID)
{
	ST_ITEM* currentItem = NULL;
	currentItem = ITEMDB->GetItem(itemSID);

	if (!currentItem) return;		// itemDB에서 아이템 못불러오면 종료

	int itemMID = currentItem->eMiddleID;

	// 벡터 인덱스 - 아이템 매칭
	/*
			0 : 머리
			1 : 오른손
			2 : 왼손
			3 : 몸
			4 : 발
	
	*/
	switch (itemMID)
	{
	case I_M_HELM:
	{
		if (m_vecShownData[0]) SAFE_DELETE(m_vecShownData[0]);
		ST_SLOTDATA* newData = new ST_SLOTDATA(currentItem->eSmallID, currentItem->name, currentItem->szImagePath, NULL, NULL);
		m_vecShownData[0] = newData;
	}
		break;
	case I_M_SWORD:
	case I_M_AXE:
	{
		if (m_vecShownData[1]) SAFE_DELETE(m_vecShownData[1]);
		ST_SLOTDATA* newData = new ST_SLOTDATA(currentItem->eSmallID, currentItem->name, currentItem->szImagePath, NULL, NULL);
		m_vecShownData[1] = newData;
	}
		break;
	case I_M_BOW:
	{
		if (m_vecShownData[1]) SAFE_DELETE(m_vecShownData[1]);
		ST_SLOTDATA* newData = new ST_SLOTDATA(currentItem->eSmallID, currentItem->name, currentItem->szImagePath, NULL, NULL);
		m_vecShownData[1] = newData;
		if (m_vecShownData[2]) SAFE_DELETE(m_vecShownData[2]);
		ST_SLOTDATA* newData2 = new ST_SLOTDATA(currentItem->eSmallID, currentItem->name, currentItem->szImagePath, NULL, NULL);
		m_vecShownData[2] = newData2;
	}
		break;
	case I_M_SHIELD:
	{
		if (m_vecShownData[2]) SAFE_DELETE(m_vecShownData[2]);
		ST_SLOTDATA* newData = new ST_SLOTDATA(currentItem->eSmallID, currentItem->name, currentItem->szImagePath, NULL, NULL);
		m_vecShownData[2] = newData;
	}
		break;
	case I_M_ARMOR:
	{
		if (m_vecShownData[3]) SAFE_DELETE(m_vecShownData[3]);
		ST_SLOTDATA* newData = new ST_SLOTDATA(currentItem->eSmallID, currentItem->name, currentItem->szImagePath, NULL, NULL);
		m_vecShownData[3] = newData;
	}
		break;
	case I_M_BOOTS:
	{
		if (m_vecShownData[4]) SAFE_DELETE(m_vecShownData[4]);
		ST_SLOTDATA* newData = new ST_SLOTDATA(currentItem->eSmallID, currentItem->name, currentItem->szImagePath, NULL, NULL);
		m_vecShownData[4] = newData;
	}
		break;
	}
}

void cUIInventory::DeleteShownData(int itemSID)
{
	for (int i = 0; i < m_vecShownData.size(); i++)
	{
		if (m_vecShownData[i]->itemID == itemSID) SAFE_DELETE(m_vecShownData[i]);
	}
}

// 현재 탭의 아이디와, 선택된 아이템 아이디를 반환하는 함수
HRESULT cUIInventory::GetClickedItemID(OUT int& eventID, OUT int& itemID)
{
	if (m_isHidden) return false;

	eventID = -1;
	itemID = -1;

	if (INPUT->IsMouseDown(MOUSE_RIGHT))
	{
		for (int i = 0; i < m_vecShownData.size(); i++)
		{
			D3DXVECTOR2 vPos = D3DXVECTOR2(m_vPosition.x, m_vPosition.y);
			if (MATH->IsCollided(INPUT->GetMousePosVector2(), vPos + m_vecSlotInfo[i].LeftTop(), vPos + m_vecSlotInfo[i].RightBottom()))
			{
				eventID = m_eEventID;
				itemID = m_vecShownData[i]->itemID;
				return true;
			}
		}
	}
	return false;
}

void cUIInventory::Setup_exitbtn(D3DXVECTOR3 btnPos, string sPath_idle, string sPath_mouseover, string sPath_clicked)
{
	m_pBtn_Exit = new cUIButton;
	m_vBtnPos = m_vPosition + btnPos;
	m_pBtn_Exit->Setup(m_vBtnPos, UI_BUTTON);
	m_pBtn_Exit->Setup_Button(sPath_idle, sPath_mouseover, sPath_clicked, TOWN_BTN_SHOPEXIT);
}