#include "stdafx.h"
#include "SkyBoxMaterial.h"

SkyBoxMaterial::SkyBoxMaterial()
	: Material{L"Effects/SkyBox.fx"}
{
}

void SkyBoxMaterial::SetSkyBoxTexture(const std::wstring& assetFile)
{
	auto SRV = ContentManager::Load<TextureData>(assetFile)->GetShaderResourceView();
	SetVariable_Texture(L"gCubeMap", SRV);
}

void SkyBoxMaterial::InitializeEffectVariables()
{
}

void SkyBoxMaterial::OnUpdateModelVariables(const SceneContext& , const ModelComponent* ) const
{
}
