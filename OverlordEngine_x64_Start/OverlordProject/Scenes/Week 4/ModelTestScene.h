#pragma once
class ModelTestScene : public GameScene
{
public:
	ModelTestScene() :GameScene(L"ModelTestScene") {}
	~ModelTestScene() override = default;

	ModelTestScene(const ModelTestScene& other) = delete;
	ModelTestScene(ModelTestScene&& other) noexcept = delete;
	ModelTestScene& operator=(const ModelTestScene& other) = delete;
	ModelTestScene& operator=(ModelTestScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	/*void Update() override;
	void OnGUI() override;*/

private:
	GameObject* m_pSprite{};
	float m_TotalRotation{};
	bool m_AutoRotate{};
};

