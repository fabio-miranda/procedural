
uniform sampler2D heightmap;
uniform float gpuGenerated;
uniform float showVerticesDisplacement;
uniform float time;
varying float z;

//Light
varying vec4 diffuse,ambient;
varying vec3 normal,lightDir,halfVector;

//Booleans
uniform float showLight;

void calculateLight(){
	
	//Light calculation
	/* now normalize the light's direction. Note that 
	according to the OpenGL specification, the light 
	is stored in eye space. Also since we're talking about 
	a directional light, the position field is actually direction */
	lightDir = normalize(vec3(gl_LightSource[0].position));

	/* Normalize the halfVector to pass it to the fragment shader */
	halfVector = normalize(gl_LightSource[0].halfVector.xyz);
				
	/* Compute the diffuse, ambient and globalAmbient terms */
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	ambient += gl_LightModel.ambient * gl_FrontMaterial.ambient;

}

void main()
{	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_MultiTexCoord1;
	gl_TexCoord[2] = gl_MultiTexCoord2;
	gl_TexCoord[3] = gl_MultiTexCoord3;
	gl_TexCoord[4] = gl_MultiTexCoord4;
	
	if(gpuGenerated == 1.0 && showVerticesDisplacement == 1.0)
		gl_Vertex.z = texture2D(heightmap,gl_TexCoord[0].st).r * 1.0 * ((5.0 - time + 1.0) / 5.0);

	z = gl_Vertex.z;

	
	if(showLight == 1.0)
		calculateLight();
	



	gl_Position = gl_ModelViewProjectionMatrix  * gl_Vertex;




}