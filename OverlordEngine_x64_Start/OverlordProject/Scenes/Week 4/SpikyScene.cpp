#include "stdafx.h"
#include "SpikyScene.h"
#include "Materials/SpikyMaterial.h"

void SpikyScene::Initialize()
{
	m_pOctaSphere = new GameObject();
	AddChild(m_pOctaSphere);
	m_pSpikyMaterial = MaterialManager::Get()->CreateMaterial<SpikyMaterial>();
	auto pModel = m_pOctaSphere->AddComponent(new ModelComponent(L"Meshes/OctaSphere.ovm"));
	pModel->SetMaterial(m_pSpikyMaterial->GetMaterialId());
	m_pOctaSphere->GetTransform()->Scale(15.f, 15.f, 15.f);

	// Disable the grid and enable ImGui
	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.enableOnGUI = true;
}

void SpikyScene::Update()
{
	constexpr float speed{ 20.f };
	m_pOctaSphere->GetTransform()->Rotate(0, m_SceneContext.pGameTime->GetTotal() * speed, 0);
}

void SpikyScene::OnGUI()
{
	m_pSpikyMaterial->DrawImGui();
}
