#pragma once
#include "cCharacter.h"




class cUnit :
	public cCharacter
{
protected:
	IEntity* m_pLeader;
	D3DXVECTOR3 m_offset;
	cUnit*   m_TargetEnemy;

	//자신을 겨누고있는 최대 적의 수를 파악
	vector<cUnit*> m_targetedEnemy;
public:
	cUnit();
	virtual ~cUnit();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void SetOffset(D3DXVECTOR3 offset) { m_offset = offset; }
	D3DXVECTOR3 GetOffset() { return D3DXVECTOR3(m_offset.x, 0, m_offset.z); }
	IEntity*    GetLeader() { return m_pLeader; }
	void SetEnemy(cUnit* enemy) { m_TargetEnemy = enemy; }
	cUnit* GetEnemy() { return m_TargetEnemy; }
	int GetTargetedSize() { return m_targetedEnemy.size(); }
	bool AddTargetedEnemy(cUnit* pUnit)
	{
		if (m_targetedEnemy.size() <= 1)
		{
			m_targetedEnemy.push_back(pUnit);
			return true;
		}
		return false;
	}
	void ClearTargetedEnemy() { m_targetedEnemy.clear(); }

	
	virtual void SetAnimBlock(){};
	virtual void SetAnimHit()  {};
	virtual void SetAnimDeath(){};
	virtual void SetStatus() {};

	virtual void SetBattleState() {};
	virtual void SetIdleState() {};
	virtual void SetDefenceState() {};

	
};

