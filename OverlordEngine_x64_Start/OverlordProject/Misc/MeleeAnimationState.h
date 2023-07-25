#pragma once
#include "AnimationState.h"

class MeleeAnimationState final : public AnimationState
{

public:
	MeleeAnimationState(CharacterAnimControllerComponent* pCharAnimControllerComp)
		:AnimationState(pCharAnimControllerComp)
		,m_Timer{}
		,m_MaxTimer{ 2.433f }
	{
		m_Timer = m_MaxTimer;
	}
	virtual ~MeleeAnimationState() = default;

	MeleeAnimationState(MeleeAnimationState&& other) = delete;
	MeleeAnimationState(const MeleeAnimationState& other) = delete;
	const MeleeAnimationState& operator=(MeleeAnimationState&& other) = delete;
	const MeleeAnimationState& operator=(const MeleeAnimationState& other) = delete;

	virtual void OnEnter() override
	{
		m_pCharAnim->SetAnimationClip(CharacterAnimControllerComponent::Melee, false);
		m_pCharAnim->GetCharacterComponent()->SetAllowInput(false);
	}
	virtual AnimationState* OnHandle(const SceneContext& sceneContext) override
	{
		m_Timer -= sceneContext.pGameTime->GetElapsed();
		if (m_Timer <= 0.f)
		{
			return m_pCharAnim->GetIdleAnimState();
		}
		return this;
	}
	virtual void OnExit() override
	{
		m_Timer = m_MaxTimer;
		m_pCharAnim->GetCharacterComponent()->SetAllowInput(true);
	}

private:
	float m_Timer;
	const float m_MaxTimer;
};