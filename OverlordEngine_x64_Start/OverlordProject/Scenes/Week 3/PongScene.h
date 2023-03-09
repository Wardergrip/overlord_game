#pragma once
class CubePrefab;
class SpherePrefab;

class PongScene : public GameScene
{
public:
	PongScene() : GameScene(L"Pong Scene") {}
	~PongScene() override = default;

	PongScene(const PongScene& other) = delete;
	PongScene(PongScene&& other) noexcept = delete;
	PongScene& operator=(const PongScene& other) = delete;
	PongScene& operator=(PongScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;

private:
	CubePrefab* m_pPaddleLeft;
	CubePrefab* m_pPaddleRight;

	SpherePrefab* m_pBall;

	GameObject* m_pTriggerLeft;
	GameObject* m_pTriggerRight;

	GameObject* m_pCeiling;
	GameObject* m_pFloor;
};