
uniform sampler2D texture;
uniform float time;



void main()
{
	gl_FragColor = texture2D(texture,gl_TexCoord[0].st) * vec4(time,1,1,1);
}
