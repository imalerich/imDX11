struct VS_OUTPUT {
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

VS_OUTPUT vMain(float4 pos : POSITION, float4 color : COLOR) {
	VS_OUTPUT output;

	output.Pos = pos;
	output.Color = color;
	
	return output;
}

float4 pMain(VS_OUTPUT input) : SV_TARGET{
	return input.Color;
}