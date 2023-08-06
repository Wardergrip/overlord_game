#include "stdafx.h"
#include "BoltPrefab.h"
#include "Materials/ColorMaterial.h"
#include "Components/ScoreComponent.h"
#include "Components/BoltComponent.h"
#include "Managers/SoundManager.h"
#include "Components/DelayedFuncComponent.h"
#include <functional>

BoltPrefab::BoltPrefab(GameObject* pPlayer)
	:m_pPlayer{pPlayer}
{
}

void BoltPrefab::Initialize(const SceneContext&)
{
	AddComponent(new BoltComponent(m_pPlayer));

	constexpr float scale{ 0.2f };

	auto pColMat = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	pColMat->SetColor(DirectX::XMFLOAT4{ DirectX::Colors::Orange });
	auto pBoltModel = AddComponent(new ModelComponent(L"Meshes/Bolt.ovm", false));
	pBoltModel->SetMaterial(pColMat);

	GetTransform()->Scale(scale);
}
