#include "stdafx.h"
#include "ModelTestScene.h"
#include "Materials/ColorMaterial.h"
#include "Materials/DiffuseMaterial.h"

void ModelTestScene::Initialize()
{
	m_pChair = new GameObject();
	AddChild(m_pChair);
	auto pColMat = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	auto pDiffMat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	pColMat->SetColor(XMFLOAT4{ Colors::Red });
	pDiffMat->SetDiffuseTexture(L"Textures/Chair_Dark.dds");
	auto& pMat = pDiffMat;
	auto pModel = m_pChair->AddComponent(new ModelComponent(L"Meshes/Chair.ovm"));
	pModel->SetMaterial(pMat->GetMaterialId());
}
