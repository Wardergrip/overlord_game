// Source: https://www.youtube.com/watch?v=9bTFVaKGIIQ&ab_channel=WorldofZero

//=============================================================================
//// Shader uses position and texture
//=============================================================================
SamplerState samPoint
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Mirror;
    AddressV = Mirror;
};

Texture2D gTexture;

float gColls;
float gRows;

/// Create Depth Stencil State (ENABLE DEPTH WRITING)

DepthStencilState EnableDepthWriting
{
    DepthEnable = true;
};

/// Create Rasterizer State (Backface culling

RasterizerState BackfaceCulling
{
    CullMode = BACK;
};


//IN/OUT STRUCTS
//--------------
struct VS_INPUT
{
    float3 Position : POSITION;
    float2 TexCoord : TEXCOORD0;

};

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD1;
};


//VERTEX SHADER
//-------------
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;
	
    output.Position = float4(input.Position, 1.f);
	
    output.TexCoord = input.TexCoord;
	
    return output;
}


//PIXEL SHADER
//------------
float4 PS(PS_INPUT input) : SV_Target
{
    float2 uv = input.TexCoord;
    
    uv.x *= gColls;
    uv.y *= gRows;
    uv.x = round(uv.x);
    uv.y = round(uv.y);
    uv.x /= gColls;
    uv.y /= gRows;
    
    return gTexture.Sample(samPoint, uv);
}


//TECHNIQUE
//---------
technique11 Pixelated
{
    pass P0
    {
		// Set states...
        SetVertexShader(CompileShader(vs_4_0, VS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, PS()));
    }
}