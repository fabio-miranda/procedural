
//uniform float seed;
#define OCTAVES 5
#define ONE 0.00390625
#define ONEHALF 0.001953125

uniform sampler2D permTexture;
uniform sampler1D permGradTexture;
varying vec2 position;

vec3 fade(vec3 t)
{
	return t * t * t * (t * (t * 6 - 15) + 10); // new curve
//	return t * t * (3 - 2 * t); // old curve
}

vec4 perm2d(vec2 p)
{
	return texture2D(permTexture, p);
}

float gradperm(float x, vec3 p)
{
	return dot(texture1D(permGradTexture, x).r, p);
	//return dot(texture2D(permTexture, p.xy).rgb, p);
}

float noise(vec3 p)
{  
  
  	vec3 P = mod(floor(p), 256.0);	// FIND UNIT CUBE THAT CONTAINS POINT
  	p -= floor(p);                      // FIND RELATIVE X,Y,Z OF POINT IN CUBE.
	vec3 f = fade(p);                 // COMPUTE FADE CURVES FOR EACH OF X,Y,Z.

	P = P / 256.0;
	//const float one = 1.0 / 256.0;
	
    // HASH COORDINATES OF THE 8 CUBE CORNERS
	vec4 AA = perm2d(P.xy) + P.z;
 
	// AND ADD BLENDED RESULTS FROM 8 CORNERS OF CUBE
  	return mix( mix( mix( gradperm(AA.x, p ),  
                             gradperm(AA.z, p + vec3(-1, 0, 0) ), f.x),
                       mix( gradperm(AA.y, p + vec3(0, -1, 0) ),
                             gradperm(AA.w, p + vec3(-1, -1, 0) ), f.x), f.y),
                             
                 mix( mix( gradperm(AA.x+ONE, p + vec3(0, 0, -1) ),
                             gradperm(AA.z+ONE, p + vec3(-1, 0, -1) ), f.x),
                       mix( gradperm(AA.y+ONE, p + vec3(0, -1, -1) ),
                             gradperm(AA.w+ONE, p + vec3(-1, -1, -1) ), f.x), f.y), f.z);
  
}


float turbulence(int octaves, vec3 P, float lacunarity, float gain)
{	
  float sum = 0.0;
  float scale = 1.0;
  float totalgain = 1.0;
  for(int i=0;i<octaves;i++){
    sum += totalgain*noise(P*scale);
    scale *= lacunarity;
    totalgain *= gain;
  }
  return abs(sum);
}



void main(void){
	
	vec3 position = vec3(gl_TexCoord[0].x + position.x, gl_TexCoord[0].y + position.y, 0);
	float color = turbulence(1, position, 1.0, 1.0);
	gl_FragColor = vec4(color, color, color, 1);

}
