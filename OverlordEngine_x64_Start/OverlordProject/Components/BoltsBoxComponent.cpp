#include "stdafx.h"
#include "BoltsBoxComponent.h"
#include "Prefabs/BoltPrefab.h"

BoltsBoxComponent::BoltsBoxComponent(GameObject* pPlayer)
	:m_pPlayer{pPlayer}
{
}

void BoltsBoxComponent::Initialize(const SceneContext& /*sceneContext*/)
{
	GetGameObject()->SetOnTriggerCallBack([&](GameObject* /*pTriggerObject*/, GameObject* pOtherObject, PxTriggerAction /*action*/)
	{
		if (pOtherObject->GetTag() == L"Weapon")
		{
			BreakSequence();
		}
	});
}

void BoltsBoxComponent::Update(const SceneContext& sceneContext)
{
	if (m_DebugTimer)
	{
		m_DebugTimeElapsed += sceneContext.pGameTime->GetElapsed();
		if (m_DebugTimeElapsed >= 5.f)
		{
			BreakSequence();
			m_DebugTimer = false;
		}
	}
}

void BoltsBoxComponent::BreakSequence()
{
	std::cout << "BreakSeq currently disabled\n";
	return;
#if 0
	auto thisObj = GetGameObject();
	auto scene = thisObj->GetScene();

	////Particle System
	//ParticleEmitterSettings settings{};
	//settings.velocity = { 0.f,6.f,0.f };
	//settings.minSize = 1.f;
	//settings.maxSize = 2.f;
	//settings.minEnergy = 1.f;
	//settings.maxEnergy = 2.f;
	//settings.minScale = 3.5f;
	//settings.maxScale = 5.5f;
	//settings.minEmitterRadius = .2f;
	//settings.maxEmitterRadius = .5f;
	//settings.color = { 1.f,1.f,1.f, .6f };

	//const auto pEmitObj = scene->AddChild(new GameObject);
	//pEmitObj->AddComponent(new ParticleEmitterComponent(L"Textures/Bolt.png", settings, 50));
	//pEmitObj->GetTransform()->Translate(thisObj->GetTransform()->GetWorldPosition());

	size_t amount = static_cast<size_t>(rand() % 10) + size_t{1};
	for (size_t i{ 0 }; i < amount; ++i)
	{
		auto pBolt = scene->AddChild(new BoltPrefab(m_pPlayer));
		const auto& thisPos = thisObj->GetTransform()->GetPosition();
		XMFLOAT3 offset{ (rand() % 101) / 100.f,(rand() % 101) / 100.f, (rand() % 101) / 100.f };
		pBolt->GetTransform()->Translate(thisPos.x + offset.x, thisPos.y + offset.y, thisPos.z + offset.z);
	}

	thisObj->SetMarkForDestroy();
#endif
}
