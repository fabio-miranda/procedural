// World View Projection matrix that will transform the input vertices
// to screen space.
float4x4 worldViewProjection : WorldViewProjection;
uniform sampler texSampler;
uniform sampler permTexture;
uniform int iteration;

#define ONE 0.00390625
#define ONEHALF 0.001953125

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

float fade(float t) {
  //return t*t*(3.0-2.0*t); // Old fade
  return t*t*t*(t*(t*6.0-15.0)+10.0); // Improved fade
}


float noise(float3 P)
{
	  float3 Pi = ONE*floor(P)+ONEHALF; 
	                                 
	  float3 Pf = P-floor(P);
	  
	  // Noise contributions from (x=0, y=0), z=0 and z=1
	  float perm00 = tex2D(permTexture, Pi.xy).a ;
	  float3  grad000 = tex2D(permTexture, float2(perm00, Pi.z)).rgb * 4.0 - 1.0;
	  float n000 = dot(grad000, Pf);
	  float3  grad001 = tex2D(permTexture, float2(perm00, Pi.z + ONE)).rgb * 4.0 - 1.0;
	  float n001 = dot(grad001, Pf - float3(0.0, 0.0, 1.0));
	
	  // Noise contributions from (x=0, y=1), z=0 and z=1
	  float perm01 = tex2D(permTexture, Pi.xy + float2(0.0, ONE)).a ;
	  float3  grad010 = tex2D(permTexture, float2(perm01, Pi.z)).rgb * 4.0 - 1.0;
	  float n010 = dot(grad010, Pf - float3(0.0, 1.0, 0.0));
	  float3  grad011 = tex2D(permTexture, float2(perm01, Pi.z + ONE)).rgb * 4.0 - 1.0;
	  float n011 = dot(grad011, Pf - float3(0.0, 1.0, 1.0));
	
	  // Noise contributions from (x=1, y=0), z=0 and z=1
	  float perm10 = tex2D(permTexture, Pi.xy + float2(ONE, 0.0)).a ;
	  float3  grad100 = tex2D(permTexture, float2(perm10, Pi.z)).rgb * 4.0 - 1.0;
	  float n100 = dot(grad100, Pf - float3(1.0, 0.0, 0.0));
	  float3  grad101 = tex2D(permTexture, float2(perm10, Pi.z + ONE)).rgb * 4.0 - 1.0;
	  float n101 = dot(grad101, Pf - float3(1.0, 0.0, 1.0));
	
	  // Noise contributions from (x=1, y=1), z=0 and z=1
	  float perm11 = tex2D(permTexture, Pi.xy + float2(ONE, ONE)).a ;
	  float3  grad110 = tex2D(permTexture, float2(perm11, Pi.z)).rgb * 4.0 - 1.0;
	  float n110 = dot(grad110, Pf - float3(1.0, 1.0, 0.0));
	  float3  grad111 = tex2D(permTexture, float2(perm11, Pi.z + ONE)).rgb * 4.0 - 1.0;
	  float n111 = dot(grad111, Pf - float3(1.0, 1.0, 1.0));
	
	  // Blend contributions along x
	  float4 n_x = lerp(float4(n000, n001, n010, n011), float4(n100, n101, n110, n111), fade(Pf.x));
	
	  // Blend contributions along y
	  float2 n_xy = lerp(n_x.xy, n_x.zw, fade(Pf.y));
	
	  // Blend contributions along z
	  float n_xyz = lerp(n_xy.x, n_xy.y, fade(Pf.z));
	 
	  return n_xyz;
}

/*
float turbulence(float3 P, float lacunarity, float gain){
	
	float sum = 0;
	float scale = 1;
  	float totalgain = 1;
  	for(int i=0;i<octaves;i++){
    	sum += totalgain*noise(P*scale);
    	scale *= lacunarity;
    	totalgain *= gain;
  	}
  	return abs(sum);
}
*/


float4 pixelShaderFunction(PixelShaderInput input): COLOR {
	//float4 check = checker(input.texcoord);
    //float4 color = float4(0,0 , 1, 1);
    float4 currentHeight = tex2D(texSampler, input.texcoord);
    
    float newHeight = currentHeight.x + noise(float3(4.0 * input.texcoord.xy, 0));
    
    return float4(newHeight, newHeight, newHeight, 1);
}

// Here we tell our effect file *which* functions are
// our vertex and pixel shaders.

// #o3d VertexShaderEntryPoint vertexShaderFunction
// #o3d PixelShaderEntryPoint pixelShaderFunction
// #o3d MatrixLoadOrder RowMajor
