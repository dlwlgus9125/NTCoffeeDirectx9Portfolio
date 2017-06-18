#pragma once
//#include "IEntity.h"
#include "cCharacter.h"
#include "BallisticMotion.h"
class cBallisticArrow:public cCharacter
{

	

public:
	cBallisticArrow(D3DXVECTOR3 pos, D3DXVECTOR3 vtarget, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed);
	~cBallisticArrow();
	BallisticMotion* Shoot();
//ST_SPHERE GetSphere() { return Shoot()->m_stSphere; }
	void Init();
	void Update(float deltaTime);
	void Render();

	void SetCamp(CAMP_STATE camp) { m_Camp = camp; };
	void SetIsPlayer() { m_isPlayer = true; }
private:
	BallisticMotion* m_pArrow;
	CAMP_STATE m_Camp;
	bool       m_isPlayer;
	bool m_isHit;
};
