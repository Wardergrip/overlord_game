#include "stdafx.h"
#include "BoltPrefab.h"
#include "Materials/ColorMaterial.h"
#include "Components/ScoreComponent.h"
#include "Components/BoltComponent.h"
#include "Managers/SoundManager.h"

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

	const auto pFmod{ SoundManager::Get()->GetSystem() };
	std::string sfxFilepath;
	int random{ rand() % 3 };
	switch (random)
	{
	default:
	case 0:
		sfxFilepath = "Resources/SFX/BoltSFX_0.mp3";
		break;
	case 1:
		sfxFilepath = "Resources/SFX/BoltSFX_1.mp3";
		break;
	case 2:
		sfxFilepath = "Resources/SFX/BoltSFX_2.mp3";
		break;
	}
	//pFmod->createStream(sfxFilepath.c_str(), FMOD_DEFAULT, nullptr, &m_pPickupSound);
	pFmod->createSound(sfxFilepath.c_str(), FMOD_DEFAULT, nullptr, &m_pPickupSound);
	m_pChannel->setVolume(1.f);
	
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
					SoundManager::Get()->GetSystem()->playSound(m_pPickupSound, nullptr, false, &m_pChannel);
					m_pChannel->setVolume(1.f);
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
}
