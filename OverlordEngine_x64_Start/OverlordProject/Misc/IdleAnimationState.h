#pragma once
#include "AnimationState.h"

class IdleAnimationState final : public AnimationState
{

public:
	IdleAnimationState(CharacterAnimControllerComponent* pCharAnimControllerComp)
		:AnimationState(pCharAnimControllerComp)
	{
	}
	virtual ~IdleAnimationState() = default;

	IdleAnimationState(IdleAnimationState&& other) = delete;
	IdleAnimationState(const IdleAnimationState& other) = delete;
	const IdleAnimationState& operator=(IdleAnimationState&& other) = delete;
	const IdleAnimationState& operator=(const IdleAnimationState& other) = delete;

	virtual void OnEnter() override
	{
		m_pCharAnim->SetAnimationClip(CharacterAnimControllerComponent::Idle);
	}
	virtual AnimationState* OnHandle(const SceneContext&) override
	{ 
		if (m_pCharAnim->GetCharacterComponent()->GetIsMeleeing()) return m_pCharAnim->GetMeleeAnimState();

		const auto& vel = m_pCharAnim->GetCharacterComponent()->GetTotalVelocity();
		if (std::abs(vel.y) > 0.15f)
		{
			return m_pCharAnim->GetJumpAnimState();
		}
		else if (std::abs(vel.x) > FLT_EPSILON || std::abs(vel.z) > FLT_EPSILON)
		{
			return m_pCharAnim->GetRunAnimState();
		}
		return this; 
	}
	//virtual void OnExit() override {}
};