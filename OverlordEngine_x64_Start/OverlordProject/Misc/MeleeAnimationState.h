#pragma once
#include "AnimationState.h"
#include "Prefabs/CubePrefab.h"
#include "Components/AutokillComponent.h"
#include "Components/BoltsBoxComponent.h"

class MeleeAnimationState final : public AnimationState
{

public:
	MeleeAnimationState(CharacterAnimControllerComponent* pCharAnimControllerComp)
		:AnimationState(pCharAnimControllerComp)
		,m_Timer{}
		,m_MaxTimer{ 2.433f * 0.5f }
	{
		m_Timer = m_MaxTimer;
	}
	virtual ~MeleeAnimationState() = default;

	MeleeAnimationState(MeleeAnimationState&& other) = delete;
	MeleeAnimationState(const MeleeAnimationState& other) = delete;
	const MeleeAnimationState& operator=(MeleeAnimationState&& other) = delete;
	const MeleeAnimationState& operator=(const MeleeAnimationState& other) = delete;

	virtual void OnEnter() override
	{
		m_pCharAnim->SetAnimationClip(CharacterAnimControllerComponent::Melee, false, m_MaxTimer);
		m_pCharAnim->GetCharacterComponent()->SetAllowInput(false);

		// Hitbox
		constexpr float hitboxDistance{ 2.f };
		constexpr float hitboxTime{ 1.f };
		const PxVec3 hitboxScale{ 3.f,1.f,3.f };
		auto pHitboxMat = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.f);
		auto hitboxObj = m_pCharAnim->GetScene()->AddChild(new GameObject(/*XMFLOAT3{1.f,1.f,1.f}*/));
		hitboxObj->AddComponent(new AutokillComponent(hitboxTime));
		auto hitboxRb = hitboxObj->AddComponent(new RigidBodyComponent());
		hitboxRb->SetKinematic(true);
		hitboxRb->AddCollider(PxBoxGeometry{hitboxScale}, *pHitboxMat, true);

		hitboxObj->SetOnTriggerCallBack([&](GameObject* /*pTriggerObject*/, GameObject* pOtherObject, PxTriggerAction /*action*/)
			{
				auto bbc = pOtherObject->GetComponent<BoltsBoxComponent>();
				if (pOtherObject->GetTag() == L"Boltsbox")
				{
					bbc->BreakSequence();
				}
			});

		const auto& forward = m_pCharAnim->GetCharacterComponent()->GetTransform()->GetForward();
		auto pos = m_pCharAnim->GetCharacterComponent()->GetTransform()->GetPosition();
		pos.x += forward.x * hitboxDistance;
		pos.y += forward.y * hitboxDistance;
		pos.z += forward.z * hitboxDistance;
		hitboxObj->GetTransform()->Translate(pos);

		// SFX
		const auto pFmod{ SoundManager::Get()->GetSystem() };
		FMOD::Channel* pChannel{};
		FMOD::Sound* pSwingSound{};
		std::string sfxFilepath;
		int random{ rand() % 3 };
		switch (random)
		{
		case 0:
			sfxFilepath = "Resources/SFX/SwingSFX_0.mp3";
			break;
		case 1:
			sfxFilepath = "Resources/SFX/SwingSFX_1.mp3";
			break;
		case 2:
			sfxFilepath = "Resources/SFX/SwingSFX_2.mp3";
			break;
		}
		pFmod->createStream(sfxFilepath.c_str(), FMOD_DEFAULT, nullptr, &pSwingSound);
		pFmod->playSound(pSwingSound, nullptr, false, &pChannel);
		pChannel->setVolume(1.f);
	}
	virtual AnimationState* OnHandle(const SceneContext& sceneContext) override
	{
		m_Timer -= sceneContext.pGameTime->GetElapsed();
		if (m_Timer <= 0.f)
		{
			return m_pCharAnim->GetIdleAnimState();
		}
		return this;
	}
	virtual void OnExit() override
	{
		m_Timer = m_MaxTimer;
		m_pCharAnim->GetCharacterComponent()->SetAllowInput(true);
	}

private:
	float m_Timer;
	const float m_MaxTimer;
};