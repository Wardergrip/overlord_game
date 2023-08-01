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
	const auto pFmod{ SoundManager::Get()->GetSystem() };
	std::string sfxFilepath;
	int random{ rand() % 2 };
	switch (random)
	{
	case 0:
		sfxFilepath = "Resources/SFX/CrateBreak_0.mp3";
		break;
	case 1:
		sfxFilepath = "Resources/SFX/CrateBreak_1.mp3";
		break;
	}
	pFmod->createStream(sfxFilepath.c_str(), FMOD_DEFAULT, nullptr, &m_pBreakSound);
	m_pChannel->setVolume(1.f);

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
	const auto pFmod{ SoundManager::Get()->GetSystem() };
	pFmod->playSound(m_pBreakSound, nullptr, false, &m_pChannel);
	m_pChannel->setVolume(1.f);

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
	size_t amount = static_cast<size_t>(rand() % 8) + size_t{3};
	for (size_t i{ 0 }; i < amount; ++i)
	{
		auto pBolt = scene->AddChild(new BoltPrefab(m_pPlayer));
		const auto& thisPos = thisObj->GetTransform()->GetPosition();
		XMFLOAT3 offset{ ((rand() % 101) / 100.f) * offsetMultiplier,((rand() % 101) / 100.f) * offsetMultiplier, ((rand() % 101) / 100.f) * offsetMultiplier };
		XMFLOAT3 randomRot{ static_cast<float>(rand() % 361),static_cast<float>(rand() % 361) ,static_cast<float>(rand() % 361) };
		pBolt->GetTransform()->Translate(thisPos.x + offset.x, thisPos.y + offset.y, thisPos.z + offset.z);
		pBolt->GetTransform()->Rotate(randomRot.x, randomRot.y, randomRot.z);
	}

	thisObj->SetMarkForDestroy();
}
