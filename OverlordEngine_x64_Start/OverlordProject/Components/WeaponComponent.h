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
		constexpr static float INV_TWO_PI{ 1.0f / (2 * static_cast<float>(3.1415926535897932384626433832795028841971693993751058209749445923078164062)) };

		//static const DirectX::XMFLOAT3 offset{-0.5f, 0.5f, -0.1f};
		static const DirectX::XMFLOAT3 offset{0, 0, 0};
		DirectX::XMFLOAT4X4 worldMatrix{ m_BoneTransformRef[m_BoneIdx] };

		// https://math.stackexchange.com/questions/237369/given-this-transformation-matrix-how-do-i-decompose-it-into-translation-rotati
		// Extract position and null them in the matrix
		const float boneX{ worldMatrix(0, 3) };
		worldMatrix(0, 3) = 0;
		const float boneY{ worldMatrix(1, 3) };
		worldMatrix(1, 3) = 0;
		const float boneZ{ worldMatrix(2, 3) };
		worldMatrix(2, 3) = 0;

		// Extract scale
		const float boneSx{ std::sqrtf((worldMatrix(0,0)* worldMatrix(0,0)) + (worldMatrix(1,0)* worldMatrix(1,0)) + (worldMatrix(2,0)* worldMatrix(2,0)))};
		const float boneSy{ std::sqrtf((worldMatrix(0,1)* worldMatrix(0,1)) + (worldMatrix(1,1)* worldMatrix(1,1)) + (worldMatrix(2,1)* worldMatrix(2,1)))};
		const float boneSz{ std::sqrtf((worldMatrix(0,2)* worldMatrix(0,2)) + (worldMatrix(1,2)* worldMatrix(1,2)) + (worldMatrix(2,2)* worldMatrix(2,2)))};

		// Extract rotation
		DirectX::XMFLOAT4X4 rotationMatrix{ worldMatrix };
		rotationMatrix(0, 0) /= boneSx;
		rotationMatrix(1, 0) /= boneSx;
		rotationMatrix(2, 0) /= boneSx;
		rotationMatrix(0, 1) /= boneSy;
		rotationMatrix(1, 1) /= boneSy;
		rotationMatrix(2, 1) /= boneSy;
		rotationMatrix(0, 2) /= boneSz;
		rotationMatrix(1, 2) /= boneSz;
		rotationMatrix(2, 2) /= boneSz;

		//https://learnopencv.com/rotation-matrix-to-euler-angles/
		float sy = sqrt(rotationMatrix(0, 0) * rotationMatrix(0, 0) + rotationMatrix(1, 0) * rotationMatrix(1, 0));
		bool singular = sy < 1e-6; // If
		float xRot, yRot, zRot;
		if (!singular)
		{
			xRot = atan2(rotationMatrix(2, 1), rotationMatrix(2, 2));
			yRot = atan2(-rotationMatrix(2, 0), sy);
			zRot = atan2(rotationMatrix(1, 0), rotationMatrix(0, 0));
		}
		else
		{
			xRot = atan2(-rotationMatrix(1, 2), rotationMatrix(1, 1));
			yRot = atan2(-rotationMatrix(2, 0), sy);
			zRot = 0;
		}
		xRot *= INV_TWO_PI * 360;
		yRot *= INV_TWO_PI * 360;
		zRot *= INV_TWO_PI * 360;

		const auto& posRatched = m_pRatchetModel->GetTransform()->GetWorldPosition();

		GetGameObject()->GetTransform()->Translate(offset.x + boneX + posRatched.x, offset.y + boneY + posRatched.y, offset.z + boneZ + posRatched.z);
		GetGameObject()->GetTransform()->Rotate(xRot, yRot, zRot);
	}

private:
	ModelComponent* m_pRatchetModel;
	const std::vector<XMFLOAT4X4>& m_BoneTransformRef;
	int m_BoneIdx;
};