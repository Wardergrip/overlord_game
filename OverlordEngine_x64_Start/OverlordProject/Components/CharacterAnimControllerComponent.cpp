#include "stdafx.h"
#include "CharacterAnimControllerComponent.h"

#include "Components/CharacterComponent.h"
#include "Components/ModelComponent.h"
#include "Misc/AnimationState.h"
#include "Misc/IdleAnimationState.h"
#include "Misc/JumpAnimationState.h"
#include "Misc/RunforwardAnimationState.h"

CharacterAnimControllerComponent::CharacterAnimControllerComponent(CharacterComponent* pCharacter, ModelAnimator* pModelAnim)
	:m_pCharacter{pCharacter}
	,m_pModelAnim{pModelAnim}
	,m_LastAnimationClip{-1}
	,m_pCurrentAnimationState{}
	,m_pIdleAnimationState{new IdleAnimationState(this)}
	,m_pJumpAnimationState{new JumpAnimationState(this)}
	,m_pRunforwardAnimationState{new RunforwardAnimationState(this)}
{
	m_pCurrentAnimationState = GetIdleAnimState();
	m_pCurrentAnimationState->OnEnter();
}

void CharacterAnimControllerComponent::Initialize(const SceneContext&)
{
}

void CharacterAnimControllerComponent::Update(const SceneContext&)
{

	auto previousState = m_pCurrentAnimationState;
	auto newState = m_pCurrentAnimationState->OnHandle();
	if (newState == previousState) return;
	previousState->OnExit();
	m_pCurrentAnimationState = newState;
	m_pCurrentAnimationState->OnEnter();

	//const auto& vel = m_pCharacter->GetTotalVelocity();
	//if (std::abs(vel.y) > 0.15f)
	//{
	//	SetAnimationClip(Jump);
	//	//std::cout << vel.y << '\n';
	//}
	//else if (std::abs(vel.x) > FLT_EPSILON || std::abs(vel.z) > FLT_EPSILON)
	//{
	//	SetAnimationClip(RunForward);
	//}
	//else
	//{
	//	SetAnimationClip(Idle);
	//}
}

void CharacterAnimControllerComponent::SetAnimationClip(AnimationClipId id, bool isReversed, float speed)
{
	if (id == m_LastAnimationClip && isReversed == m_LastIsReverse) return;
	m_LastAnimationClip = id;
	m_LastIsReverse = isReversed;
	m_pModelAnim->SetAnimation(id);
	m_pModelAnim->SetPlayReversed(isReversed);
	m_pModelAnim->SetAnimationSpeed(speed);
	m_pModelAnim->Play();
	std::cout << "Changing animationclip id\n";
}
