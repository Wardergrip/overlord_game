#pragma once
#include "AnimationState.h"
#include "Scenes/Exam/TestScene.h"

class RunAnimationState final : public AnimationState
{

public:
	RunAnimationState(CharacterAnimControllerComponent* pCharAnimControllerComp)
		:AnimationState(pCharAnimControllerComp)
	{
	}
	virtual ~RunAnimationState() = default;

	RunAnimationState(RunAnimationState&& other) = delete;
	RunAnimationState(const RunAnimationState& other) = delete;
	const RunAnimationState& operator=(RunAnimationState&& other) = delete;
	const RunAnimationState& operator=(const RunAnimationState& other) = delete;

	virtual void OnEnter() override
	{
		bool reverse{ m_pCharAnim->GetCharacterComponent()->GetTotalVelocity().x < 0.f };
		m_pCharAnim->SetAnimationClip(CharacterAnimControllerComponent::RunForward, reverse);
	}
	virtual AnimationState* OnHandle(const SceneContext& sceneContext) override
	{
		if (m_pCharAnim->GetCharacterComponent()->GetIsMeleeing()) return m_pCharAnim->GetMeleeAnimState();

		const auto& vel = m_pCharAnim->GetCharacterComponent()->GetTotalVelocity();
		if (std::abs(vel.x) < FLT_EPSILON || std::abs(vel.z) < FLT_EPSILON)
		{
			return m_pCharAnim->GetIdleAnimState();
		}
		else if (std::abs(vel.y) > 0.15f)
		{
			return m_pCharAnim->GetJumpAnimState();
		}
		else if (std::abs(vel.x) > FLT_EPSILON && (sceneContext.pInput->IsActionTriggered(TestScene::CharacterMoveForward) || sceneContext.pInput->IsActionTriggered(TestScene::CharacterMoveForward)))
		{
			bool reverse{ sceneContext.pInput->IsActionTriggered(TestScene::CharacterMoveBackward) };
			m_pCharAnim->SetAnimationClip(CharacterAnimControllerComponent::RunForward, reverse);
		}
		else if (std::abs(vel.z) > FLT_EPSILON && (sceneContext.pInput->IsActionTriggered(TestScene::CharacterMoveLeft) || sceneContext.pInput->IsActionTriggered(TestScene::CharacterMoveRight)))
		{
			bool reverse{ sceneContext.pInput->IsActionTriggered(TestScene::CharacterMoveLeft) };
			m_pCharAnim->SetAnimationClip(CharacterAnimControllerComponent::StrafeRight, reverse);
		}
		return this;
	}
	virtual void OnExit() override
	{

	}
};