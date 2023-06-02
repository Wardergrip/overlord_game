#include "stdafx.h"
#include "TestScene.h"
#include "Materials/ColorMaterial.h"
#include "Materials/DiffuseMaterial.h"
#include "Prefabs/Character.h"

void TestScene::Initialize()
{
	m_pCharacter = nullptr;
	m_pCameraComp = nullptr;
	m_pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);

	m_SceneContext.settings.enableOnGUI = true;

	//auto& physX{ PxGetPhysics() };
	//auto pPhysMat{ physX.createMaterial(0.5f, 0.5f, 0.5f) };

	auto pLevel = new GameObject();
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
	}

	AddPlayerToScene();
	/*auto pCamera = new FixedCamera();
	m_pCameraComp = pCamera->GetComponent<CameraComponent>();
	AddChild(pCamera);*/
}

void TestScene::OnGUI()
{
	if (m_pCharacter) m_pCharacter->DrawImGui();
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

	m_pCharacter = AddChild(new Character(characterDesc));
	m_pCharacter->GetTransform()->Translate(0.f, 5.f, 0.f);

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
}
