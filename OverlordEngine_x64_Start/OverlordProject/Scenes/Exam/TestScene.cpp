#include "stdafx.h"
#include "TestScene.h"
#include "Materials/ColorMaterial.h"
#include "Materials/DiffuseMaterial_Shadow_Skinned.h"
#include "Materials/DiffuseMaterial_Shadow.h"
#include "Materials/DiffuseMaterial.h"
#include "Materials/SkyBoxMaterial.h"
#include "Components/CharacterComponent.h"
#include "Components/CharacterAnimControllerComponent.h"
#include "Components/TextComponent.h"
#include "Prefabs/CubePrefab.h"
#include "Components/BoltsBoxComponent.h"
#include "Prefabs/BoltPrefab.h"
#include "Components/ScoreComponent.h"
#include "Components/WeaponComponent.h"
#include "Materials/Post/PostPixelated.h"
#include "Components/AutokillComponent.h"

#define ENABLE_POSTPROCESSING
//#define ENABLE_BACKGROUNDMUSIC

void TestScene::Initialize()
{
	m_LightDirection = { 0.740129888f, -0.597205281f, 0.309117377f };
	m_LightOffset = { 0.f,0.f,0.f };
	m_ShadowMapNear = 0.1f;
	m_ShadowMapFar = 500.f;

	m_DrawShadowMap = false;
	m_pPlayer = nullptr;
	m_pCameraComp = nullptr;
	m_pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);

	m_SceneContext.settings.enableOnGUI = true;

	//auto& physX{ PxGetPhysics() };
	auto pFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/Consolas_32.fnt");

	AddLevelVisual();
	AddLevelHitbox();

	auto boltsHudObj = AddChild(new GameObject());
	boltsHudObj->AddComponent(new SpriteComponent(L"Textures/BoltsHUD.png", DirectX::XMFLOAT2{1.f,0.f}));
	boltsHudObj->GetTransform()->Translate(m_SceneContext.windowWidth, 0, .9f);

	auto boltsAmountObj = AddChild(new GameObject());
	auto boltText = boltsAmountObj->AddComponent(new TextComponent(pFont, L"0", DirectX::XMFLOAT2{m_SceneContext.windowWidth - 200, 10}, DirectX::XMFLOAT4{251 / 255.f, 218.f / 255.f, 127 / 255.f, 1.f}));

	AddPlayerToScene(boltText);
	AddFlagToScene();

	AddBoxToScene(XMVECTOR{ 3.4f, -1.f, 14.4f });
	AddBoxToScene(XMVECTOR{ 36.8f, -2.1f, 8.8f });
	AddBoxToScene(XMVECTOR{ 57.8f, -2.1f, -27.8f });
	AddBoxToScene(XMVECTOR{ 95.3f, -2.1f, -22.8f });
	AddBoxToScene(XMVECTOR{ 66.9f, 1.7f, -55.3f });
	AddBoxToScene(XMVECTOR{ 23.6f, 3.9f, -33.f });
	AddBoxToScene(XMVECTOR{ 57.725f, -2.1f, -62.2f });

	auto pSkyBox = AddChild(new GameObject());
	auto pSkyBoxModel = pSkyBox->AddComponent(new ModelComponent(L"Meshes/SkyBoxModel.ovm"));
	auto pSkyBoxDiff = MaterialManager::Get()->CreateMaterial<SkyBoxMaterial>();
	pSkyBoxDiff->SetSkyBoxTexture(L"Textures/SkyDawn.dds");
	pSkyBoxModel->SetMaterial(pSkyBoxDiff);

	m_pTagbox = AddChild(new CubePrefab());
	m_BoneTransformIdx = 0;
	m_pTagbox->GetTransform()->Scale(0.1f);

	//AddChild(new BoltPrefab(m_pPlayer))->GetTransform()->Translate(0, 10, 10);

#ifdef ENABLE_BACKGROUNDMUSIC
	const auto pFmod{ SoundManager::Get()->GetSystem() };
	std::string filePath{ "Resources/Music/RnC3_Veldin_Kyzil_Plateau.mp3" };
	pFmod->createStream(filePath.c_str(), FMOD_DEFAULT, nullptr, &m_pMusic);
	pFmod->playSound(m_pMusic, nullptr, false, &m_pChannel);
#endif

#ifdef ENABLE_POSTPROCESSING
	// POST PROCESSING
	auto pPostPixelated = MaterialManager::Get()->CreateMaterial<PostPixelated>();
	const float windowWidth{ 1280 };
	const float windowHeight{ 720 };
	const float scaleFactor{ 0.45f };
	pPostPixelated->SetCollRow(windowWidth * scaleFactor, windowHeight * scaleFactor);
	AddPostProcessingEffect(pPostPixelated);
#endif
}

void TestScene::Update()
{
	XMFLOAT3 pos = m_pPlayer->GetTransform()->GetPosition();
	pos.x += m_LightOffset.x;
	pos.y += m_LightOffset.y;
	pos.z += m_LightOffset.z;
	m_SceneContext.pLights->SetDirectionalLight(pos, m_LightDirection);
}

void TestScene::OnGUI()
{
	if (m_pCharComp) m_pCharComp->DrawImGui();
	ImGui::DragInt("BoneTransformIdx", &m_BoneTransformIdx, 1.0f, 0, static_cast<int>(m_pRatchetModel->GetAnimator()->GetBoneTransforms().size() - 1));
	auto x = m_pRatchetModel->GetAnimator()->GetBoneTransforms()[m_BoneTransformIdx](4,1) /*+ m_pRatchedModel->GetTransform()->GetWorldPosition().x*/;
	auto y = m_pRatchetModel->GetAnimator()->GetBoneTransforms()[m_BoneTransformIdx](4,2) /*+ m_pRatchedModel->GetTransform()->GetWorldPosition().y*/;
	auto z = m_pRatchetModel->GetAnimator()->GetBoneTransforms()[m_BoneTransformIdx](4,3) /*+ m_pRatchedModel->GetTransform()->GetWorldPosition().z*/;
	m_pTagbox->GetTransform()->Translate(x,y,z);

	auto playerPos = m_pPlayer->GetTransform()->GetPosition();
	ImGui::DragFloat("playX", &playerPos.x);
	ImGui::DragFloat("playY", &playerPos.y);
	ImGui::DragFloat("playZ", &playerPos.z);

	ImGui::DragFloat("playX", &playerPos.x);
	ImGui::DragFloat("playY", &playerPos.y);
	ImGui::DragFloat("playZ", &playerPos.z);
	
	/*ImGui::DragFloat("lightX", &m_LightOffset.x);
	ImGui::DragFloat("lightY", &m_LightOffset.y);
	ImGui::DragFloat("lightZ", &m_LightOffset.z);
	ImGui::DragFloat("lightDirX", &m_LightDirection.x,0.01f,-1.f,1.f);
	ImGui::DragFloat("lightDirY", &m_LightDirection.y,0.01f,-1.f,1.f);
	ImGui::DragFloat("lightDirZ", &m_LightDirection.z,0.01f,-1.f,1.f);
	ImGui::DragFloat("Near plane", &m_ShadowMapNear);
	ImGui::DragFloat("Far plane", &m_ShadowMapFar);*/

	ImGui::Checkbox("Draw ShadowMap", &m_DrawShadowMap);
	ImGui::SliderFloat("ShadowMap Scale", &m_ShadowMapScale, 0.f, 1.f);
}

void TestScene::PostDraw()
{
	ShadowMapRenderer::Get()->SetNearplane(m_ShadowMapNear).SetFarplane(m_ShadowMapFar);
	if (m_DrawShadowMap) 
	{
		ShadowMapRenderer::Get()->Debug_DrawDepthSRV({ m_SceneContext.windowWidth - 10.f, 10.f }, { m_ShadowMapScale, m_ShadowMapScale }, { 1.f,0.f });
	}
}

void TestScene::AddPlayerToScene(TextComponent* pBoltsTextComp)
{

	//Ground Plane	
	//GameSceneExt::CreatePhysXGroundPlane(*this, m_pDefaultMaterial);

	//Character
	CharacterDesc characterDesc{ m_pDefaultMaterial };
	characterDesc.actionId_MoveForward = CharacterMoveForward;
	characterDesc.actionId_MoveBackward = CharacterMoveBackward;
	characterDesc.actionId_MoveLeft = CharacterMoveLeft;
	characterDesc.actionId_MoveRight = CharacterMoveRight;
	characterDesc.actionId_Jump = CharacterJump;
	characterDesc.actionId_Melee = CharacterMelee;

	m_pPlayer = AddChild(new GameObject());
	m_pPlayer->SetTag(L"Player");
	m_pPlayer->AddComponent(new ScoreComponent(pBoltsTextComp));
	m_pCharComp = m_pPlayer->AddComponent(new CharacterComponent(characterDesc));
	m_pPlayer->GetTransform()->Translate(25, 1, 4);
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

	inputAction = InputAction(CharacterMelee, InputState::pressed, 'G');
	m_SceneContext.pInput->AddInputAction(inputAction);

	// Model
	auto pRatchet = new GameObject();
	m_pPlayer->AddChild(pRatchet);
	auto pRatchetModel = pRatchet->AddComponent(new ModelComponent(L"Meshes/Ratchet/RatchetFixedAnims.ovm"));
	auto pRatchetMainDiff = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow_Skinned>();
	auto pRatchetSubDiff_1 = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow_Skinned>();
	auto pRatchetSubDiff_2 = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow_Skinned>();
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
	//const std::vector<XMFLOAT4X4>& r = pRatchetModel->GetAnimator()->GetBoneTransforms();
	m_pRatchetModel = pRatchetModel;
}

GameObject* TestScene::AddBoxToScene(const DirectX::XMVECTOR& pos, bool debugTimer)
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

	auto boltsComp = pBoxObj->AddComponent(new BoltsBoxComponent(m_pPlayer));
	if (debugTimer) boltsComp->StartDebugTimer();

	return pBoxObj;
}

void TestScene::AddLevelVisual()
{
	auto pLevel = new GameObject();
	AddChild(pLevel);
	auto pModel = pLevel->AddComponent(new ModelComponent(L"Meshes/Aridia.ovm"));
	pLevel->GetTransform()->Translate(-15.f, 0, 35.f);

	constexpr UINT8 amountSubmeshes{ 205 };
	for (UINT8 submeshid{ 0 }; submeshid < amountSubmeshes; ++submeshid)
	{
		std::wstringstream filePath;
		filePath << L"Textures/Aridia/" << std::to_wstring(221 + submeshid) << L".png";
		auto pMat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
		pMat->SetDiffuseTexture(filePath.str());
		pModel->SetMaterial(pMat, submeshid);
	}
}
void TestScene::AddFlagToScene()
{
	constexpr float scale = 0.05f;

	auto pFlag = AddChild(new GameObject());
	pFlag->GetTransform()->Scale(scale);
	pFlag->AddComponent(new WeaponComponent(m_pRatchetModel, 22));
	auto pFlagModel = pFlag->AddComponent(new ModelComponent(L"Meshes/Flag.ovm"));
	auto pFlagDiff = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pFlagDiff->SetDiffuseTexture(L"Textures/RedFlag.png");
	pFlagModel->SetMaterial(pFlagDiff);
}

void TestScene::AddLevelHitbox()
{
	auto pLevelHitboxObj = new GameObject();
	AddChild(pLevelHitboxObj);
	const auto pPxTriangleMesh = ContentManager::Load<PxTriangleMesh>(L"Meshes/AridiaPlatformV2.ovpt");
	auto levelRb = pLevelHitboxObj->AddComponent(new RigidBodyComponent(true));
	levelRb->AddCollider(PxTriangleMeshGeometry(pPxTriangleMesh, PxMeshScale({ 1.0f, 1.0f, 1.0f })), *m_pDefaultMaterial);
	pLevelHitboxObj->GetTransform()->Translate(-15.f, 0, 35.f);
}
