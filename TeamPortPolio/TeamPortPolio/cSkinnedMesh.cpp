 #include "StdAfx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"


cSkinnedMesh::cSkinnedMesh(cSkinnedMesh* pSkinnedMesh)
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
	, m_vPosition(0, 0, 0)
	, m_vForward(0, 0, 0)
	, m_fBlendTime(0.3f)
	, m_fPassedBlendTime(0.0f)
	, m_isAnimBlend(false)
{
	//cSkinnedMesh* pSkinnedMesh = pSkinnedMesh;

	m_pRootFrame = pSkinnedMesh->m_pRootFrame;
	m_dwWorkingPaletteSize = pSkinnedMesh->m_dwWorkingPaletteSize;
	m_pmWorkingPalette = pSkinnedMesh->m_pmWorkingPalette;
	m_pEffect = pSkinnedMesh->m_pEffect;
	m_stBoundingSphere = pSkinnedMesh->m_stBoundingSphere;

	pSkinnedMesh->m_pAnimController->CloneAnimationController(
		pSkinnedMesh->m_pAnimController->GetMaxNumAnimationOutputs(),
		pSkinnedMesh->m_pAnimController->GetMaxNumAnimationSets(),
		pSkinnedMesh->m_pAnimController->GetMaxNumTracks(),
		pSkinnedMesh->m_pAnimController->GetMaxNumEvents(),
		&m_pAnimController);
	m_currentIndex = 0;
	m_pAnimController->GetAnimationSet(m_currentIndex, &m_currentAnim);
}

cSkinnedMesh::cSkinnedMesh()
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
	, m_fBlendTime(0.3f)
	, m_fPassedBlendTime(0.0f)
	, m_isAnimBlend(false)
{
	m_currentIndex = 0;
}

cSkinnedMesh::~cSkinnedMesh(void)
{
	SAFE_RELEASE(m_pAnimController);
}

void cSkinnedMesh::Load(char* szDirectory, char* szFilename)
{
	m_pEffect = LoadEffect("MultiAnimation.hpp");

	int nPaletteSize = 0;
	m_pEffect->GetInt("MATRIX_PALETTE_SIZE", &nPaletteSize);

	cAllocateHierarchy ah;
	ah.SetDirectory(szDirectory);
	ah.SetDefaultPaletteSize(nPaletteSize);

	m_stBoundingSphere.vCenter = (ah.GetMin() + ah.GetMax()) / 2.0f;
	m_stBoundingSphere.fRadius = D3DXVec3Length(&(ah.GetMin() - ah.GetMax()));

	std::string sFullPath(szDirectory);
	sFullPath += std::string(szFilename);

	D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED,
		D3DDevice,
		&ah,
		NULL,
		(LPD3DXFRAME*)&m_pRootFrame,
		&m_pAnimController);

	if (m_pmWorkingPalette)
		delete[] m_pmWorkingPalette;

	m_dwWorkingPaletteSize = ah.GetMaxPaletteSize();
	m_pmWorkingPalette = new D3DXMATRIX[m_dwWorkingPaletteSize];
	if (m_pmWorkingPalette == NULL)
	{
		m_dwWorkingPaletteSize = 0;
	}

	if (m_pRootFrame)
		SetupBoneMatrixPtrs(m_pRootFrame);

	GetFindHand(m_pRootFrame);
}

void cSkinnedMesh::UpdateAndRender(bool isStop)
{
	m_fPassedTime += TIME->GetElapsedTime();
	if (m_pAnimController)
	{
		if (m_isAnimBlend)
		{
			m_fPassedBlendTime += TIME->GetElapsedTime();
			if (m_fPassedBlendTime >= m_fBlendTime)
			{
				m_isAnimBlend = false;
				m_pAnimController->SetTrackWeight(0, 1.0f);
				m_pAnimController->SetTrackEnable(1, false);
			}
			else
			{
				float fWeight = m_fPassedBlendTime / m_fBlendTime;
				m_pAnimController->SetTrackWeight(0, fWeight);
				m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);

			}
		}
		if (isStop == false)m_pAnimController->AdvanceTime(TIME->GetElapsedTime(), NULL);
		else m_pAnimController->AdvanceTime(0.0f, NULL);
	}

	if (m_pRootFrame)
	{
		D3DXMATRIXA16 mat, matS, matR, matT;
		D3DXMatrixScaling(&matS, 2.0f, 2.0f, 2.0f);
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		D3DXMatrixRotationY(&matR, MATH->GetRotY(m_vForward));
		mat = matS* matR*matT;
		Update(m_pRootFrame, &mat);
		Render(m_pRootFrame);
	}

}

void cSkinnedMesh::UpdateAndRenderForItem(bool isStop, D3DXMATRIXA16& handMat)
{
	
	if (m_pAnimController)
	{
		if (m_isAnimBlend)
		{
			m_fPassedBlendTime += TIME->GetElapsedTime();
			if (m_fPassedBlendTime >= m_fBlendTime)
			{
				m_isAnimBlend = false;
				m_pAnimController->SetTrackWeight(0, 1.0f);
				m_pAnimController->SetTrackEnable(1, false);
			}
			else
			{
				float fWeight = m_fPassedBlendTime / m_fBlendTime;
				m_pAnimController->SetTrackWeight(0, fWeight);
				m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);

			}
		}
		if (isStop == false) { m_pAnimController->AdvanceTime(TIME->GetElapsedTime(), NULL); m_fPassedTime += TIME->GetElapsedTime(); }
		else { m_pAnimController->AdvanceTime(0.0f, NULL); }
	}

	if (m_pRootFrame)
	{
		Update(m_pRootFrame, &handMat);
		Render(m_pRootFrame);
	}
}

void cSkinnedMesh::UpdateAndRenderForArrow(bool isStop)
{
	m_fPassedTime += TIME->GetElapsedTime();
	if (m_pAnimController)
	{
		if (m_isAnimBlend)
		{
			m_fPassedBlendTime += TIME->GetElapsedTime();
			if (m_fPassedBlendTime >= m_fBlendTime)
			{
				m_isAnimBlend = false;
				m_pAnimController->SetTrackWeight(0, 1.0f);
				m_pAnimController->SetTrackEnable(1, false);
			}
			else
			{
				float fWeight = m_fPassedBlendTime / m_fBlendTime;
				m_pAnimController->SetTrackWeight(0, fWeight);
				m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);

			}
		}
		if (isStop == false)m_pAnimController->AdvanceTime(TIME->GetElapsedTime(), NULL);
		else m_pAnimController->AdvanceTime(0.0f, NULL);
	}

	if (m_pRootFrame)
	{
		D3DXMATRIXA16 mat, matS, matR, matRX, matRY, matRZ, matT;
		D3DXMatrixScaling(&matS, 2.0f, 2.0f, 2.0f);
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

		D3DXVECTOR3 dirX = m_vForward;
		D3DXVECTOR3 dirZ = m_vForward + D3DXVECTOR3(0, 0, 1);
		dirX.x *= 10000000;
		D3DXVec3Normalize(&dirX, &dirX);




		//D3DXMatrixRotationX(&matRX, MATH->GetRotX(m_vForward));

		D3DXMatrixRotationY(&matR, MATH->GetRotY(m_vForward));
		//D3DXMatrixRotationZ(&matRZ, MATH->GetRotY(m_vForward));


		//matR = matRX*matRY;
		mat = matS* matR*matT;
		Update(m_pRootFrame, &mat);
		Render(m_pRootFrame);
	}
}

void cSkinnedMesh::Render(ST_BONE* pBone /*= NULL*/)
{
	assert(pBone);

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

		// get bone combinations
		LPD3DXBONECOMBINATION pBoneCombos =
			(LPD3DXBONECOMBINATION)(pBoneMesh->pBufBoneCombos->GetBufferPointer());

		D3DXMATRIXA16 matViewProj, matView, matProj;
		D3DDevice->GetTransform(D3DTS_VIEW, &matView);
		D3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		matViewProj = matView * matProj;

		D3DXMATRIXA16 mView, mInvView;
		D3DDevice->GetTransform(D3DTS_VIEW, &mView);
		D3DXMatrixInverse(&mInvView, 0, &mView);
		D3DXVECTOR3 vEye = D3DXVECTOR3(0, 0, 0);
		D3DXVec3TransformCoord(&vEye, &vEye, &mInvView);

		// for each palette
		for (DWORD dwAttrib = 0; dwAttrib < pBoneMesh->dwNumAttrGroups; ++dwAttrib)
		{
			// set each transform into the palette
			for (DWORD dwPalEntry = 0; dwPalEntry < pBoneMesh->dwNumPaletteEntries; ++dwPalEntry)
			{
				DWORD dwMatrixIndex = pBoneCombos[dwAttrib].BoneId[dwPalEntry];
				if (dwMatrixIndex != UINT_MAX)
				{
					m_pmWorkingPalette[dwPalEntry] =
						pBoneMesh->pBoneOffsetMatrices[dwMatrixIndex] *
						(*pBoneMesh->ppBoneMatrixPtrs[dwMatrixIndex]);
				}
			}

			// set the matrix palette into the effect
			m_pEffect->SetMatrixArray("amPalette",
				m_pmWorkingPalette,
				pBoneMesh->dwNumPaletteEntries);

			m_pEffect->SetMatrix("g_mViewProj", &matViewProj);
			m_pEffect->SetVector("vLightDiffuse", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
			m_pEffect->SetVector("vWorldLightPos", &D3DXVECTOR4(500.0f, 500.0f, 500.0f, 1.0f));
			m_pEffect->SetVector("vWorldCameraPos", &D3DXVECTOR4(vEye, 1.0f));
			m_pEffect->SetVector("vMaterialAmbient", &D3DXVECTOR4(0.53f, 0.53f, 0.53f, 0.53f));
			m_pEffect->SetVector("vMaterialDiffuse", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

			// we're pretty much ignoring the materials we got from the x-file; just set
			// the texture here
			m_pEffect->SetTexture("g_txScene", pBoneMesh->vecTexture[pBoneCombos[dwAttrib].AttribId]);

			// set the current number of bones; this tells the effect which shader to use
			m_pEffect->SetInt("CurNumBones", pBoneMesh->dwMaxNumFaceInfls - 1);

			// set the technique we use to draw
			m_pEffect->SetTechnique("Skinning20");

			UINT uiPasses, uiPass;

			// run through each pass and draw
			m_pEffect->Begin(&uiPasses, 0);
			for (uiPass = 0; uiPass < uiPasses; ++uiPass)
			{
				m_pEffect->BeginPass(uiPass);
				pBoneMesh->pWorkingMesh->DrawSubset(dwAttrib);
				m_pEffect->EndPass();
			}
			m_pEffect->End();
		}

	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if (pBone->pFrameSibling)
	{
		Render((ST_BONE*)pBone->pFrameSibling);
	}

	if (pBone->pFrameFirstChild)
	{
		Render((ST_BONE*)pBone->pFrameFirstChild);
	}
	//SHADOW->CharacterShadow(m_vPosition, pBone->pMeshContainer, m_vForward, uiPasses);
}

LPD3DXEFFECT cSkinnedMesh::LoadEffect(char* szFilename)
{
	LPD3DXEFFECT pEffect = NULL;

	D3DXMACRO mac[2] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ NULL,                          NULL }
	};

	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;
	D3DDevice->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion > D3DVS_VERSION(1, 1))
		pmac = mac;

	DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	ID3DXBuffer* pBuffer = NULL;
	if (FAILED(D3DXCreateEffectFromFile(D3DDevice,
		szFilename,
		pmac,
		NULL,
		dwShaderFlags,
		NULL,
		&pEffect,
		&pBuffer)))
	{
		// if creation fails, and debug information has been returned, output debug info
		if (pBuffer)
		{
			OutputDebugStringA((char*)pBuffer->GetBufferPointer());
			SAFE_RELEASE(pBuffer);
		}

		return NULL;
	}

	return pEffect;
}

void cSkinnedMesh::Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent)
{

	pCurrent->CombinedTransformationMatrix = pCurrent->TransformationMatrix;
	if (pmatParent)
	{
		pCurrent->CombinedTransformationMatrix =
			pCurrent->CombinedTransformationMatrix * (*pmatParent);
	}

	if (pCurrent->pFrameSibling)
	{
		Update((ST_BONE*)pCurrent->pFrameSibling, pmatParent);
	}

	if (pCurrent->pFrameFirstChild)
	{
		Update((ST_BONE*)pCurrent->pFrameFirstChild, &(pCurrent->CombinedTransformationMatrix));
	}
}

void cSkinnedMesh::SetupBoneMatrixPtrs(ST_BONE* pBone)
{
	assert(pBone);

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
			// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
			// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
			// 찾아서 월드매트릭스를 걸어줘라.
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				LPCSTR szBoneName = pSkinInfo->GetBoneName(i);
				if (szBoneName == NULL || strlen(szBoneName) == 0)
					continue;
				ST_BONE* pInfluence = (ST_BONE*)D3DXFrameFind(m_pRootFrame, szBoneName);
				pBoneMesh->ppBoneMatrixPtrs[i] = &(pInfluence->CombinedTransformationMatrix);
			}
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if (pBone->pFrameSibling)
	{
		SetupBoneMatrixPtrs((ST_BONE*)pBone->pFrameSibling);
	}

	if (pBone->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs((ST_BONE*)pBone->pFrameFirstChild);
	}
}

void cSkinnedMesh::SetAnimationIndex(int nIndex)
{
	m_currentIndex = nIndex;
	if (!m_pAnimController)
		return;
	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pAnimSet);
	SAFE_RELEASE(pAnimSet);
}


void cSkinnedMesh::SetAnimationIndexBlend(int nIndex)
{
	int num = m_pAnimController->GetNumAnimationSets();
	if (nIndex > num)nIndex = nIndex%num;

	if (nIndex != m_currentIndex)
	{
		m_isAnimBlend = true;
		m_fPassedBlendTime = 0.0f;

		LPD3DXANIMATIONSET pPrevAnimSet = NULL;
		LPD3DXANIMATIONSET pNextAnimSet = NULL;

		D3DXTRACK_DESC stTrackDesc;
		m_pAnimController->GetTrackDesc(0, &stTrackDesc);

		m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
		m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet);
		m_pAnimController->SetTrackDesc(1, &stTrackDesc);

		m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet);
		m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
		m_pAnimController->SetTrackPosition(0, 0.0f);


		m_pAnimController->SetTrackWeight(0, 0.0f);
		m_pAnimController->SetTrackWeight(1, 1.0f);


		SAFE_RELEASE(pPrevAnimSet);
		SAFE_RELEASE(pNextAnimSet);
		m_fPassedTime = 0.0f;
		m_currentIndex = nIndex;
		m_pAnimController->GetAnimationSet(m_currentIndex, &m_currentAnim);
	}
}


void cSkinnedMesh::Destroy()
{
	cAllocateHierarchy ah;
	D3DXFrameDestroy((LPD3DXFRAME)m_pRootFrame, &ah);

	SAFE_DELETE_ARRAY(m_pmWorkingPalette);
	SAFE_RELEASE(m_pEffect);
}

void cSkinnedMesh::FindAttackBone(char* BoneName)
{
	FindAttackBone(m_pRootFrame, BoneName);
}

void cSkinnedMesh::FindAttackBone(ST_BONE * pBone, char* BoneName)
{
	if (pBone->Name)
	{
		if ((string)pBone->Name == (string)BoneName)
		{
			m_AttackBone = pBone;
		}
	}

	if (pBone->pFrameSibling)
	{
		FindAttackBone((ST_BONE*)pBone->pFrameSibling, BoneName);
	}

	if (pBone->pFrameFirstChild)
	{
		FindAttackBone((ST_BONE*)pBone->pFrameFirstChild, BoneName);
	}
}

void cSkinnedMesh::GetFindHand(ST_BONE* targetBone)
{
	if (targetBone->Name)
	{
		if ("RHand_Bone_Col_root" == (string)targetBone->Name)m_RightHand = targetBone;
		if ("LHand_Bone_Col_root" == (string)targetBone->Name)m_leftHand = targetBone;
	}

	if (targetBone->pFrameSibling)
	{
		GetFindHand((ST_BONE*)targetBone->pFrameSibling);
	}

	if (targetBone->pFrameFirstChild)
	{
		GetFindHand((ST_BONE*)targetBone->pFrameFirstChild);
	}
}

void cSkinnedMesh::SetRandomTrackPosition()
{
	m_pAnimController->SetTrackPosition(0, (rand() % 100) / 10.0f);
}
