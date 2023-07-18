#pragma once
class BoltsBoxComponent : public BaseComponent
{
public:
	BoltsBoxComponent() = default;
	~BoltsBoxComponent() override = default;

	BoltsBoxComponent(const BoltsBoxComponent& other) = delete;
	BoltsBoxComponent(BoltsBoxComponent&& other) noexcept = delete;
	BoltsBoxComponent& operator=(const BoltsBoxComponent& other) = delete;
	BoltsBoxComponent& operator=(BoltsBoxComponent&& other) noexcept = delete;

	void BreakSequence();
protected:
	void Initialize(const SceneContext& sceneContext) override;
	//void Update(const SceneContext& sceneContext) override;

};

