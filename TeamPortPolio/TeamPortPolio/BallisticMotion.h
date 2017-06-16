#pragma once
class IEntity;
class BallisticMotion
{
public:
	BallisticMotion(IEntity * entity, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vTarget, D3DXVECTOR3 vDir);
	~BallisticMotion();
	void Update_with_targetpos();
	void Update_with_dir();
	IEntity* Entity() { return m_pEntity; }
	ST_SPHERE m_stSphere;
private:
	D3DXVECTOR3 m_vOrigin;
	D3DXVECTOR3 m_vTarget;
	IEntity* m_pEntity;
	float m_fGravity;; // 중력적용을 위한값.
	float GravityMultiPlier(float distance);//중력 곱연산값
};
