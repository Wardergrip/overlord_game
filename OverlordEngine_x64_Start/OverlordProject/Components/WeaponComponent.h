#pragma once
#include "Components/BaseComponent.h"
#include "Components/ModelComponent.h"

class WeaponComponent final : public BaseComponent
{
public:
	WeaponComponent(ModelComponent* pRatchetModel, int boneIdx)
		:m_pRatchetModel{pRatchetModel}
		,m_BoneTransformRef{ pRatchetModel->GetAnimator()->GetBoneTransforms() }
		,m_BoneIdx{boneIdx}
	{
	}
	virtual ~WeaponComponent() = default;

	WeaponComponent(const WeaponComponent& other) = delete;
	WeaponComponent(WeaponComponent&& other) noexcept = delete;
	WeaponComponent& operator=(const WeaponComponent& other) = delete;
	WeaponComponent& operator=(WeaponComponent&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& /*sceneContext*/)
	{
	}

	void Update(const SceneContext& /*sceneContext*/) override
	{
		static const DirectX::XMFLOAT3 offset{-0.5f, 0.5f, -0.1f};
		const auto x = m_BoneTransformRef[m_BoneIdx](4, 1);
		const auto y = m_BoneTransformRef[m_BoneIdx](4, 2);
		const auto z = m_BoneTransformRef[m_BoneIdx](4, 3);
		const auto& posRatched = m_pRatchetModel->GetTransform()->GetWorldPosition();

		GetGameObject()->GetTransform()->Translate(offset.x + x + posRatched.x, offset.y + y + posRatched.y, offset.z + z + posRatched.z);
	}

private:
	ModelComponent* m_pRatchetModel;
	const std::vector<XMFLOAT4X4>& m_BoneTransformRef;
	int m_BoneIdx;
};