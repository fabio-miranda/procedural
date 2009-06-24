
#define NORMAL_OFF 0.001953125 //(1.0 / textureSize)

uniform sampler2D texture;
uniform float time;

//Light
varying vec4 diffuse,ambient;
//varying vec3 normal,lightDir,halfVector;
varying vec3 lightDir,halfVector;


void main()
{
	//gl_FragColor = texture2D(texture,gl_TexCoord[0].st);
	
	vec3 n,halfV;
	float NdotL,NdotHV;
	
	/* The ambient term will always be present */
	vec4 color = ambient;
	

	//Normal:
	float A = texture2D(texture,gl_TexCoord[0].st).x;
	float B = texture2D(texture,gl_TexCoord[0].st + vec2(NORMAL_OFF,0)).x;
	float C = texture2D(texture,gl_TexCoord[0].st + vec2(0,NORMAL_OFF)).x;

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




	gl_FragColor = color;
}
