// shaders.hlsl
// Ian Malerich

Texture2D diffuseTex;
SamplerState diffuseState;

Texture2D normalTex;
SamplerState normalState;

cbuffer cbPerObject {
	float4x4 WVP;
	float4x4 IW;
};

struct VS_OUTPUT {
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
	float2 Texcoords : TEXCOORD;
};

VS_OUTPUT vMain(float4 pos : POSITION, 
		float3 norm : NORMAL, float3 tan : TANGENT, float3 binorm : BINORMAL,
		float2 texcoords : TEXCOORD) {
	VS_OUTPUT output;

	output.Pos = mul(pos, WVP);

	output.Normal = mul(float4(norm, 0.0f), IW).xyz;
	output.Tangent = mul(float4(tan, 0.0f), IW).xyz;
	output.Binormal = mul(float4(binorm, 0.0f), IW).xyz;

	output.Texcoords = texcoords;
	
	return output;
}

float4 pMain(VS_OUTPUT input) : SV_TARGET{
	// TODO - Lighting information should be handed as input to the shader.
	float3 LDIR = -float3(0.0f, 0.0f, 1.0f);

	float3 norm = normalTex.Sample(normalState, input.Texcoords).xyz;
	norm = norm * 2.0 - 1.0f;
	norm = float3(0.0f, 0.0f, 1.0f);

	float3x3 TBN = transpose(float3x3(
		normalize(input.Tangent),
		normalize(input.Binormal),
		normalize(input.Normal)
	));

	norm = normalize(mul(norm, TBN));
	float s = max(dot(LDIR, norm), 0.1f);

	return diffuseTex.Sample(diffuseState, input.Texcoords) * s;
}