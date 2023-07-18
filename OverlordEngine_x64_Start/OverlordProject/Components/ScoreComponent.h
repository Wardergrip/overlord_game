#pragma once
class ScoreComponent final : public BaseComponent
{
public:
	ScoreComponent();
	~ScoreComponent() override = default;

	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) noexcept = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;

	void AddBolts(int bolts);

private:
	int m_Bolts;
};

