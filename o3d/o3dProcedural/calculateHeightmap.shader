// World View Projection matrix that will transform the input vertices
// to screen space.
float4x4 worldViewProjection : WorldViewProjection;
sampler texSampler;

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
	output.texcoord = input.texcoord;
	//output.color = float4(1, 0, 0, 1);
	return output;
}

float4 pixelShaderFunction(PixelShaderInput input): COLOR {
	//float4 check = checker(input.texcoord);
    //float4 color = float4(0,0 , 1, 1);
    float4 height = tex2D(texSampler, input.texcoord);
    
    height = height + 0.1;
    
    return height;
}

// Here we tell our effect file *which* functions are
// our vertex and pixel shaders.

// #o3d VertexShaderEntryPoint vertexShaderFunction
// #o3d PixelShaderEntryPoint pixelShaderFunction
// #o3d MatrixLoadOrder RowMajor
