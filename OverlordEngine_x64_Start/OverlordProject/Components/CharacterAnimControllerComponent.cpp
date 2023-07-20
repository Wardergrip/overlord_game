#include "stdafx.h"
#include "CharacterAnimControllerComponent.h"

#include "Components/CharacterComponent.h"
#include "Components/ModelComponent.h"

CharacterAnimControllerComponent::CharacterAnimControllerComponent(CharacterComponent* pCharacter, ModelAnimator* pModelAnim)
	:m_pCharacter{pCharacter}
	,m_pModelAnim{pModelAnim}
	,m_LastAnimationClip{-1}
{
}

void CharacterAnimControllerComponent::Initialize(const SceneContext&)
{
}

void CharacterAnimControllerComponent::Update(const SceneContext&)
{
	const auto& vel = m_pCharacter->GetTotalVelocity();
	if (std::abs(vel.y) > 0.15f)
	{
		SetAnimationClip(1);
		//std::cout << vel.y << '\n';
	}
	else if (std::abs(vel.x) > FLT_EPSILON || std::abs(vel.z) > FLT_EPSILON)
	{
		SetAnimationClip(2);
	}
	else
	{
		SetAnimationClip(0);
	}
}

void CharacterAnimControllerComponent::SetAnimationClip(int id)
{
	if (id == m_LastAnimationClip) return;
	m_LastAnimationClip = id;
	m_pModelAnim->SetAnimation(id);
	m_pModelAnim->Play();
}
