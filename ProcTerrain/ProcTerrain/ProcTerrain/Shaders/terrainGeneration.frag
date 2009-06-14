
//uniform float seed;
#define SEED 5123.0
varying vec2 position;

float rand(vec2 co){

	return 1.0 - 2.0 * fract(sin(dot((cos(vec2(co.x, co.y)) * sin(SEED)), vec2(15.12345, 91.98765))) * 115309.76543);

}






void main(void){
	
	float color = rand(gl_TexCoord[0].xy + position.xy);
	gl_FragColor = vec4(color, color, color, 1);

}
