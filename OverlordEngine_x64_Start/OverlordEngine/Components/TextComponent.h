#pragma once
class TextComponent : public BaseComponent
{
public:
	TextComponent(SpriteFont* pFont, const std::wstring& text, const XMFLOAT2& pos = {}, const XMFLOAT4& color = {1.f,1.f,1.f,1.f});
	~TextComponent() override = default;

	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) noexcept = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) noexcept = delete;

	TextComponent* SetFont(SpriteFont* pFont);
	TextComponent* SetText(const std::wstring& text);
	TextComponent* SetPos(const XMFLOAT2& pos);
	TextComponent* SetColor(const XMFLOAT4& color);

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Draw(const SceneContext& sceneContext) override;

private:
	SpriteFont* m_pFont;
	std::wstring m_Text;
	XMFLOAT2 m_TextPosition;
	XMFLOAT4 m_TextColor;
};

