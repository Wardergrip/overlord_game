#include "stdafx.h"
#include "PongScene.h"

#include "Prefabs/CubePrefab.h"
#include "Prefabs/SpherePrefab.h"

void PongScene::Initialize()
{
	auto& physx = PxGetPhysics();

	// SceneSettings
	m_SceneContext.settings.clearColor = XMFLOAT4{0,0,0,1};
	m_SceneContext.settings.drawGrid = false;
	
	// Fixed camera
	{
		const auto pFixedCamera = new FixedCamera();
		pFixedCamera->GetTransform()->Translate(0, 40.f, 0);
		pFixedCamera->GetTransform()->Rotate(90, 0, 0);
		AddChild(pFixedCamera);
		SetActiveCamera(pFixedCamera->GetComponent<CameraComponent>());
	}

	// Material
	auto pDefaultMat = physx.createMaterial(.0f, .0f, 1.0f);

	// Level
	{
		XMFLOAT3 dimensions{ 60,3,3 };
		const constexpr float displacement{ 15.f };
		m_pCeiling = new GameObject();
		AddChild(m_pCeiling);
		auto pRigidBody = m_pCeiling->AddComponent(new RigidBodyComponent(true));
		pRigidBody->AddCollider(PxBoxGeometry{ dimensions.x * 0.5f,dimensions.y * 0.5f,dimensions.z * 0.5f }, *pDefaultMat);

		m_pFloor = new GameObject();
		AddChild(m_pFloor);
		pRigidBody = m_pFloor->AddComponent(new RigidBodyComponent(true));
		pRigidBody->AddCollider(PxBoxGeometry{ dimensions.x * 0.5f,dimensions.y * 0.5f,dimensions.z * 0.5f }, *pDefaultMat);

		m_pCeiling->GetTransform()->Translate(XMVECTOR{ 0,0,displacement });
		m_pFloor->GetTransform()->Translate(XMVECTOR{ 0,0,-displacement });
	}

	// Paddles
	{
		XMFLOAT3 paddleDimensions{ 3,3,6 };
		m_pPaddleLeft = new CubePrefab(paddleDimensions, XMFLOAT4{ Colors::White });
		m_pPaddleRight = new CubePrefab(paddleDimensions, XMFLOAT4{ Colors::White });

		AddChild(m_pPaddleLeft);
		AddChild(m_pPaddleRight);

		auto pRigidBody = m_pPaddleLeft->AddComponent(new RigidBodyComponent(true));
		pRigidBody->AddCollider(PxBoxGeometry{ paddleDimensions.x * 0.5f,paddleDimensions.y * 0.5f,paddleDimensions.z * 0.5f }, *pDefaultMat);

		pRigidBody = m_pPaddleRight->AddComponent(new RigidBodyComponent(true));
		pRigidBody->AddCollider(PxBoxGeometry{ paddleDimensions.x * 0.5f,paddleDimensions.y * 0.5f,paddleDimensions.z * 0.5f }, *pDefaultMat);
	}

	// Ball
	{
		const constexpr float ballRadius{ 1.f };
		const constexpr int ballSteps{ 10 };
		m_pBall = new SpherePrefab(ballRadius, ballSteps, XMFLOAT4{ Colors::Red });
		AddChild(m_pBall);

		auto pRigidBody = m_pBall->AddComponent(new RigidBodyComponent());
		pRigidBody->SetConstraint(RigidBodyConstraint::TransY, false);
		pRigidBody->SetConstraint(RigidBodyConstraint::AllRot, false);
		pRigidBody->AddCollider(PxSphereGeometry{ ballRadius }, *pDefaultMat);
	}

	Reset();
}

void PongScene::Update()
{
	const float deltaTime = m_SceneContext.pGameTime->GetElapsed();

	auto inputManager = m_SceneContext.pInput;
	auto inputState = InputState::down;
	
	constexpr const float movementSpeed{ 10.f };
	constexpr const float maxDisplacement{ 10.f };


	// LEFT
	if (inputManager->IsKeyboardKey(inputState, 'Q'))
	{
		auto pos = m_pPaddleLeft->GetTransform()->GetPosition();
		pos.z += movementSpeed * deltaTime;
		pos.z = std::min(pos.z, maxDisplacement);
		m_pPaddleLeft->GetTransform()->Translate(pos);
	}
	if (inputManager->IsKeyboardKey(inputState, 'A'))
	{
		auto pos = m_pPaddleLeft->GetTransform()->GetPosition();
		pos.z -= movementSpeed * deltaTime;
		pos.z = std::max(pos.z, -maxDisplacement);
		m_pPaddleLeft->GetTransform()->Translate(pos);
	}

	// RIGHT
	if (inputManager->IsKeyboardKey(inputState, VK_UP))
	{
		auto pos = m_pPaddleRight->GetTransform()->GetPosition();
		pos.z += movementSpeed * deltaTime;
		pos.z = std::min(pos.z, maxDisplacement);
		m_pPaddleRight->GetTransform()->Translate(pos);
	}
	if (inputManager->IsKeyboardKey(inputState, VK_DOWN))
	{
		auto pos = m_pPaddleRight->GetTransform()->GetPosition();
		pos.z -= movementSpeed * deltaTime;
		pos.z = std::max(pos.z, -maxDisplacement);
		m_pPaddleRight->GetTransform()->Translate(pos);
	}

	// Reset
	auto ballPos = m_pBall->GetTransform()->GetPosition();
	if (InputManager::IsKeyboardKey(InputState::pressed, 'R') || std::abs(ballPos.x) > 25 || std::abs(ballPos.z) > 25)
	{
		Reset();
	}

	/*auto& pos = m_SceneContext.pCamera->GetTransform()->GetPosition();
	auto& rot = m_SceneContext.pCamera->GetTransform()->GetRotation();
	std::cout << pos.x << " " << pos.y << " " << pos.z
		<< " ROT: " << rot.x << " " << rot.y << " " << rot.z << '\n';*/
}

void PongScene::Draw()
{
}

void PongScene::OnGUI()
{
}

void PongScene::Reset()
{
	m_pPaddleLeft->GetTransform()->Translate(XMVECTOR{ -20,0,0 });
	m_pPaddleRight->GetTransform()->Translate(XMVECTOR{ 20,0,0 });
	m_pBall->GetTransform()->Translate(XMVECTOR{ 0,0,0 });
	m_pBall->GetComponent<RigidBodyComponent>()->AddForce(XMFLOAT3{ 10,0,10 }, PxForceMode::eIMPULSE);
}
