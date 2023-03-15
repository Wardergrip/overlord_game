#include "stdafx.h"
#include "UberMaterialScene.h"
#include "Materials/UberMaterial.h"

void UberMaterialScene::Initialize()
{
	// Create uber materials
	m_pUberMaterial = MaterialManager::Get()->CreateMaterial<UberMaterial>();

	// Create a sphere GO
	m_pSphere = new GameObject{};
	AddChild(m_pSphere);

	// Add a model component and assign the material
	m_pSphere->AddComponent(new ModelComponent{ L"Meshes/Sphere.ovm" })->SetMaterial(m_pUberMaterial);

	// Scale the sphere
	TransformComponent* pSphereTransform{ m_pSphere->GetComponent<TransformComponent>() };
	pSphereTransform->Scale(30.0f, 30.0f, 30.0f);

	//// Create a chair GO
	//GameObject* pChair{ new GameObject{} };
	//AddChild(pChair);

	//// Add a model component and assign the material
	//pChair->AddComponent(new ModelComponent{ L"Meshes/Chair.ovm" })->SetMaterial(m_pBricksMaterial);

	//// Scale the sphere
	//TransformComponent* pChairTransform{ pChair->GetComponent<TransformComponent>() };
	//pChairTransform->Scale(4.0f, 4.0f, 4.0f);
	//pChairTransform->Translate(-25.0f, -10.0f, -10.0f);

	// Disable the grid and enable ImGui
	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.enableOnGUI = true;
}

void UberMaterialScene::Update()
{
	constexpr float speed{ 10.f };
	m_pSphere->GetTransform()->Rotate(0,GetSceneContext().pGameTime->GetTotal() * speed,0);
}

void UberMaterialScene::OnGUI()
{
	m_pUberMaterial->DrawImGui();
}
