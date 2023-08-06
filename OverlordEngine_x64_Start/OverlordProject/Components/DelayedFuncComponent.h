#pragma once
#include <functional>

class DelayedFuncComponent : public BaseComponent
{
public:
	DelayedFuncComponent(std::function<void()>&& func, float delay = 1.f)
		:m_Func{func}
		,m_Timer{delay}
		,m_Done{false}
	{
	}
	virtual ~DelayedFuncComponent() = default;

	DelayedFuncComponent(const DelayedFuncComponent& other) = delete;
	DelayedFuncComponent(DelayedFuncComponent&& other) noexcept = delete;
	DelayedFuncComponent& operator=(const DelayedFuncComponent& other) = delete;
	DelayedFuncComponent& operator=(DelayedFuncComponent&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& /*sceneContext*/) override
	{
	}
	void Update(const SceneContext& sceneContext) override
	{
		if (m_Done) return;

		m_Timer -= sceneContext.pGameTime->GetElapsed();
		if (m_Timer <= 0.f)
		{
			m_Func();
			m_Done = true;
		}
	}

private:
	float m_Timer;
	bool m_Done;
	std::function<void()> m_Func;
};