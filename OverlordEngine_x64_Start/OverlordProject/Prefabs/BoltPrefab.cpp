#include "stdafx.h"
#include "BoltPrefab.h"
#include "Materials/ColorMaterial.h"
#include "Components/ScoreComponent.h"
#include "Components/BoltComponent.h"

BoltPrefab::BoltPrefab(GameObject* pPlayer)
{
	AddComponent(new BoltComponent(pPlayer));
}

void BoltPrefab::Initialize(const SceneContext&)
{
	constexpr float scale{ 1.f };
	auto pBoltMat = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.f);

	auto pColMat = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	pColMat->SetColor(DirectX::XMFLOAT4{ DirectX::Colors::Orange });
	auto pBoltModel = AddComponent(new ModelComponent(L"Meshes/Bolt.ovm", false));
	pBoltModel->SetMaterial(pColMat);
	
	const auto pPxConvexMesh = ContentManager::Load<PxConvexMesh>(L"Meshes/Bolt.ovpc");
	auto boltRb = AddComponent(new RigidBodyComponent());
	boltRb->SetKinematic(true);
	boltRb->AddCollider(PxConvexMeshGeometry{ pPxConvexMesh,PxMeshScale({ scale,scale,scale }) }, *pBoltMat,true);
	SetOnTriggerCallBack([&](GameObject* /*pTriggerObject*/, GameObject* pOtherObject, PxTriggerAction /*action*/)
	{
			if (pOtherObject->GetTag() == L"Player")
			{
				auto scoreComp = pOtherObject->GetComponent<ScoreComponent>();
				if (scoreComp)
				{
					scoreComp->AddBolts(1);
				}
				else
				{
					std::cout << "Did not find scorecomponent on overlapping object tagged 'Player'\n";
				}
				// TODO: Sounds and stuff

				SetMarkForDestroy();
			}
	});

	// Random rotation
	const float xRot{ static_cast<float>(rand() % 360) };
	const float yRot{ static_cast<float>(rand() % 360) };
	const float zRot{ static_cast<float>(rand() % 360) };
	GetTransform()->Rotate(xRot, yRot, zRot);
}
