//varying vec2 position;

void main()
{	
	//position = gl_Vertex.xy;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
