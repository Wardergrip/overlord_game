#include "stdafx.h"
#include "MenuScene.h"

#include "Prefabs/CubePrefab.h"
#include "Components/TextComponent.h"

void MenuScene::Initialize()
{
	m_SceneContext.settings.drawGrid = true;
	m_SceneContext.settings.enableOnGUI = true;
	m_SceneContext.settings.drawPhysXDebug = true;

	// Camera
	const auto pFixedCamera = new FixedCamera();
	AddChild(pFixedCamera);
	SetActiveCamera(pFixedCamera->GetComponent<CameraComponent>());
	m_SceneContext.pCamera->GetTransform()->Translate(0, 0, -10);
	m_SceneContext.pCamera->GetTransform()->Rotate(0, 0, 0);

	// Button
	constexpr DirectX::XMFLOAT3 buttonDimensions{3.5f, 1.f, 1.f};
	constexpr float buttonAlpha{ 1.0f };
	const auto pButtonMaterial = PxGetPhysics().createMaterial(.5f, .5f, .5f);
	/*auto*/ pPlayButtonSprite = new GameObject();
	AddChild(pPlayButtonSprite);

	pPlayButtonSprite->AddComponent(new SpriteComponent(L"Textures/BasicButton.png", { 0.5f,0.5f }, { 1.f,1.f,1.f,buttonAlpha }));
	pPlayButtonSprite->GetTransform()->Translate(m_SceneContext.windowWidth / 2.f, m_SceneContext.windowHeight / 2.f, .9f);
	pPlayButtonSprite->GetTransform()->Scale(1.f, 1.f, 1.f);

	m_pPlayButton = new CubePrefab(buttonDimensions);
	AddChild(m_pPlayButton);
	const auto pPlayButtonRigidBody = m_pPlayButton->AddComponent(new RigidBodyComponent(true));
	pPlayButtonRigidBody->AddCollider(PxBoxGeometry{ buttonDimensions.x / 2,buttonDimensions.y / 2,buttonDimensions.z / 2 }, *pButtonMaterial);

	pExitButtonSprite = new GameObject();
	AddChild(pExitButtonSprite);

	pExitButtonSprite->AddComponent(new SpriteComponent(L"Textures/BasicButton.png",{ 0.5f,0.5f }, { 1.f,1.f,1.f,buttonAlpha }));
	pExitButtonSprite->GetTransform()->Translate(m_SceneContext.windowWidth / 2.f, 2 * (m_SceneContext.windowHeight / 3.f), .9f);
	pExitButtonSprite->GetTransform()->Scale(1.f, 1.f, 1.f);

	m_pExitButton = new CubePrefab(buttonDimensions);
	const auto pExitButtonRigidBody = m_pExitButton->AddComponent(new RigidBodyComponent(true));
	pExitButtonRigidBody->AddCollider(PxBoxGeometry{ buttonDimensions.x / 2,buttonDimensions.y / 2,buttonDimensions.z / 2 }, *pButtonMaterial);
	AddChild(m_pExitButton);
	m_pExitButton->GetTransform()->Translate(XMFLOAT3{ 0,-1.35f,0.0f });

	// Background
	auto pBackground{ new GameObject() };
	AddChild(pBackground);

	pBackground->AddComponent(new SpriteComponent(L"Textures/GP2_Exam2023_MainMenu.png", { 0.5f,0.5f }, { 1.f,1.f,1.f,1.0f }));

	pBackground->GetTransform()->Translate(m_SceneContext.windowWidth / 2.f, m_SceneContext.windowHeight / 2.f, .9f);
	pBackground->GetTransform()->Scale(1.f, 1.f, 1.f);

	// Button text
	auto pFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/Consolas_32.fnt");
	auto pPlayText = new GameObject();
	auto pPlayTextComp = AddChild(pPlayText)->AddComponent(new TextComponent(pFont, L"Play"));
	pPlayTextComp->SetPos({ m_SceneContext.windowWidth * 0.5f - 30.f,m_SceneContext.windowHeight * 0.5f - 10.f });

	auto pExitText = new GameObject();
	auto pExitTextComp = AddChild(pExitText)->AddComponent(new TextComponent(pFont, L"Exit"));
	pExitTextComp->SetPos({ m_SceneContext.windowWidth * 0.5f - 30.f,m_SceneContext.windowHeight * 0.5f + 100.f });

#ifdef ENABLE_BACKGROUNDMUSIC
	const auto pFmod{ SoundManager::Get()->GetSystem() };
	std::string filePath{ "Resources/Music/RnC3_Title_Screen.mp3" };
	pFmod->createStream(filePath.c_str(), FMOD_DEFAULT, nullptr, &m_pMusic);
	pFmod->playSound(m_pMusic, nullptr, false, &m_pChannel);
#endif
}

void MenuScene::Update()
{
	if (InputManager::IsMouseButton(InputState::pressed, VK_LBUTTON))
	{
		if (const auto pPickedObject = m_SceneContext.pCamera->Pick())
		{
			if (pPickedObject == m_pPlayButton)
			{
				SceneManager::Get()->NextScene();
			}
			else if (pPickedObject == m_pExitButton)
			{
				OverlordGame::SHOULD_EXIT = true;
			}
		}
	}
}

void MenuScene::OnGUI()
{
	/*if (ImGui::Button("hide/unhide"))
	{
		if (pPlayButtonSprite->GetScene())
		{
			RemoveChild(pPlayButtonSprite);
			RemoveChild(pExitButtonSprite);
		}
		else
		{
			AddChild(pPlayButtonSprite);
			AddChild(pExitButtonSprite);
		}
	}*/
}
