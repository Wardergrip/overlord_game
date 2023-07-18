#include "stdafx.h"
#include "ScoreComponent.h"

ScoreComponent::ScoreComponent()
	:m_Bolts{0}
{
}

void ScoreComponent::AddBolts(int bolts)
{
	m_Bolts += bolts;
}
