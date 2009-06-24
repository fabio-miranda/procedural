uniform sampler2D texture;
uniform float time;
uniform float gpuGenerated;
//varying float z;



void main()
{
	
	vec4 height = vec4(1,1,1,1);
	if(gpuGenerated == 1)
		height = texture2D(texture,gl_TexCoord[0].st) * vec4(time,1,1,1);
	
	gl_FragColor = height;
}

