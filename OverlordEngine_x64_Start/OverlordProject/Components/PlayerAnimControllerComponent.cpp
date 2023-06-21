#include "stdafx.h"
#include "PlayerAnimControllerComponent.h"

#include "Prefabs/Character.h"

PlayerAnimControllerComponent::PlayerAnimControllerComponent(Character* pCharacter)
	:m_pCharacter{pCharacter}
{
}

void PlayerAnimControllerComponent::Initialize(const SceneContext& sceneContext)
{
}

void PlayerAnimControllerComponent::Update(const SceneContext& sceneContext)
{
}
