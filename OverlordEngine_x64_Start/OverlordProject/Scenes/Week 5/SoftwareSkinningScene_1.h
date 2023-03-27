#pragma once

class BoneObject;

class SoftwareSkinningScene_1 : public GameScene
{
public:
	SoftwareSkinningScene_1() :GameScene(L"SoftwareSkinningScene_1") {}
	~SoftwareSkinningScene_1() override = default;

	SoftwareSkinningScene_1(const SoftwareSkinningScene_1& other) = delete;
	SoftwareSkinningScene_1(SoftwareSkinningScene_1&& other) noexcept = delete;
	SoftwareSkinningScene_1& operator=(const SoftwareSkinningScene_1& other) = delete;
	SoftwareSkinningScene_1& operator=(SoftwareSkinningScene_1&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void OnGUI() override;

private:
	BoneObject* m_pBone0{};
	BoneObject* m_pBone1{};

	bool m_ManualOverride{ false };
	float m_BoneRotation{};
	XMFLOAT3 m_Bone0Rotation{};
	XMFLOAT3 m_Bone1Rotation{};
	
	int m_RotationSign{ 1 };

	const float m_RotSpeed{ 45.f };
	const float m_UpperBound{ 45.f };
	const float m_LowerBound{ -45.f };
};

