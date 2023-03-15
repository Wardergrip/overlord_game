#include "stdafx.h"
#include "ModelTestScene.h"
#include "Materials/ColorMaterial.h"
#include "Materials/DiffuseMaterial.h"

void ModelTestScene::Initialize()
{
	auto& physX{ PxGetPhysics() };
	auto pPhysMat{ physX.createMaterial(0.5f, 0.5f, 0.5f) };

	m_pChair = new GameObject();
	AddChild(m_pChair);
	auto pColMat = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	auto pDiffMat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	pColMat->SetColor(XMFLOAT4{ Colors::Red });
	pDiffMat->SetDiffuseTexture(L"Textures/Chair_Dark.dds");
	auto& pMat = pDiffMat;
	auto pModel = m_pChair->AddComponent(new ModelComponent(L"Meshes/Chair.ovm"));
	pModel->SetMaterial(pMat->GetMaterialId());

	m_pChair->GetComponent<TransformComponent>()->Translate(0.0f, 10.0f, 0.0f);

	const auto pConvexMesh = ContentManager::Load<PxConvexMesh>(L"Meshes/Chair.ovpc");
	const auto convexGeometry{ PxConvexMeshGeometry{ pConvexMesh } };

	m_pChair->AddComponent(new RigidBodyComponent())->AddCollider(convexGeometry, *pPhysMat);


	GameSceneExt::CreatePhysXGroundPlane(*this, pPhysMat);
}
