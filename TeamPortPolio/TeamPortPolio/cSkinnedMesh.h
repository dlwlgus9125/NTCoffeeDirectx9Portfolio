#pragma once


class cSkinnedMesh
{
	friend class cTextureManager;

private:
	//하나만 생성
	ST_BONE*					m_pRootFrame;
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;
	ST_SPHERE					m_stBoundingSphere;

	// 객체마다 생성
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	D3DXVECTOR3					m_vPosition;
	D3DXVECTOR3					m_vForward;
	int                         m_currentIndex;

	//Blend용
	float                       m_fBlendTime;
	float                       m_fPassedBlendTime;
	float                       m_fPassedTime;
	bool                        m_isAnimBlend;

	//현재 애니메이션 재생시간 확인용
	LPD3DXANIMATIONSET m_currentAnim;

	//충돌체 확인용
	ST_BONE*                    m_AttackBone;
public:
	cSkinnedMesh(cSkinnedMesh* pSkinnedMesh);
	~cSkinnedMesh(void);

	void UpdateAndRender(bool isStop);
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
	int  GetIndex() { return m_currentIndex; }
	void SetRandomTrackPosition(); // 테스트용
	void SetPosition(D3DXVECTOR3 v, D3DXVECTOR3 dir)
	{
		m_vPosition = v;
		m_stBoundingSphere.vCenter = v;
		m_vForward = dir;
	}
	ST_SPHERE* GetBoundingSphere()
	{
		return &m_stBoundingSphere;
	}
	LPD3DXANIMATIONSET GetCurrentAnim() { return m_currentAnim; }
	float GetPassedTime() { return m_fPassedTime; }

	D3DXMATRIXA16  GetAttackBoneMat() { return m_AttackBone->CombinedTransformationMatrix; }
	void      FindAttackBone(char* BoneName);
	void      FindAttackBone(ST_BONE* pBone, char* BoneName);
private:
	cSkinnedMesh();
	void Load(char* szFolder, char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void Destroy();

	
};

