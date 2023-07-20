#include "stdafx.h"
#include "ScoreComponent.h"
#include "Components/TextComponent.h"
#include <sstream>

ScoreComponent::ScoreComponent(TextComponent* pBoltsTextComp)
	:m_Bolts{0}
	,m_pBoltsTextComp{pBoltsTextComp}
{
}

void ScoreComponent::AddBolts(int bolts)
{
	m_Bolts += bolts;
	std::wstringstream wss{};
	int boltsLeft{ m_Bolts };
	int amountOfNumbers{ 5 };
	while (boltsLeft >= 10)
	{
		boltsLeft /= 10;
		--amountOfNumbers;
	}
	for (int i{ 1 }; i < amountOfNumbers; ++i)
	{
		wss << L"0";
	}
	wss << m_Bolts;
	m_pBoltsTextComp->SetText(wss.str());
}

void ScoreComponent::Initialize(const SceneContext& /*sceneContext*/)
{
	AddBolts(0);
}
