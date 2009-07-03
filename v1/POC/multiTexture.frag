
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;

varying vec4 vPosition;

void main()
{
	vec4 color0 = texture2D(tex0,gl_TexCoord[0].st);
	vec4 color1 = texture2D(tex1,gl_TexCoord[1].st);
	vec4 color2 = texture2D(tex2,gl_TexCoord[2].st);
	
	gl_FragColor = color0;
	
	//gl_FragColor = vec4(0,1.0,0,1) * (vPosition.z) + vec4(0,0,1.0,1) / (vPosition.z);
}

