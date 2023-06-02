#pragma once
class MenuScene : public GameScene
{
public:
	MenuScene() : GameScene(L"MenuScene") {}
	~MenuScene() override = default;

	MenuScene(const MenuScene& other) = delete;
	MenuScene(MenuScene&& other) noexcept = delete;
	MenuScene& operator=(const MenuScene& other) = delete;
	MenuScene& operator=(MenuScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	/*void Draw() override; */
	void OnGUI() override;

private:
	GameObject* m_pPlayButton;
	GameObject* m_pExitButton;
	GameObject* pPlayButtonSprite;
	GameObject* pExitButtonSprite;
};

