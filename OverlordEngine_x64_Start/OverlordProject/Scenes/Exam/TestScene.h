#pragma once

class CharacterComponent;
class TextComponent;
class PostPixelated;
class TestScene : public GameScene
{
public:
	static bool ENDGOAL_REACHED;

	enum InputIds
	{
		CharacterMoveLeft,
		CharacterMoveRight,
		CharacterMoveForward,
		CharacterMoveBackward,
		CharacterJump,
		CharacterMelee,
		PauseGame,
		GoMainMenu
	};

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
	void Update() override;
	/*void Draw() override;*/
	void OnGUI() override;
	void PostDraw() override;
	void OnSceneDeactivated() override;

private:
	GameObject* m_pPlayer;
	CharacterComponent* m_pCharComp;
	physx::PxMaterial* m_pDefaultMaterial;
	std::vector<RigidBodyComponent*> m_pLevelColliders;
	CameraComponent* m_pCameraComp;
	GameObject* m_pPauseMenuRoot;

	void AddPlayerToScene(TextComponent* pBoltsTextComp);
	void AddLevelVisual();
	void AddLevelHitbox();
	void AddFlagToScene();
	GameObject* AddBoxToScene(const DirectX::XMVECTOR& pos, bool debugTimer = false);

	int m_BoneTransformIdx;
	ModelComponent* m_pRatchetModel;
	GameObject* m_pTagbox;

	PostPixelated* m_pPostPixaleted;
	GameObject* m_pBoltsAmountObj;

	FMOD::Sound* m_pMusic{ nullptr };
	FMOD::Channel* m_pChannel{ nullptr };

	DirectX::XMFLOAT3 m_LightDirection;
	DirectX::XMFLOAT3 m_LightOffset;

	bool m_DrawShadowMap;
	float m_ShadowMapScale;
	float m_ShadowMapNear;
	float m_ShadowMapFar;

	float m_EndGoalWaitTime;
	float m_EndGoalReachedTimer;
};