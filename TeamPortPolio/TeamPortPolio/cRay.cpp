#include "stdafx.h"
#include "cRay.h"



// 화면 클릭 시 ray반환하는 함수
stRay& cRay::CalculatePickingRay(D3DXVECTOR2& cursorPos)
{
	float px = 0.0f;
	float py = 0.0f;

	D3DVIEWPORT9 viewport;
	D3DDevice->GetViewport(&viewport);

	D3DXMATRIX projection;
	D3DDevice->GetTransform(D3DTS_PROJECTION, &projection);

	px = (((2.0f * cursorPos.x) / viewport.Width) - 1.0f) / projection(0, 0);
	py = (((-2.0f * cursorPos.y) / viewport.Height) + 1.0f) / projection(1, 1);

	stRay ray;
	ray.vOrigin = D3DXVECTOR3(0.0F, 0.0F, 0.0F);
	ray.vDirection = D3DXVECTOR3(px, py, 1.0f);
	return ray;
}

// 화면 클릭 시 해당 매쉬와 접촉된 위치 반환해주는 함수
bool cRay::IsCollidedWithMesh(IN D3DXVECTOR2& cursorPos, IN LPD3DXMESH pMesh, OUT D3DXVECTOR3& collidedPos)
{
	stRay ray = CalculatePickingRay(cursorPos);

	// >> 광선 변환
	D3DXMATRIX matView, matViewInverse;
	D3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matViewInverse, 0, &matView);

	D3DXVec3TransformCoord(&ray.vOrigin, &ray.vOrigin, &matViewInverse);
	D3DXVec3TransformNormal(&ray.vDirection, &ray.vDirection, &matViewInverse);
	D3DXVec3Normalize(&ray.vDirection, &ray.vDirection);
	// <<

	BOOL intersect = false;
	DWORD faceIndex = 0;
	float u = 0;
	float v = 0;
	float t = 0;
	for (int i = 0; i < pMesh->GetNumFaces(); i++)
	{
		D3DXIntersect(pMesh, &ray.vOrigin, &ray.vDirection, &intersect, &faceIndex, &u, &v, &t, 0, 0);
		//D3DXIntersectTri()
		if (intersect)	
		{
			collidedPos = ray.vOrigin + ray.vDirection * t;
			break;
		}
		faceIndex++;
	}

	return intersect;
}

// 화면 클릭 시 해당 매쉬와 접촉된 폴리곤 인덱스 반환해주는 함수
bool cRay::IsCollidedWithMesh(IN D3DXVECTOR2& cursorPos, IN LPD3DXMESH pMesh, OUT int& index, OUT D3DXVECTOR3& outPos, IN float& minX, IN float& maxX)
{
	// 맵 밖에 있다면 바로 false;
	if(!IsMounseInMap(cursorPos, minX, maxX)) return false;

	stRay ray = CalculatePickingRay(cursorPos);

	// >> 광선 변환
	D3DXMATRIX matView, matViewInverse;
	D3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matViewInverse, 0, &matView);

	D3DXVec3TransformCoord(&ray.vOrigin, &ray.vOrigin, &matViewInverse);
	D3DXVec3TransformNormal(&ray.vDirection, &ray.vDirection, &matViewInverse);
	D3DXVec3Normalize(&ray.vDirection, &ray.vDirection);
	// <<

	// >> 변수 선언 및 초기화
	BOOL intersect = false;
	DWORD faceIndex = -1;
	float u = 0;
	float v = 0;
	float t = 0;
	// << 

	// >> 매쉬와 충돌 검사
	for (int i = 0; i < pMesh->GetNumFaces(); i++)
	{
		D3DXIntersect(pMesh, &ray.vOrigin, &ray.vDirection, &intersect, &faceIndex, &u, &v, &t, 0, 0);
		
		if (intersect)
		{
			index = faceIndex*0.5f;
			outPos = ray.vOrigin + ray.vDirection * t;
			break;
		}
		faceIndex++;
	}
	// <<

	return intersect;
}

// >> 맵 끝 모서리 네부분을 기준으로 맵 내부에 커서가 있는지 확인해주는 함수
bool cRay::IsMounseInMap(IN D3DXVECTOR2& cursorPos, IN float& minX, IN float& maxX)
{
	stRay ray = CalculatePickingRay(cursorPos);

	// >> 광선 변환
	D3DXMATRIX matView, matViewInverse;
	D3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matViewInverse, 0, &matView);

	D3DXVec3TransformCoord(&ray.vOrigin, &ray.vOrigin, &matViewInverse);
	D3DXVec3TransformNormal(&ray.vDirection, &ray.vDirection, &matViewInverse);
	D3DXVec3Normalize(&ray.vDirection, &ray.vDirection);
	//<<
	
	D3DXVECTOR3 v0 = D3DXVECTOR3(minX * -1, 0, maxX * -1);
	D3DXVECTOR3 v1 = D3DXVECTOR3(minX * -1, 0, maxX * +1);
	D3DXVECTOR3 v2 = D3DXVECTOR3(minX * +1, 0, maxX * +1);
	D3DXVECTOR3 v3 = D3DXVECTOR3(minX * +1, 0, maxX * -1);

	if (!D3DXIntersectTri(&v0, &v1, &v2, &ray.vOrigin, &ray.vDirection, 0, 0, 0) &&
		!D3DXIntersectTri(&v0, &v2, &v3, &ray.vOrigin, &ray.vDirection, 0, 0, 0)) return false;

	//v0 = D3DXVECTOR3(minX * -1, -20, maxX * -1);
	//v1 = D3DXVECTOR3(minX * -1, -20, maxX * +1);
	//v2 = D3DXVECTOR3(minX * +1, -20, maxX * +1);
	//v3 = D3DXVECTOR3(minX * +1, -20, maxX * -1);
	//
	//if (D3DXIntersectTri(&v0, &v1, &v2, &ray.vOrigin, &ray.vDirection, 0, 0, 0) ||
	//	D3DXIntersectTri(&v0, &v2, &v3, &ray.vOrigin, &ray.vDirection, 0, 0, 0)) return false;

	return true;
}

bool cRay::RaySphereIntersect(IN D3DXVECTOR2 & cursorPos, IN MeshSpere sphere, IN float minX, IN float maxX)
{
	stRay ray = CalculatePickingRay(cursorPos);
	if (!IsMounseInMap(cursorPos, minX, maxX)) return false;
	// >> 광선 변환
	D3DXMATRIX matView, matViewInverse;
	D3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matViewInverse, 0, &matView);

	D3DXVec3TransformCoord(&ray.vOrigin, &ray.vOrigin, &matViewInverse);
	D3DXVec3TransformNormal(&ray.vDirection, &ray.vDirection, &matViewInverse);
	D3DXVec3Normalize(&ray.vDirection, &ray.vDirection);

	D3DXVECTOR3 v = ray.vOrigin - sphere.m_vCenter;

	float b = 2.0f * D3DXVec3Dot(&ray.vDirection, &v);
	float c = D3DXVec3Dot(&v, &v) - (sphere.m_radius * sphere.m_radius);

	float discriminant = (b * b) - (4.0f * c);

	if (discriminant < 0.0f)
		return false;

	discriminant = sqrtf(discriminant);

	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;

	if (s0 >= 0.0f || s1 >= 0.0f)
		return true;

	return false;
}

stRay cRay::RayAtViewSpace(int nScreenX, int nScreenY)
{
	D3DVIEWPORT9 vp;
	D3DDevice->GetViewport(&vp);

	D3DXMATRIXA16 matProj;
	D3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	stRay r;
	r.vDirection.x = ((2.0 * nScreenX) / vp.Width - 1.0f) / matProj._11;
	r.vDirection.y = ((-2.0 * nScreenY) / vp.Height + 1.0f) / matProj._22;
	r.vDirection.z = 1.0f;
	return r;
}

stRay cRay::RayAtWorldSpace(int nScreenX, int nScreenY)
{
	stRay r = cRay::RayAtViewSpace(nScreenX, nScreenY);

	D3DXMATRIXA16 matView, matInvView;
	D3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, 0, &matView);

	D3DXVec3TransformCoord(&r.vOrigin, &r.vOrigin, &matInvView);
	D3DXVec3TransformNormal(&r.vDirection, &r.vDirection, &matInvView);
	D3DXVec3Normalize(&r.vDirection, &r.vDirection);

	return r;
}

// 현재 스크린에 클릭된 위치 넣으면 sphere랑 충돌됨을 확인해줌
bool cRay::IsPicked(D3DXVECTOR2 cursorPos, ST_SPHERE* pSphere)
{
	stRay r = RayAtWorldSpace(cursorPos.x, cursorPos.y);

	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixIdentity(&matInvWorld);
	matInvWorld._41 = -pSphere->vCenter.x;
	matInvWorld._42 = -pSphere->vCenter.y;
	matInvWorld._43 = -pSphere->vCenter.z;

	D3DXVec3TransformCoord(&r.vOrigin, &r.vOrigin, &matInvWorld);
	D3DXVec3TransformNormal(&r.vDirection, &r.vDirection, &matInvWorld);

	float vv = D3DXVec3Dot(&r.vDirection, &r.vDirection);
	float qv = D3DXVec3Dot(&r.vOrigin, &r.vDirection);
	float qq = D3DXVec3Dot(&r.vOrigin, &r.vOrigin);
	float rr = pSphere->fRadius * pSphere->fRadius;

	return qv*qv - (qq - rr) >= 0;
}