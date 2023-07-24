#pragma once

class CharacterComponent;
class TextComponent;
class TestScene : public GameScene
{
public:
	TestScene() 
		: GameScene(L"TestScene") 
		, m_pPlayer{}
		, m_pCharComp{}
		, m_pDefaultMaterial{}
		, m_pLevelColliders{}
		, m_pCameraComp{}
	{
	}
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
	GameObject* m_pPlayer;
	CharacterComponent* m_pCharComp;
	physx::PxMaterial* m_pDefaultMaterial;
	std::vector<RigidBodyComponent*> m_pLevelColliders;
	CameraComponent* m_pCameraComp;

	void AddPlayerToScene(TextComponent* pBoltsTextComp);
	void AddLevelVisual();
	void AddLevelHitbox();
	void AddFlagToScene();
	GameObject* AddBoxToScene(const DirectX::XMVECTOR& pos);

	int m_BoneTransformIdx;
	ModelComponent* m_pRatchetModel;
	GameObject* m_pTagbox;
};