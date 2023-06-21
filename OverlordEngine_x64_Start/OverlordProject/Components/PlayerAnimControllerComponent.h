#pragma once
class Character;
class PlayerAnimControllerComponent : public BaseComponent
{
public:
	PlayerAnimControllerComponent(Character* pCharacter);
	~PlayerAnimControllerComponent() override = default;

	PlayerAnimControllerComponent(const PlayerAnimControllerComponent& other) = delete;
	PlayerAnimControllerComponent(PlayerAnimControllerComponent&& other) noexcept = delete;
	PlayerAnimControllerComponent& operator=(const PlayerAnimControllerComponent& other) = delete;
	PlayerAnimControllerComponent& operator=(PlayerAnimControllerComponent&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	Character* m_pCharacter;
};
