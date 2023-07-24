#pragma once
#include "Components/CharacterAnimControllerComponent.h"
class AnimationState
{
public:
	AnimationState(CharacterAnimControllerComponent* pCharAnimControllerComp)
		:m_pCharAnim{ pCharAnimControllerComp }
	{
	}
	virtual ~AnimationState() = default;

	AnimationState(AnimationState&& other) = delete;
	AnimationState(const AnimationState& other) = delete;
	const AnimationState& operator=(AnimationState&& other) = delete;
	const AnimationState& operator=(const AnimationState& other) = delete;

	virtual void OnEnter() {}
	virtual AnimationState* OnHandle() { return this; }
	virtual void OnExit() {}
protected:
	CharacterAnimControllerComponent* m_pCharAnim;
};

