#include "stdafx.h"
#include "SoftwareSkinningScene_1.h"
#include "Materials/ColorMaterial.h"
#include "Prefabs/BoneObject.h"

void SoftwareSkinningScene_1::Initialize()
{
	/*
		During the scene initialization we will setup a simple bone hierarchy 
		existing out of two bones.
		1. Create a ColorMaterial that will be used for both BoneObjects
		2. Create a new GameObject which will act as the root for our Bone 
		Hierarchy(pRoot)
		3. Initialize the first bone(m_pBone0), use the premade 
		ColorMaterial and a length of 15.f.This bone is then added to the
		pRoot as a child.
		4. Initialize the second bone(m_pBone1), same parameters as
		m_pBone0.This bone is added as a child to
		m_pBone0 BUT use the AddBone function instead of the
		AddChild function!(The AddBone function will add this bone as a child and
			translate it to the end of the parent bone)
		5. Make sure to add
		pRoot to the scenegraph using AddChild
	*/
	ColorMaterial* pColorMat = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	GameObject* pRoot = new GameObject();
	AddChild(pRoot);
	constexpr float boneLength{ 15.f };
	m_pBone0 = new BoneObject(pColorMat, boneLength);
	pRoot->AddChild(m_pBone0);
	m_pBone1 = new BoneObject(pColorMat, boneLength);
	m_pBone0->AddBone(m_pBone1);

	m_SceneContext.settings.enableOnGUI = true;
}

void SoftwareSkinningScene_1::Update()
{
	/*
		The update function takes care of animating both bones.The datamember
		m_BoneRotation fluctuates between - 45 and 45 degrees at a speed of 
		45 degrees per second.Use m_RotationSign(must be - 1 of 1) to keep 
		track of the update rate (increment or decrement the rotation).
		Both bones are rotated along the Z - Axis.
		m_pBone0 > Rotate(0, 0, m_BoneRotation)
		m_pBone1 > Rotate(0, 0, -m_BoneRotation * 2.f)
	*/

	if (m_ManualOverride == false)
	{
		m_BoneRotation += m_RotSpeed * m_SceneContext.pGameTime->GetElapsed() * m_RotationSign;
		if ((m_BoneRotation > m_UpperBound) || (m_BoneRotation < m_LowerBound))
		{
			m_RotationSign *= -1;
		}
		m_Bone0Rotation.x = 0;
		m_Bone0Rotation.y = 0;
		m_Bone0Rotation.z = m_BoneRotation;

		m_Bone1Rotation.x = 0;
		m_Bone1Rotation.y = 0;
		m_Bone1Rotation.z = -m_BoneRotation * 2.f;
	}

	m_pBone0->GetTransform()->Rotate(m_Bone0Rotation);
	m_pBone1->GetTransform()->Rotate(m_Bone1Rotation);
}

void SoftwareSkinningScene_1::OnGUI()
{
	/*
		Add some ImGui widget so you can manually adjust the rotations of 
		both bones.
		Also add a checkbox to toggle between manual and automatic mode.
		You can of course add some extra datamembers to the class to achieve 
		this behaviour.
	*/

	ImGui::Checkbox("Manual override", &m_ManualOverride);
	if (m_ManualOverride)
	{
		ImGui::SliderFloat3("Bone0 Rot", ConvertUtil::ToImFloatPtr(m_Bone0Rotation), m_LowerBound, m_UpperBound);
		ImGui::SliderFloat3("Bone1 Rot", ConvertUtil::ToImFloatPtr(m_Bone1Rotation), m_LowerBound, m_UpperBound);
	}
}
