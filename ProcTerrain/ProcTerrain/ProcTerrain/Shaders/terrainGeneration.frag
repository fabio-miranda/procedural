
//uniform float seed;
#define OCTAVES 5
#define ONE 0.00390625
#define ONEHALF 0.001953125

uniform sampler2D permTexture;
varying vec2 position;

float fade(float t) {
  //return t*t*(3.0-2.0*t); // Old fade
  return t*t*t*(t*(t*6.0-15.0)+10.0); // Improved fade
}


float noise(vec3 P)
{
  vec3 Pi = ONE*floor(P)+ONEHALF; 
                                 
  vec3 Pf = P-floor(P);
  
  // Noise contributions from (x=0, y=0)
  float perm00 = texture2D(permTexture, Pi.xy).a ;
  vec3  grad000 = texture2D(permTexture, vec2(perm00, Pi.z)).rgb * 4.0 - 1.0;
  float n000 = dot(grad000, Pf);

  // Noise contributions from (x=0, y=1)
  float perm01 = texture2D(permTexture, Pi.xy + vec2(0.0, ONE)).a ;
  vec3  grad010 = texture2D(permTexture, vec2(perm01, Pi.z)).rgb * 4.0 - 1.0;
  float n010 = dot(grad010, Pf - vec3(0.0, 1.0, 0.0));

  // Noise contributions from (x=1, y=0)
  float perm10 = texture2D(permTexture, Pi.xy + vec2(ONE, 0.0)).a ;
  vec3  grad100 = texture2D(permTexture, vec2(perm10, Pi.z)).rgb * 4.0 - 1.0;
  float n100 = dot(grad100, Pf - vec3(1.0, 0.0, 0.0));

  // Noise contributions from (x=1, y=1)
  float perm11 = texture2D(permTexture, Pi.xy + vec2(ONE, ONE)).a ;
  vec3  grad110 = texture2D(permTexture, vec2(perm11, Pi.z)).rgb * 4.0 - 1.0;
  float n110 = dot(grad110, Pf - vec3(1.0, 1.0, 0.0));

  // Blend contributions along x
  vec4 n_x = vec4(n000, n010, n100, n110);

  // Blend contributions along y
  vec2 n_xy = mix(n_x.xy, n_x.zw, fade(Pf.y));

  // Blend contributions along z
  float n_xyz = mix(n_xy.x, n_xy.y, fade(Pf.z));
 
  return n_xyz;
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
