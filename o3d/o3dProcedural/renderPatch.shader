// World View Projection matrix that will transform the input vertices
// to screen space.
float4x4 worldViewProjection : WorldViewProjection;
uniform float heightmap[1];


struct VertexShaderInput {
	float4 position : POSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
};


struct PixelShaderInput {
	float4 position : POSITION;
	//float4 color : COLOR;
	float2 texcoord : TEXCOORD0;
};


PixelShaderInput vertexShaderFunction(VertexShaderInput input) {
	PixelShaderInput output;

	// Multiply the vertex positions by the worldViewProjection matrix to
	// transform them to screen space.
	output.position = mul(input.position, worldViewProjection);
	
	//output.position.z = tex2Dlod(texHeightmap, float4(input.texcoord, 0, 0));
	
	output.texcoord = input.texcoord;
	return output;
}



float4 pixelShaderFunction(PixelShaderInput input): COLOR {
	//float4 height = checker(input.texcoord);
    //float4 height = float4(0, 1, 0, 1);
    
    //float4 height = tex2D(texHeightmap, input.texcoord);
    
    return float4(1, 0, 0, 1);
}

// Here we tell our effect file *which* functions are
// our vertex and pixel shaders.

// #o3d VertexShaderEntryPoint vertexShaderFunction
// #o3d PixelShaderEntryPoint pixelShaderFunction
// #o3d MatrixLoadOrder RowMajor
