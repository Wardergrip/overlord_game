#include "stdafx.h"
#include "TextComponent.h"

TextComponent::TextComponent(SpriteFont* pFont, const std::wstring& text, const XMFLOAT2& pos, const XMFLOAT4& color)
	:m_pFont{pFont}
	,m_Text{text}
	,m_TextPosition{ pos }
	,m_TextColor{ color }
{
	assert(pFont && "No font assigned!");
}

void TextComponent::Initialize(const SceneContext& /*sceneContext*/)
{
}

void TextComponent::Draw(const SceneContext& /*sceneContext*/)
{
	TextRenderer::Get()->DrawText(m_pFont, m_Text, m_TextPosition, m_TextColor);
}

TextComponent* TextComponent::SetFont(SpriteFont* pFont)
{
	assert(pFont && "Font is nullptr!");
	m_pFont = pFont;
	return this;
}

TextComponent* TextComponent::SetText(const std::wstring& text)
{
	m_Text = text;
	return this;
}

TextComponent* TextComponent::SetPos(const XMFLOAT2& pos)
{
	m_TextPosition = pos;
	return this;
}

TextComponent* TextComponent::SetColor(const XMFLOAT4& color)
{
	m_TextColor = color;
	return nullptr;
}
