
uniform sampler2D texture;

void main()
{
	gl_FragColor = texture2D(texture,gl_TexCoord[0].st) + vec4(0, 0, 0, 0);
	//gl_FragColor = vec4(1, 0, 0, 0);
}
