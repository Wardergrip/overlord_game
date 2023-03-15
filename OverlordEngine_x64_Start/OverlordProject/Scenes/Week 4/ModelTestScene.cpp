#include "stdafx.h"
#include "ModelTestScene.h"
#include "Materials/ColorMaterial.h"

void ModelTestScene::Initialize()
{
	m_pChair = new GameObject();
	AddChild(m_pChair);
	auto pColMat = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	pColMat->SetColor(XMFLOAT4{ Colors::Red });
	auto pModel = m_pChair->AddComponent(new ModelComponent(L"Meshes/Chair.ovm"));
	pModel->SetMaterial(pColMat->GetMaterialId());
}
