#include "stdafx.h"
#include "BoltComponent.h"

BoltComponent::BoltComponent(GameObject* pPlayer)
	:m_pPlayer{pPlayer}
{
}

void BoltComponent::Initialize(const SceneContext& /*sceneContext*/)
{
	
}

void BoltComponent::Update(const SceneContext& sceneContext)
{
	static auto Sqr = [](float val) { return val * val; };

	constexpr float sqrEngageRadius{ 80.f };

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
}
