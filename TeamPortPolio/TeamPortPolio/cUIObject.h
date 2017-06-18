#pragma once

class cUIObject
{
public:
	cUIObject();
	virtual ~cUIObject();

protected:
	vector<cUIObject*> m_vecChild;
	D3DXMATRIXA16 m_matWorld;
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(cUIObject*, m_pParent, Parent);
	SYNTHESIZE(ST_SIZEN, m_stSize, Size);
	SYNTHESIZE(int, m_nAlpha, Alpha);

	SYNTHESIZE(int, m_nTag, Tag);

	SYNTHESIZE(bool, m_isHidden, Hidden);

	SYNTHESIZE(int, m_eEventID, EventID);

public:
	virtual void Setup(D3DXVECTOR3 pos, int tag);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();
	virtual void AddChild(cUIObject* pChild);
	virtual void SetHiddenAll(bool isHidden);
	virtual D3DXVECTOR2 LeftTop();
	virtual D3DXVECTOR2 LeftVCenter();
	virtual D3DXVECTOR2 RightBottom();
	virtual D3DXVECTOR2 RightVCenter();

};

