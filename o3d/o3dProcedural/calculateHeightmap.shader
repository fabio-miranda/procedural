// World View Projection matrix that will transform the input vertices
// to screen space.
float4x4 worldViewProjection : WorldViewProjection;
uniform float time;


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

float4 checker(float2 uv) {
    float checkSize = 4;
    float fmodResult = fmod(floor(checkSize * uv.x) + floor(checkSize * uv.y),
                            2.0);
    if (fmodResult < 1) {
      return float4(0, 1, 1, 1);
    } else {
      return float4(1, 0, 1, 1);
    }
  }

float4 pixelShaderFunction(PixelShaderInput input): COLOR {
	//float4 check = checker(input.texcoord);
    float4 color = float4(time,0 , 0, 1);
    //float height = tex2D(texSampler0, input.texcoord).r;
    
    return color;
}

// Here we tell our effect file *which* functions are
// our vertex and pixel shaders.

// #o3d VertexShaderEntryPoint vertexShaderFunction
// #o3d PixelShaderEntryPoint pixelShaderFunction
// #o3d MatrixLoadOrder RowMajor
