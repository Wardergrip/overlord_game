#pragma once
class BoltPrefab final : public GameObject
{
public:
	BoltPrefab(GameObject* pPlayer);
	~BoltPrefab() override = default;
	BoltPrefab(const BoltPrefab& other) = delete;
	BoltPrefab(BoltPrefab&& other) noexcept = delete;
	BoltPrefab& operator=(const BoltPrefab& other) = delete;
	BoltPrefab& operator=(BoltPrefab&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext&) override;

private:
	FMOD::Sound* m_pPickupSound{ nullptr };
	FMOD::Channel* m_pChannel{ nullptr };
};

