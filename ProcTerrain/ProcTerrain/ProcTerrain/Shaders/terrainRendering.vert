
uniform sampler2D heightmap;



void main()
{	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Vertex.z = texture2D(heightmap,gl_TexCoord[0].st).r * 0.5;

	gl_Position = gl_ModelViewProjectionMatrix  * gl_Vertex;

}
