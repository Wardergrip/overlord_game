#include "stdafx.h"
#include "BoltComponent.h"
#include "ScoreComponent.h"

BoltComponent::BoltComponent(GameObject* pPlayer)
	:m_pPlayer{pPlayer}
{
}

void BoltComponent::Initialize(const SceneContext& /*sceneContext*/)
{
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
}

void BoltComponent::Update(const SceneContext& sceneContext)
{
	static auto Sqr = [](float val) { return val * val; };

	constexpr float sqrEngageRadius{ 80.f };
	constexpr float sqrPickupRadius{ 10.f };

	const auto& playerWorldPos = m_pPlayer->GetTransform()->GetWorldPosition();
	const auto& thisPos = GetTransform()->GetWorldPosition();
	XMFLOAT3 desiredVec{playerWorldPos.x - thisPos.x,playerWorldPos.y - thisPos.y,playerWorldPos.z - thisPos.z };
	const float sqrDistance{ Sqr(desiredVec.x) + Sqr(desiredVec.y) + Sqr(desiredVec.z)};

	if (sqrDistance > sqrEngageRadius)
	{
		return;
	}
	constexpr float speed{ 5.f };

	const float elapsedSec{ sceneContext.pGameTime->GetElapsed() };
	const float invDistance{ 1.f / sqrt(sqrDistance) };
	desiredVec.x *= invDistance * speed * elapsedSec;
	desiredVec.y *= invDistance * speed * elapsedSec;
	desiredVec.z *= invDistance * speed * elapsedSec;
	GetTransform()->Translate(thisPos.x + desiredVec.x, thisPos.y + desiredVec.y, thisPos.z + desiredVec.z);

	if (sqrDistance < sqrPickupRadius)
	{
		m_pPlayer->GetComponent<ScoreComponent>()->AddBolts(1);
		SoundManager::Get()->GetSystem()->playSound(m_pPickupSound, nullptr, false, &m_pChannel);
		m_pChannel->setVolume(1.f);
		GetGameObject()->SetMarkForDestroy();
	}
}
