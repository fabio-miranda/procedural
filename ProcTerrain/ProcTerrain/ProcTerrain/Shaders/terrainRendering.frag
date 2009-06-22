
uniform sampler2D texture;
uniform float time;
uniform float gpuGenerated;



void main()
{
	if(gpuGenerated == 1)
		gl_FragColor = texture2D(texture,gl_TexCoord[0].st) * vec4(time,1,1,1);
	else
		gl_FragColor = vec4(1,1,1,1);
}
