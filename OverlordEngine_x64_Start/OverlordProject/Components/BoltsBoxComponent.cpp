#include "stdafx.h"
#include "BoltsBoxComponent.h"
#include "Prefabs/BoltPrefab.h"
#include "Components/AutokillComponent.h"

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
	auto thisObj = GetGameObject();
	auto scene = thisObj->GetScene();

	//Particle System
	constexpr float timer{ 1.f };
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

	const auto pEmitObj = scene->AddChild(new GameObject);
	pEmitObj->AddComponent(new ParticleEmitterComponent(L"Textures/SoftBall.png", settings, 10));
	pEmitObj->AddComponent(new AutokillComponent(timer));
	const auto& objPos = thisObj->GetTransform()->GetWorldPosition();
	pEmitObj->GetTransform()->Translate(objPos.x,objPos.y + 0.5f,objPos.z);

	constexpr float offsetMultiplier{ 2.f };
	size_t amount = static_cast<size_t>(rand() % 10) + size_t{1};
	for (size_t i{ 0 }; i < amount; ++i)
	{
		auto pBolt = scene->AddChild(new BoltPrefab(m_pPlayer));
		const auto& thisPos = thisObj->GetTransform()->GetPosition();
		XMFLOAT3 offset{ ((rand() % 101) / 100.f) * offsetMultiplier,((rand() % 101) / 100.f) * offsetMultiplier, ((rand() % 101) / 100.f) * offsetMultiplier };
		XMFLOAT3 randomRot{ static_cast<float>(rand() % 90),static_cast<float>(rand() % 90) ,static_cast<float>(rand() % 90) };
		pBolt->GetTransform()->Translate(thisPos.x + offset.x, thisPos.y + offset.y, thisPos.z + offset.z);
		pBolt->GetTransform()->Rotate(randomRot.x, randomRot.y, randomRot.z);
	}

	thisObj->SetMarkForDestroy();
}
