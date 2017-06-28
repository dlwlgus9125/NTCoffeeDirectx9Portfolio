#pragma once
#include "stdafx.h"
#include "Singleton.h"
#include <cmath>
#include <time.h>

#define MATH				Math::Instance()


class Math : public Singleton<Math>
{
public:
	Math();

	D3DXVECTOR3 Nomalize(D3DXVECTOR3 vec);

	float Magnitude(D3DXVECTOR3 vec);
	float SqrMagnitude(D3DXVECTOR3 vec);
	float Min(float a, float b);
	float Max(float a, float b);
	float Clamp(float num, float min, float max);

	float Distance(D3DXVECTOR3 from, D3DXVECTOR3 to);
	float SqrDistance(D3DXVECTOR3 from, D3DXVECTOR3 to);

	float GetRotX(D3DXVECTOR3 dir);
	float GetRotY(D3DXVECTOR3 dir);
	float GetRotZ(D3DXVECTOR3 dir);
	D3DXVECTOR3 Clamp(D3DXVECTOR3 v, float min, float max);
	bool IsCollided(ST_SPHERE c0, ST_SPHERE c1);
	bool IsCollided(MeshSpere c0, MeshSpere c1);
	bool IsCollided(D3DXVECTOR2 cursorPos, D3DXVECTOR2 leftTop, D3DXVECTOR2 rightBottom);


	// 원과 원의 겹쳐진 벡터 반환
	D3DXVECTOR3 GetOverlappedVector(ST_SPHERE from, ST_SPHERE to);
	D3DXVECTOR3 LocalToWorld(D3DXVECTOR3 local, D3DXVECTOR3 forward);


	//벡터간 각도 계산
	float SinAngle(D3DXVECTOR3 from, D3DXVECTOR3 to);
	float CosAngle(D3DXVECTOR3 from, D3DXVECTOR3 to);
	float Angle(D3DXVECTOR3 from, D3DXVECTOR3 to);
	
	// 정렬
	void BubbleSort(IN OUT vector<int>& vecInven);
};