struct VS_OUTPUT
{
	float4 pos: POSITION;
};


VS_OUTPUT VS(float2 pos: POSITION)
{
	VS_OUTPUT output;
	
	output.pos = pos;
	
	return output;
}


float4 PS(): COLOR0
{
	return float4(1.0, 1.0, 1.0, 1.0);
}


technique RenderScene
{
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_1_1 PS();
	}
}
