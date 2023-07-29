#pragma once
#include "Misc/PostProcessingMaterial.h"

class PostPixelated final : public PostProcessingMaterial
{
public:
	PostPixelated();
	~PostPixelated() override = default;
	PostPixelated(const PostPixelated& other) = delete;
	PostPixelated(PostPixelated&& other) noexcept = delete;
	PostPixelated& operator=(const PostPixelated& other) = delete;
	PostPixelated& operator=(PostPixelated&& other) noexcept = delete;

	void SetCollRow(float colls, float rows) const;

protected:
	void Initialize(const GameContext& /*gameContext*/) override {}
};

