#pragma once
#include "AnimationState.h"

class JumpAnimationState final : public AnimationState
{

public:
	JumpAnimationState(CharacterAnimControllerComponent* pCharAnimControllerComp)
		:AnimationState(pCharAnimControllerComp)
		,m_GoingDown{ false }
	{
	}
	virtual ~JumpAnimationState() = default;

	JumpAnimationState(JumpAnimationState&& other) = delete;
	JumpAnimationState(const JumpAnimationState& other) = delete;
	const JumpAnimationState& operator=(JumpAnimationState&& other) = delete;
	const JumpAnimationState& operator=(const JumpAnimationState& other) = delete;

	virtual void OnEnter() override
	{
		m_pCharAnim->SetAnimationClip(CharacterAnimControllerComponent::Jump, false, 2.f);
	}
	virtual AnimationState* OnHandle() override
	{
		const auto& vel = m_pCharAnim->GetCharacterComponent()->GetTotalVelocity();
		if (m_GoingDown && std::abs(vel.y) < 0.15f)
		{
			if (std::abs(vel.x) > FLT_EPSILON || std::abs(vel.z) > FLT_EPSILON)
			{
				return m_pCharAnim->GetRunforwardAnimState();
			}
			return m_pCharAnim->GetIdleAnimState();

		}
		else if (vel.y > 0.15f)
		{
			return this;
		}
		else if (vel.y <= -FLT_EPSILON)
		{
			m_GoingDown = true;
			return this;
		}
		return this;
	}
	virtual void OnExit() override
	{
		m_GoingDown = false;
	}

private:
	bool m_GoingDown;
};