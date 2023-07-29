#include "stdafx.h"
#include "PostPixelated.h"

PostPixelated::PostPixelated() :
	PostProcessingMaterial(L"Effects/Post/PixelatedShader.fx")
{
}

void PostPixelated::SetCollRow(float colls, float rows) const
{
	m_pBaseEffect->GetVariableByName("gColls")->AsScalar()->SetFloat(colls);
	m_pBaseEffect->GetVariableByName("gRows")->AsScalar()->SetFloat(rows);
}
