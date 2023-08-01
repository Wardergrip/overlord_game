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
	constexpr float scale{ 0.2f };
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

	GetTransform()->Scale(scale);

	ParticleEmitterSettings settings{};
	settings.velocity = { 0.f,2.5f,0.f };
	settings.minSize = 0.1f;
	settings.maxSize = 0.5f;
	settings.minEnergy = 1.0f;
	settings.maxEnergy = 1.0f;
	settings.minScale = 0.01f;
	settings.maxScale = 0.05f;
	settings.minEmitterRadius = 0.8f;
	settings.maxEmitterRadius = 2.0f;
	settings.color = { 0.2f,0.78f,1.f, .6f };

	const auto pEmitObj = AddChild(new GameObject);
	pEmitObj->AddComponent(new ParticleEmitterComponent(L"Textures/SoftBall.png", settings, 10));
}
