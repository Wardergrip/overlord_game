#include "stdafx.h"
#include "TestScene.h"
#include "Materials/ColorMaterial.h"
#include "Materials/DiffuseMaterial_Skinned.h"
#include "Prefabs/Character.h"

void TestScene::Initialize()
{
	m_pCharacter = nullptr;
	m_pCameraComp = nullptr;
	m_pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);

	m_SceneContext.settings.enableOnGUI = true;

	//auto& physX{ PxGetPhysics() };
	//auto pPhysMat{ physX.createMaterial(0.5f, 0.5f, 0.5f) };

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
	m_pCharacter->GetComponent<CameraComponent>(true)->GetTransform()->Translate(DirectX::XMVECTOR{0, 5, -10.f});

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
	auto pAdamanite = new GameObject();
	m_pCharacter->AddChild(pAdamanite);
	auto pAdamModel = pAdamanite->AddComponent(new ModelComponent(L"Meshes/Ratchet/RatchetFixedAnims.ovm"));
	auto pAdamMainDiff = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	auto pAdamSubDiff_1 = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	auto pAdamSubDiff_2 = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	pAdamMainDiff->SetDiffuseTexture(L"Textures/Adamantine/Texture0.png");
	pAdamSubDiff_1->SetDiffuseTexture(L"Textures/Adamantine/Texture1.png");
	pAdamSubDiff_2->SetDiffuseTexture(L"Textures/Adamantine/Texture2.png");
	pAdamModel->SetMaterial(pAdamMainDiff, 0);
	pAdamModel->SetMaterial(pAdamSubDiff_1, 1);
	pAdamModel->SetMaterial(pAdamSubDiff_2, 2);

	pAdamanite->GetTransform()->Scale(0.05f);
	pAdamanite->GetTransform()->Translate(0, -1.2f, 0);
	pAdamanite->GetTransform()->Rotate(0, 180, 0);

	auto pAnimator = pAdamModel->GetAnimator();
	pAnimator->SetAnimation(0);
	pAnimator->SetAnimationSpeed(1.0f);
	pAnimator->Play();

}
