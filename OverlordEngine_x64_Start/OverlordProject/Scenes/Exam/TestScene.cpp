#include "stdafx.h"
#include "TestScene.h"
#include "Materials/ColorMaterial.h"
#include "Materials/DiffuseMaterial.h"


void TestScene::Initialize()
{
	//auto& physX{ PxGetPhysics() };
	//auto pPhysMat{ physX.createMaterial(0.5f, 0.5f, 0.5f) };

	auto pLevel = new GameObject();
	AddChild(pLevel);
	auto pModel = pLevel->AddComponent(new ModelComponent(L"Meshes/Aridia.ovm"));

	constexpr UINT8 amountSubmeshes{ 205 };
	std::wstringstream filePath;
	for (UINT8 submeshid{ 0 }; submeshid < amountSubmeshes; ++submeshid)
	{
		filePath.clear();
		filePath << L"Textures/Aridia/" << std::to_wstring(221 + submeshid) << L".png";
		auto pMat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
		pMat->SetDiffuseTexture(filePath.str());
		pModel->SetMaterial(pMat,submeshid);
	}
}
