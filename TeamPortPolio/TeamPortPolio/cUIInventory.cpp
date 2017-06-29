#include "stdafx.h"
#include "cUIInventory.h"


cUIInventory::cUIInventory() : m_pBtn_Exit(NULL)
{
	m_vecShownData.resize(3, 0);
}


cUIInventory::~cUIInventory()
{
}

void cUIInventory::Update(float deltaTime)
{
	if(m_pBtn_Exit) m_pBtn_Exit->SetHidden(m_isHidden);
	if (m_isHidden) return;

	// >> 종료버튼 업데이트 및 클릭 시 hidden되도록
	if (m_pBtn_Exit) m_pBtn_Exit->Update(deltaTime);
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
	if (m_pBtn_Exit)
	{
		pSprite->SetTransform(&m_matWorld);
		pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pBtn_Exit->Render(pSprite);
		pSprite->End();
	}

	// >> 슬롯 이미지	
	for (int i = 0; i < m_vecShownData.size(); i++)
	{
		if (!m_vecShownData[i]) continue;

		pSprite->SetTransform(&m_matWorld);
		pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	
		D3DXIMAGE_INFO imageInfo;
		LPDIRECT3DTEXTURE9 texture = TEXTURE->GetTexture(m_vecShownData[i]->imagePath, imageInfo);
		SetRect(&rc, 0, 0, imageInfo.Width, imageInfo.Height);

		pSprite->Draw(texture, &rc, &D3DXVECTOR3(0, 0, 0), &(m_vecSlotInfo[i].rectPos + m_vecSlotInfo[i].imagePos), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	
		pSprite->End();
	}
	// << 

	cUIObject::Render(pSprite);
}

void cUIInventory::Destroy()
{
	if (m_vecShownData.size() > 0)
	{
		if (m_vecShownData[0] &&
			ITEMDB->GetItem(m_vecShownData[0]->itemID)->eMiddleID == I_M_BOW) m_vecShownData[1] = NULL;

		for each(auto p in  m_vecShownData)
		{
			SAFE_DELETE(p);
		}
		m_vecShownData.clear();
	}

	if(m_pBtn_Exit) m_pBtn_Exit->Destroy();
	cUIObject::Destroy();
}

void cUIInventory::Setup_Tap(string sPath_body, D3DXVECTOR3 pos_body)
{
	D3DXIMAGE_INFO imageInfo;

	m_pTexture_Body = TEXTURE->GetTexture(sPath_body, imageInfo);
	m_vPos_Body = pos_body;
	m_stBodySize = ST_SIZEN(imageInfo.Width, imageInfo.Height);
}

void cUIInventory::Setup_Slot(D3DXVECTOR3 rectPos, ST_SIZEN rectSize, D3DXVECTOR3 imagePos, ST_SIZEN imageSize)
{
	ST_SLOT slot = ST_SLOT(rectPos, rectSize, imagePos, imageSize, D3DXVECTOR3(0,0,0), ST_SIZEN(0,0));
	m_vecSlotInfo.push_back(slot);
}

void cUIInventory::ResetItems(vector<int> vecEquipment)
{
	// >> 기존 장비창 깨끗히!
	for (vector<ST_SLOTDATA*>::iterator	 it = m_vecShownData.begin(); it != m_vecShownData.end(); )
	{
		it = m_vecShownData.erase(it);
	}
	m_vecShownData.resize(3, 0);
	// <<

	// 0 : 오른손, 1 : 왼손, 2 : 몸
	// >> 아이템 착용
	for (int i = 0; i < vecEquipment.size(); i++)
	{
		ST_SLOTDATA* newData = NULL;
		ST_ITEM* currentItem = NULL;
		currentItem = ITEMDB->GetItem(vecEquipment[i]);

		if (!currentItem) continue;			// 아이템DB에서 불러올 것이 없으면 안함

		int itemSID = currentItem->eSmallID;
		int itemMID = currentItem->eMiddleID;
		string name = currentItem->name;
		string imagePath = currentItem->szImagePath;
		newData = new ST_SLOTDATA(itemSID, name, imagePath, "", 0);

		switch (itemMID)
		{
		case I_M_SWORD:
		case I_M_AXE:
			m_vecShownData[0] = newData;
			break;
		case I_M_ARMOR:
			m_vecShownData[2] = newData;
			break;
		case I_M_SHIELD:
			m_vecShownData[1] = newData;
			break;
		case I_M_BOW:
			m_vecShownData[0] = newData;
			m_vecShownData[1] = newData;
			break;
		}
	}
	// <<
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
				if (!m_vecShownData[i]) return false;

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