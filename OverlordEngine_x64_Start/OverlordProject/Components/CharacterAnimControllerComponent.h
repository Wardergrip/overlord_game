#pragma once
class CharacterComponent;
class ModelAnimator;
class CharacterAnimControllerComponent : public BaseComponent
{
public:
	CharacterAnimControllerComponent(CharacterComponent* pCharacter, ModelAnimator* pModelAnim);
	~CharacterAnimControllerComponent() override = default;

	CharacterAnimControllerComponent(const CharacterAnimControllerComponent& other) = delete;
	CharacterAnimControllerComponent(CharacterAnimControllerComponent&& other) noexcept = delete;
	CharacterAnimControllerComponent& operator=(const CharacterAnimControllerComponent& other) = delete;
	CharacterAnimControllerComponent& operator=(CharacterAnimControllerComponent&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	CharacterComponent* m_pCharacter;
	ModelAnimator* m_pModelAnim;
	int m_LastAnimationClip;
	void SetAnimationClip(int id);
};
