#pragma once
#include <memory>
class CharacterComponent;
class ModelAnimator;
class AnimationState;
class IdleAnimationState;
class JumpAnimationState;
class RunforwardAnimationState;
class MeleeAnimationState;
class CharacterAnimControllerComponent final : public BaseComponent
{
public:
	enum AnimationClipId : int
	{
		Idle = 0,
		Jump = 1,
		RunForward = 2,
		StrafeRight = 3,
		Melee = 4
	};

	CharacterAnimControllerComponent(CharacterComponent* pCharacter, ModelAnimator* pModelAnim);
	~CharacterAnimControllerComponent() override = default;

	CharacterAnimControllerComponent(const CharacterAnimControllerComponent& other) = delete;
	CharacterAnimControllerComponent(CharacterAnimControllerComponent&& other) noexcept = delete;
	CharacterAnimControllerComponent& operator=(const CharacterAnimControllerComponent& other) = delete;
	CharacterAnimControllerComponent& operator=(CharacterAnimControllerComponent&& other) noexcept = delete;

	AnimationState* GetIdleAnimState() const { return reinterpret_cast<AnimationState*>(m_pIdleAnimationState.get()); }
	AnimationState* GetJumpAnimState() const { return reinterpret_cast<AnimationState*>(m_pJumpAnimationState.get()); }
	AnimationState* GetRunforwardAnimState() const { return reinterpret_cast<AnimationState*>(m_pRunforwardAnimationState.get()); }
	AnimationState* GetMeleeAnimState() const { return reinterpret_cast<AnimationState*>(m_pMeleeAnimationState.get()); }
	
	CharacterComponent* GetCharacterComponent() const { return m_pCharacter; }

	void SetAnimationClip(AnimationClipId id, bool isReversed = false, float speed = 1.f);
protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	AnimationState* m_pCurrentAnimationState;
	std::unique_ptr<IdleAnimationState> m_pIdleAnimationState;
	std::unique_ptr<JumpAnimationState> m_pJumpAnimationState;
	std::unique_ptr<RunforwardAnimationState> m_pRunforwardAnimationState;
	std::unique_ptr<MeleeAnimationState> m_pMeleeAnimationState;

	CharacterComponent* m_pCharacter;
	ModelAnimator* m_pModelAnim;
	int m_LastAnimationClip;
	bool m_LastIsReverse;
};
