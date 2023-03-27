#include "stdafx.h"
#include "BoneObject.h"
//#include ""

BoneObject::BoneObject(BaseMaterial* pMaterial, float length)
	:m_Length{length}
	,m_pMaterial{pMaterial}
{
	// The constructor is simple, initialize the datamembers with the corresponding
	// constructor parameters.
}

void BoneObject::AddBone(BoneObject* pBone)
{
	/*
	* 1. The incoming bone (pBone) must be translated along the X-axis so it is 
	located next to the parent (this) bone. The length of the parent bone is 
	defined by m_Length
	* 2. Add pBone as a child to the parent BoneObject (this). 
	This creates the hierarchical relation between both bone, pBone is now 
	a child and ‘follows’ the transformation of its parent.
	*/
	pBone->GetTransform()->Translate(m_Length,0,0);
	AddChild(pBone);
}

void BoneObject::CalculateBindPose()
{
	const XMMATRIX inverseWorldMatrix{ XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&GetTransform()->GetWorld())) };

	XMStoreFloat4x4(&m_BindPose, inverseWorldMatrix);

	for (BoneObject* pChild : GetChildren<BoneObject>())
	{
		pChild->CalculateBindPose();
	}
}

void BoneObject::Initialize(const SceneContext&)
{
	/*
	* 1. Create an GameObject (pEmpty)
	* 2. Add pEmpty as a child to the BoneObject
	* 3. Add a ModelComponent to pEmpty (pModel), use Bone.ovm (GP2_W6_Resources)
	* 4. Assign the BoneObject’s material (m_pMaterial) to pModel
	* 5. Rotate pEmpty -90 degrees around the Y-axis 
	(This transform will orient the bone along the X-axis)
	* 6. Uniformly scale pEmpty to match the BoneObject’s length (m_Length)
	*/
	GameObject* pEmpty = new GameObject();
	AddChild(pEmpty);
	ModelComponent* pModel = pEmpty->AddComponent(new ModelComponent(L"Meshes/Bone.ovm"));
	pModel->SetMaterial(m_pMaterial->GetMaterialId());
	pEmpty->GetTransform()->Rotate(0, -90, 0);
	pEmpty->GetTransform()->Scale(m_Length);
}