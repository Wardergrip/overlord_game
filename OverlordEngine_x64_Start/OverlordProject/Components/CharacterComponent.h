#pragma once
#include "Prefabs/Character.h"

class CharacterComponent : public BaseComponent
{
public:
	CharacterComponent(const CharacterDesc& characterDesc);
	~CharacterComponent() override = default;

	CharacterComponent(const CharacterComponent& other) = delete;
	CharacterComponent(CharacterComponent&& other) noexcept = delete;
	CharacterComponent& operator=(const CharacterComponent& other) = delete;
	CharacterComponent& operator=(CharacterComponent&& other) noexcept = delete;

	void DrawImGui();

	const XMFLOAT3& GetTotalVelocity() const { return m_TotalVelocity; }
	const XMFLOAT3& GetCurrentDirection() const { return m_CurrentDirection; }

	CameraComponent* GetCharacterCamera() { return m_pCameraComponent; }
	ControllerComponent* GetControllerCamera() { return m_pControllerComponent; }

	bool GetAllowInput() const { return m_AllowInput; }
	void SetAllowInput(bool state) { m_AllowInput = state; }

	bool GetIsMeleeing() const { return m_IsMeleeing; }
	void SetIsMeeling(bool state) { m_IsMeleeing = state; }
	 
protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	CameraComponent* m_pCameraComponent{};
	ControllerComponent* m_pControllerComponent{};
	bool m_AllowInput;
	bool m_IsMeleeing;

	CharacterDesc m_CharacterDesc;
	float m_TotalPitch{}, m_TotalYaw{};				//Total camera Pitch(X) and Yaw(Y) rotation
	float m_MoveAcceleration{},						//Acceleration required to reach maxMoveVelocity after 1 second (maxMoveVelocity / moveAccelerationTime)
		m_FallAcceleration{},						//Acceleration required to reach maxFallVelocity after 1 second (maxFallVelocity / fallAccelerationTime)
		m_MoveSpeed{};								//MoveSpeed > Horizontal Velocity = MoveDirection * MoveVelocity (= TotalVelocity.xz)

	XMFLOAT3 m_TotalVelocity{};						//TotalVelocity with X/Z for Horizontal Movement AND Y for Vertical Movement (fall/jump)
	XMFLOAT3 m_CurrentDirection{};					//Current/Last Direction based on Camera forward/right (Stored for deacceleration)

	FMOD::Channel* m_pChannel;
	FMOD::Sound* m_pFallSound;
};

