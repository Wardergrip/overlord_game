#pragma once

#include "Misc/Material.h"
class SkyBoxMaterial : public Material<SkyBoxMaterial>
{
public:
	SkyBoxMaterial();
	SkyBoxMaterial(const SkyBoxMaterial&) = delete;
	SkyBoxMaterial& operator=(const SkyBoxMaterial&) = delete;
	SkyBoxMaterial(SkyBoxMaterial&&) = delete;
	SkyBoxMaterial& operator=(SkyBoxMaterial&&) = delete;
	~SkyBoxMaterial() override = default;

	void SetSkyBoxTexture(const std::wstring& assetFile);

protected:
	void InitializeEffectVariables()override;
	void OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* pModelComponent)const override;
};

