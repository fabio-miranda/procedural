
#define NORMAL_OFF 0.001953125 //(1.0 / textureSize)

uniform sampler2D heightmap;
uniform sampler2D blendTexture1;
uniform sampler2D blendTexture2;
uniform sampler2D blendTexture3;
uniform sampler2D blendTexture4;

uniform float time;
uniform float gpuGenerated;
varying float z;

//Light
varying vec4 diffuse,ambient;
varying vec3 lightDir,halfVector;

//Booleans
uniform float showBlendTexture;
uniform float showLight;
uniform float showHeightMap;

vec4 calculateLightFactor(){

	vec3 n,halfV;
	float NdotL,NdotHV;
	
	/* The ambient term will always be present */
	vec4 color = ambient;
	

	//TODO: generate it only once
	//Normal:
	float A = texture2D(heightmap,gl_TexCoord[0].st).x;
	float B = texture2D(heightmap,gl_TexCoord[0].st + vec2(NORMAL_OFF,0)).x;
	float C = texture2D(heightmap,gl_TexCoord[0].st + vec2(0,NORMAL_OFF)).x;

	vec3 normal = vec3(B - A, C - A, 0.1);
	normalize(normal);


	/* a fragment shader can't write a varying variable, hence we need
	a new variable to store the normalized interpolated normal */
	n = normalize(normal);
	
	/* compute the dot product between normal and ldir */
	NdotL = max(dot(n,lightDir),0.0);

	if (NdotL > 0.0) {
		color += diffuse * NdotL;
		halfV = normalize(halfVector);
		NdotHV = max(dot(n,halfV),0.0);
		color += gl_FrontMaterial.specular * 
				gl_LightSource[0].specular * 
				pow(NdotHV, gl_FrontMaterial.shininess);
	}

	return color;

}

vec4 calculateBlendFactor(){
	vec4 sand = vec4(1.0, 1.0, 0, 1);
	vec4 grass = vec4(0, 0.5, 0, 1);
	vec4 rock = vec4(0.5, 0.5, 0, 1);
	vec4 snow = vec4(1, 1, 1, 1);

	/*
	vec4 sand = texture2D(blendTexture1,gl_TexCoord[1].st);
	vec4 grass = texture2D(blendTexture2,gl_TexCoord[2].st);
	vec4 rock = texture2D(blendTexture3,gl_TexCoord[3].st);
	vec4 snow = texture2D(blendTexture4,gl_TexCoord[4].st);
	*/
	
	if(z < 0.375){
		float weight_sand_grass = (z - 0.0) / (0.375 - 0.0);
		return mix(sand, grass, weight_sand_grass);
	}
	else if(z >= 0.375 && z < 0.625){
		float weight_grass_rock = (z - 0.375) / (0.625 - 0.375);
		return mix(grass, rock, weight_grass_rock);
	}
	else{
		float weight_rock_snow = (z - 0.625) / (1.0 - 0.625);
		return mix(rock, snow, weight_rock_snow);
	}

	


}

void main()
{
	vec4 lightFactor = vec4(1,1,1,1);
	vec4 blendTextureFactor = vec4(1,1,1,1);
	vec4 height = vec4(1,1,1,1);

	if(showLight == 1.0)
		lightFactor = calculateLightFactor();

	if(gpuGenerated == 1.0 && showHeightMap == 1.0)
		height = texture2D(heightmap,gl_TexCoord[0].st) * vec4(time,1,1,1);

	if(showBlendTexture == 1.0){
		blendTextureFactor = calculateBlendFactor();
	}

	gl_FragColor = blendTextureFactor * height * 1.2 * lightFactor;

	
	
	
	
}

