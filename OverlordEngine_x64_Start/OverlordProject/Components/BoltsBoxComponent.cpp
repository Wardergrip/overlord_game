#include "stdafx.h"
#include "BoltsBoxComponent.h"

void BoltsBoxComponent::Initialize(const SceneContext& /*sceneContext*/)
{
	/*GetGameObject()->SetOnTriggerCallBack([&](GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action)
	{
		if (pOtherObject->GetTag() == L"Weapon")
		{
			BreakSequence();
		}
	});*/
}

void BoltsBoxComponent::BreakSequence()
{
	auto obj = GetGameObject();
	auto scene = obj->GetScene();

	//Particle System
	ParticleEmitterSettings settings{};
	settings.velocity = { 0.f,6.f,0.f };
	settings.minSize = 1.f;
	settings.maxSize = 2.f;
	settings.minEnergy = 1.f;
	settings.maxEnergy = 2.f;
	settings.minScale = 3.5f;
	settings.maxScale = 5.5f;
	settings.minEmitterRadius = .2f;
	settings.maxEmitterRadius = .5f;
	settings.color = { 1.f,1.f,1.f, .6f };

	const auto pObject = scene->AddChild(new GameObject);
	pObject->AddComponent(new ParticleEmitterComponent(L"Textures/Smoke.png", settings, 200));
	scene->RemoveChild(obj, true);
}
