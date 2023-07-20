#pragma once
class TextComponent;
class ScoreComponent final : public BaseComponent
{
public:
	ScoreComponent(TextComponent* pBoltsTextComp);
	~ScoreComponent() override = default;

	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) noexcept = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;

	void AddBolts(int bolts);

protected:
	void Initialize(const SceneContext& sceneContext) override;

private:
	int m_Bolts;
	TextComponent* m_pBoltsTextComp;
};

