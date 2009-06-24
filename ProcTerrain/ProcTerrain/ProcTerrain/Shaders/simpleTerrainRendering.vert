
uniform sampler2D heightmap;
uniform float gpuGenerated;
varying float z;



void main()
{	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	if(gpuGenerated == 1.0)
		gl_Vertex.z = texture2D(heightmap,gl_TexCoord[0].st).r * 1.0;

	z = gl_Vertex.z;
	gl_Position = gl_ModelViewProjectionMatrix  * gl_Vertex;

}