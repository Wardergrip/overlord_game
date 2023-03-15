#include "stdafx.h"
#include "DiffuseMaterial.h"

DiffuseMaterial::DiffuseMaterial()
	:Material<DiffuseMaterial>(L"Effects/PosNormTex3d.fx")
{
}

void DiffuseMaterial::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
	SetVariable_Texture(L"gDiffuseMap", m_pDiffuseTexture->GetShaderResourceView());
}

void DiffuseMaterial::InitializeEffectVariables()
{
}
