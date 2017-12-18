// shaders.hlsl
// Ian Malerich

cbuffer cbPerObject {
	float4x4 WVP;
};

struct VS_OUTPUT {
	float4 Pos : SV_POSITION;
	float3 Norm : NORMAL;
	float4 Color : COLOR;
};

VS_OUTPUT vMain(float4 pos : POSITION, float3 norm : NORMAL , float4 color : COLOR) {
	VS_OUTPUT output;

	output.Pos = mul(pos, WVP);
	output.Norm = norm;
	output.Color = color;
	
	return output;
}

float4 pMain(VS_OUTPUT input) : SV_TARGET{
	// TODO - Lighting information should be handed as input to the shader.
	float3 LDIR = float3(0.0f, 0.0f, -1.0f);
	float diffuse = max(dot(LDIR, input.Norm), 0.0f);
	return input.Color * diffuse;
}