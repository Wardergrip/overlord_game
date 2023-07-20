#pragma once
class BoltComponent final : public BaseComponent
{
public:
	BoltComponent(GameObject* pPlayer);
	virtual ~BoltComponent() = default;

	BoltComponent(const BoltComponent& other) = delete;
	BoltComponent(BoltComponent&& other) noexcept = delete;
	BoltComponent& operator=(const BoltComponent& other) = delete;
	BoltComponent& operator=(BoltComponent&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	GameObject* m_pPlayer;
};

