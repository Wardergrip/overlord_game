#include "stdafx.h"
#include "TestScene.h"
#include "Materials/ColorMaterial.h"
#include "Materials/DiffuseMaterial_Skinned.h"
#include "Materials/DiffuseMaterial_Shadow.h"
#include "Materials/DiffuseMaterial.h"
#include "Components/CharacterComponent.h"
#include "Components/CharacterAnimControllerComponent.h"
#include "Components/TextComponent.h"

void TestScene::Initialize()
{
	m_pPlayer = nullptr;
	m_pCameraComp = nullptr;
	m_pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);

	m_SceneContext.settings.enableOnGUI = true;

	//auto& physX{ PxGetPhysics() };
	auto pFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/Consolas_32.fnt");

	//AddLevelVisual();
	//AddLevelHitbox();

	AddPlayerToScene();

	auto boltsHudObj = AddChild(new GameObject());
	boltsHudObj->AddComponent(new SpriteComponent(L"Textures/BoltsHUD.png", DirectX::XMFLOAT2{1.f,0.f}));
	boltsHudObj->GetTransform()->Translate(m_SceneContext.windowWidth, 0, .9f);

	auto boltsAmountObj = AddChild(new GameObject());
	boltsAmountObj->AddComponent(new TextComponent(pFont, L"000000", DirectX::XMFLOAT2{m_SceneContext.windowWidth - 400, 0}, DirectX::XMFLOAT4{251 / 255.f, 218.f / 255.f, 127 / 255.f, 1.f}));

	AddBoxToScene(XMVECTOR{ 0,10,0 });

	/*auto pSkyBox = AddChild(new GameObject());
	pSkyBox->GetTransform()->Scale(1000.f);
	auto pSkyBoxModel = pSkyBox->AddComponent(new ModelComponent(L"Meshes/SkyBox.ovm"));
	auto pSkyBoxDiff = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pSkyBoxDiff->SetDiffuseTexture(L"Textures/RC_SkyBox.png");
	pSkyBoxModel->SetMaterial(pSkyBoxDiff);*/
}

void TestScene::OnGUI()
{
	if (m_pCharComp) m_pCharComp->DrawImGui();
}

void TestScene::AddPlayerToScene()
{

	//Ground Plane	
	GameSceneExt::CreatePhysXGroundPlane(*this, m_pDefaultMaterial);

	//Character
	CharacterDesc characterDesc{ m_pDefaultMaterial };
	characterDesc.actionId_MoveForward = CharacterMoveForward;
	characterDesc.actionId_MoveBackward = CharacterMoveBackward;
	characterDesc.actionId_MoveLeft = CharacterMoveLeft;
	characterDesc.actionId_MoveRight = CharacterMoveRight;
	characterDesc.actionId_Jump = CharacterJump;

	m_pPlayer = AddChild(new GameObject());
	m_pCharComp = m_pPlayer->AddComponent(new CharacterComponent(characterDesc));
	m_pPlayer->GetTransform()->Translate(0.f, 5.f, 0.f);
	m_pCharComp->GetCharacterCamera()->GetTransform()->Translate(DirectX::XMVECTOR{0, 5, -10.f});

	//Input
	auto inputAction = InputAction(CharacterMoveLeft, InputState::down, 'A');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterMoveRight, InputState::down, 'D');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterMoveForward, InputState::down, 'W');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterMoveBackward, InputState::down, 'S');
	m_SceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(CharacterJump, InputState::pressed, VK_SPACE, -1, XINPUT_GAMEPAD_A);
	m_SceneContext.pInput->AddInputAction(inputAction);

	// Model
	auto pRatchet = new GameObject();
	m_pPlayer->AddChild(pRatchet);
	auto pRatchetModel = pRatchet->AddComponent(new ModelComponent(L"Meshes/Ratchet/RatchetFixedAnims.ovm"));
	auto pRatchetMainDiff = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	auto pRatchetSubDiff_1 = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	auto pRatchetSubDiff_2 = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	pRatchetMainDiff->SetDiffuseTexture(L"Textures/Adamantine/Texture0.png");
	pRatchetSubDiff_1->SetDiffuseTexture(L"Textures/Adamantine/Texture1.png");
	pRatchetSubDiff_2->SetDiffuseTexture(L"Textures/Adamantine/Texture2.png");
	pRatchetModel->SetMaterial(pRatchetMainDiff, 0);
	pRatchetModel->SetMaterial(pRatchetSubDiff_1, 1);
	pRatchetModel->SetMaterial(pRatchetSubDiff_2, 2);

	pRatchet->GetTransform()->Scale(0.05f);
	pRatchet->GetTransform()->Translate(0, -1.2f, 0);
	pRatchet->GetTransform()->Rotate(0, 180, 0);

	pRatchet->AddComponent(new CharacterAnimControllerComponent(m_pCharComp, pRatchetModel->GetAnimator()));
}

void TestScene::AddBoxToScene(const DirectX::XMVECTOR& pos)
{
	static auto pBoxMat = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.f);
	constexpr float scale = 0.05f;
	constexpr float triggerScale = 0.06f;

	auto pBoxObj = AddChild(new GameObject());
	pBoxObj->GetTransform()->Translate(pos);
	pBoxObj->GetTransform()->Scale(scale);

	auto pBoxModel = pBoxObj->AddComponent(new ModelComponent(L"Meshes/WeaponCrate.ovm"));
	auto pBoxDiff = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pBoxDiff->SetDiffuseTexture(L"Textures/Mystery.png");
	pBoxModel->SetMaterial(pBoxDiff);

	const auto pPxConvexMesh = ContentManager::Load<PxConvexMesh>(L"Meshes/WeaponCrate.ovpc");
	auto boxRb = pBoxObj->AddComponent(new RigidBodyComponent());
	boxRb->AddCollider(PxConvexMeshGeometry{ pPxConvexMesh,PxMeshScale({ scale,scale,scale })}, *pBoxMat);
	boxRb->AddCollider(PxConvexMeshGeometry{ pPxConvexMesh,PxMeshScale({triggerScale,triggerScale,triggerScale}) }, *pBoxMat, true);
}

void TestScene::AddLevelVisual()
{
	auto pLevel = new GameObject();
	AddChild(pLevel);
	auto pModel = pLevel->AddComponent(new ModelComponent(L"Meshes/Aridia.ovm"));

	constexpr UINT8 amountSubmeshes{ 205 };
	for (UINT8 submeshid{ 0 }; submeshid < amountSubmeshes; ++submeshid)
	{
		std::wstringstream filePath;
		filePath << L"Textures/Aridia/" << std::to_wstring(221 + submeshid) << L".png";
		auto pMat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
		pMat->SetDiffuseTexture(filePath.str());
		pModel->SetMaterial(pMat, submeshid);
	}
}

void TestScene::AddLevelHitbox()
{
	auto pLevelHitboxObj = new GameObject();
	AddChild(pLevelHitboxObj);
	const auto pPxTriangleMesh = ContentManager::Load<PxTriangleMesh>(L"Meshes/AridiaPlatformV2.ovpt");
	auto levelRb = pLevelHitboxObj->AddComponent(new RigidBodyComponent(true));
	levelRb->AddCollider(PxTriangleMeshGeometry(pPxTriangleMesh, PxMeshScale({ .5f,.5f,.5f })), *m_pDefaultMaterial);
}
