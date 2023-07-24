#pragma once
#include "AnimationState.h"

class RunforwardAnimationState final : public AnimationState
{

public:
	RunforwardAnimationState(CharacterAnimControllerComponent* pCharAnimControllerComp)
		:AnimationState(pCharAnimControllerComp)
	{
	}
	virtual ~RunforwardAnimationState() = default;

	RunforwardAnimationState(RunforwardAnimationState&& other) = delete;
	RunforwardAnimationState(const RunforwardAnimationState& other) = delete;
	const RunforwardAnimationState& operator=(RunforwardAnimationState&& other) = delete;
	const RunforwardAnimationState& operator=(const RunforwardAnimationState& other) = delete;

	virtual void OnEnter() override
	{
		bool reverse{ m_pCharAnim->GetCharacterComponent()->GetTotalVelocity().x < 0.f };
		m_pCharAnim->SetAnimationClip(CharacterAnimControllerComponent::RunForward, reverse);
	}
	virtual AnimationState* OnHandle() override
	{
		const auto& vel = m_pCharAnim->GetCharacterComponent()->GetTotalVelocity();
		if (std::abs(vel.x) < FLT_EPSILON || std::abs(vel.z) < FLT_EPSILON)
		{
			return m_pCharAnim->GetIdleAnimState();
		}
		else if (std::abs(vel.y) > 0.15f)
		{
			return m_pCharAnim->GetJumpAnimState();
		}
		else
		{
			bool reverse{ vel.x < 0.f };
			m_pCharAnim->SetAnimationClip(CharacterAnimControllerComponent::RunForward, reverse);
		}
		return this;
	}
	virtual void OnExit() override
	{

	}
};