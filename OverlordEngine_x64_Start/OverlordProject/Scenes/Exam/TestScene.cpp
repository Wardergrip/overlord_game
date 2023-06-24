#include "stdafx.h"
#include "TestScene.h"
#include "Materials/ColorMaterial.h"
#include "Materials/DiffuseMaterial_Skinned.h"
#include "Components/CharacterComponent.h"
#include "Components/CharacterAnimControllerComponent.h"

void TestScene::Initialize()
{
	m_pPlayer = nullptr;
	m_pCameraComp = nullptr;
	m_pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);

	m_SceneContext.settings.enableOnGUI = true;

	auto& physX{ PxGetPhysics() };
	auto pPhysMat{ physX.createMaterial(0.5f, 0.5f, 0.5f) };

	/*auto pLevel = new GameObject();
	AddChild(pLevel);
	auto pModel = pLevel->AddComponent(new ModelComponent(L"Meshes/Aridia.ovm"));

	constexpr UINT8 amountSubmeshes{ 205 };
	for (UINT8 submeshid{ 0 }; submeshid < amountSubmeshes; ++submeshid)
	{
		std::wstringstream filePath;
		filePath << L"Textures/Aridia/" << std::to_wstring(221 + submeshid) << L".png";
		auto pMat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
		pMat->SetDiffuseTexture(filePath.str());
		pModel->SetMaterial(pMat,submeshid);
	}*/

	auto pLevelHitboxObj = new GameObject();
	AddChild(pLevelHitboxObj);
	const auto pPxTriangleMesh = ContentManager::Load<PxTriangleMesh>(L"Meshes/AridiaPlatform.ovpt");
	auto levelRb = pLevelHitboxObj->AddComponent(new RigidBodyComponent(true));
	levelRb->AddCollider(PxTriangleMeshGeometry(pPxTriangleMesh, PxMeshScale({ .5f,.5f,.5f })), *pPhysMat);

	AddPlayerToScene();
	/*auto pCamera = new FixedCamera();
	m_pCameraComp = pCamera->GetComponent<CameraComponent>();
	AddChild(pCamera);*/	
}

void TestScene::OnGUI()
{
	if (m_pCharComp) m_pCharComp->DrawImGui();
}

void TestScene::AddPlayerToScene()
{

	//Ground Plane	
	GameSceneExt::CreatePhysXGroundPlane(*this, m_pDefaultMaterial);

	//Character
	CharacterDesc characterDesc{ m_pDefaultMaterial };
	characterDesc.actionId_MoveForward = CharacterMoveForward;
	characterDesc.actionId_MoveBackward = CharacterMoveBackward;
	characterDesc.actionId_MoveLeft = CharacterMoveLeft;
	characterDesc.actionId_MoveRight = CharacterMoveRight;
	characterDesc.actionId_Jump = CharacterJump;

	m_pPlayer = AddChild(new GameObject());
	m_pCharComp = m_pPlayer->AddComponent(new CharacterComponent(characterDesc));
	m_pPlayer->GetTransform()->Translate(0.f, 5.f, 0.f);
	m_pCharComp->GetCharacterCamera()->GetTransform()->Translate(DirectX::XMVECTOR{0, 5, -10.f});

	//Input
	auto inputAction = InputAction(CharacterMoveLeft, InputState::down, 'A');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterMoveRight, InputState::down, 'D');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterMoveForward, InputState::down, 'W');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterMoveBackward, InputState::down, 'S');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterJump, InputState::pressed, VK_SPACE, -1, XINPUT_GAMEPAD_A);
	m_SceneContext.pInput->AddInputAction(inputAction);

	// Model
	auto pRatchet = new GameObject();
	m_pPlayer->AddChild(pRatchet);
	auto pRatchetModel = pRatchet->AddComponent(new ModelComponent(L"Meshes/Ratchet/RatchetFixedAnims.ovm"));
	auto pRatchetMainDiff = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	auto pRatchetSubDiff_1 = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	auto pRatchetSubDiff_2 = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	pRatchetMainDiff->SetDiffuseTexture(L"Textures/Adamantine/Texture0.png");
	pRatchetSubDiff_1->SetDiffuseTexture(L"Textures/Adamantine/Texture1.png");
	pRatchetSubDiff_2->SetDiffuseTexture(L"Textures/Adamantine/Texture2.png");
	pRatchetModel->SetMaterial(pRatchetMainDiff, 0);
	pRatchetModel->SetMaterial(pRatchetSubDiff_1, 1);
	pRatchetModel->SetMaterial(pRatchetSubDiff_2, 2);

	pRatchet->GetTransform()->Scale(0.05f);
	pRatchet->GetTransform()->Translate(0, -1.2f, 0);
	pRatchet->GetTransform()->Rotate(0, 180, 0);

	pRatchet->AddComponent(new CharacterAnimControllerComponent(m_pCharComp, pRatchetModel->GetAnimator()));
}
