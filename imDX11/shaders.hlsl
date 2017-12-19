// shaders.hlsl
// Ian Malerich

cbuffer cbPerObject {
	float4x4 WVP;
};

struct VS_OUTPUT {
	float4 Pos : SV_POSITION;
	float3 Norm : NORMAL;
	float2 Texcoords : TEXCOORD;
};

VS_OUTPUT vMain(float4 pos : POSITION, float3 norm : NORMAL , float2 texcoords : TEXCOORD) {
	VS_OUTPUT output;

	output.Pos = mul(pos, WVP);
	output.Norm = norm;
	output.Texcoords = texcoords;
	
	return output;
}

float4 pMain(VS_OUTPUT input) : SV_TARGET{
	// TODO - Lighting information should be handed as input to the shader.
	float3 LDIR = float3(0.0f, 0.0f, -1.0f);
	float diffuse = max(dot(LDIR, input.Norm), 0.1f);
	return float4(1.0f, 1.0f, 1.0f, 1.0f) * diffuse;
}