#pragma once
#include "IEntity.h"
#include "BallisticMotion.h"
class cBallisticArrow:public IEntity
{
public:
	cBallisticArrow(D3DXVECTOR3 pos, D3DXVECTOR3 vtarget, float radius, D3DXVECTOR3 forward, float mass, float maxSpeed);
	~cBallisticArrow();
	BallisticMotion* Shoot();
	ST_SPHERE GetSphere() { return Shoot()->m_stSphere; }
private:
	BallisticMotion* m_pArrow;


};
