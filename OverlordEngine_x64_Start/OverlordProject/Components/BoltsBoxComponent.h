#pragma once
class BoltsBoxComponent : public BaseComponent
{
public:
	BoltsBoxComponent(GameObject* pPlayer);
	virtual ~BoltsBoxComponent() = default;

	BoltsBoxComponent(const BoltsBoxComponent& other) = delete;
	BoltsBoxComponent(BoltsBoxComponent&& other) noexcept = delete;
	BoltsBoxComponent& operator=(const BoltsBoxComponent& other) = delete;
	BoltsBoxComponent& operator=(BoltsBoxComponent&& other) noexcept = delete;

	void StartDebugTimer() { m_DebugTimer = true; }
protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	void BreakSequence();

	bool m_DebugTimer{ false };
	float m_DebugTimeElapsed{ 0.0f };
	GameObject* m_pPlayer;
};

