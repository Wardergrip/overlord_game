#pragma once
#include "Components/BaseComponent.h"
class AutokillComponent final : public BaseComponent
{
public:
	AutokillComponent(float seconds = 1.f)
		:BaseComponent()
		,m_Timer{seconds}
	{
	}
	~AutokillComponent() = default;

	AutokillComponent(AutokillComponent&& other) = delete;
	AutokillComponent(const AutokillComponent& other) = delete;
	const AutokillComponent& operator=(AutokillComponent&& other) = delete;
	const AutokillComponent& operator=(const AutokillComponent& other) = delete;

protected:
	void Initialize(const SceneContext& /*sceneContext*/) override {}
	void Update(const SceneContext& sceneContext) override
	{
		m_Timer -= sceneContext.pGameTime->GetElapsed();
		if (m_Timer <= 0.f)
		{
			GetGameObject()->SetMarkForDestroy();
		}
	}

private:
	float m_Timer;
};