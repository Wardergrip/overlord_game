#pragma once

class Character;
class TestScene : public GameScene
{
public:
	TestScene() : GameScene(L"TestScene") {}
	~TestScene() override = default;

	TestScene(const TestScene& other) = delete;
	TestScene(TestScene&& other) noexcept = delete;
	TestScene& operator=(const TestScene& other) = delete;
	TestScene& operator=(TestScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	/*void Update() override;
	void Draw() override;*/
	void OnGUI() override;

private:
	enum InputIds
	{
		CharacterMoveLeft,
		CharacterMoveRight,
		CharacterMoveForward,
		CharacterMoveBackward,
		CharacterJump
	};
	Character* m_pCharacter;
	physx::PxMaterial* m_pDefaultMaterial;
	std::vector<RigidBodyComponent*> m_pLevelColliders;
	CameraComponent* m_pCameraComp;

	void AddPlayerToScene();
};