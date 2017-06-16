#pragma once

class IEntity
{
	int m_uniqueId;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_forward;
	D3DXVECTOR3 m_velocity;

	float m_radius;
	float m_mass;
	float m_maxSpeed;
	float m_currentSpeed;

	bool  m_isDeath;
public:
	IEntity(D3DXVECTOR3 pos, float radius=10, D3DXVECTOR3 forward = D3DXVECTOR3(0, 0, 1),
		float mass = 1, float maxSpeed = 1);

	virtual ~IEntity();

	int UniqueID();
	D3DXVECTOR3 Pos();
	D3DXVECTOR3 Forward();
	D3DXVECTOR3 Velocity();
	float Radius();
	float Mass();
	float Speed();
	float MaxSpeed();

	void SetPos(D3DXVECTOR3 pos);
	void AddPos(D3DXVECTOR3 pos);
	void SetForward(D3DXVECTOR3 forward);
	void SetVelocity(D3DXVECTOR3 velocity);
	void AddVelocity(D3DXVECTOR3 velocity);
	void SetRadius(float radius);
	void SetSpeed(float speed);
	void SetDeath(bool death);

	bool IsDeath();
	virtual void Update(float deltaTime) {}
	virtual void Render() {}
};
