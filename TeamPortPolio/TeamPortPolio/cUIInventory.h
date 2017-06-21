#pragma once
#include "cUIObject.h"
class cUIInventory :
	public cUIObject
{
	// >> 바디
	ST_SIZEN							m_stBodySize;
	D3DXVECTOR3							m_vPos_Body;
	LPDIRECT3DTEXTURE9					m_pTexture_Body;
	// <<

	// >> 슬롯
	vector<ST_SLOT>						m_vecSlotInfo;
	vector<ST_SLOTDATA*>				m_vecShownData;
	// << 

	// >>  끄는 버튼					버튼 수정해야 함
	D3DXVECTOR3					m_vBtnPos;
	cUIButton*					m_pBtn_Exit;
	// <<
public:
	cUIInventory();
	~cUIInventory();

	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	void Setup_Tap(string sPath_body, D3DXVECTOR3 pos_body);
	void Setup_Slot(D3DXVECTOR3 rectPos, ST_SIZEN rectSize,	D3DXVECTOR3 imagePos, ST_SIZEN imageSize);
	void ResetItems(vector<int> vecEquipment);
	HRESULT GetClickedItemID(OUT int& eventID, OUT int& itemID);
	void Setup_exitbtn(D3DXVECTOR3 btnPos, string sPath_idle, string sPath_mouseover, string sPath_clicked);
};

