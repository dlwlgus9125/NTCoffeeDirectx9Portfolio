#pragma once
#include "cCharacter.h"
#include "BallisticMotion.h"

class cBallisticArrow :public cCharacter
{
public:
	cBallisticArrow(D3DXVECTOR3 pos, D3DXVECTOR3 vtarget, D3DXVECTOR3 forward, float radius = 0.5, float mass = 1, float maxSpeed = 1);
	~cBallisticArrow();
	BallisticMotion* Shoot();
	D3DXMATRIXA16 GetMatrix() { return m_pArrow->GetMatrix(); }
 
	void Init();
	void Render();
	void ArrowUpdate();
private:
	BallisticMotion* m_pArrow;
	
	ST_SPHERE		m_ArrowSphere;
	LPD3DXMESH      m_pMeshSphere;
	D3DMATERIAL9    m_stMtlSphere;

	D3DXVECTOR3 m_vTarget;
	D3DXVECTOR3 m_vDir;

	bool         m_isHit;
};
