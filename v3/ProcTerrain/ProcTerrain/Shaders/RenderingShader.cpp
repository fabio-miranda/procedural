#include "RenderingShader.h"



//TODO: calculate the normal of the heightmap on the generation shader (instead of calculating it each frame on the rendering shader)
RenderingShader::RenderingShader(bool complex){
	

	if(complex)
		LoadFiles("Shaders/complexTerrainRendering.vert", "Shaders/complexTerrainRendering.frag");
	else
		LoadFiles("Shaders/simpleTerrainRendering.vert", "Shaders/simpleTerrainRendering.frag");

	m_locTexture = glGetUniformLocationARB(m_shaderProg,"heightmap");
	//glUniform1i(m_locTexture, 0);

	m_locTime = glGetUniformLocationARB(m_shaderProg,"time");
	m_locGPUGenerated = glGetUniformLocationARB(m_shaderProg,"gpuGenerated");

	m_locShowBlendTexture = glGetUniformLocationARB(m_shaderProg,"showBlendTexture");
	m_locShowLight = glGetUniformLocationARB(m_shaderProg,"showLight");
	m_locShowHeightMap = glGetUniformLocationARB(m_shaderProg,"showHeightMap");
	m_locShowVerticesDisplacement = glGetUniformLocationARB(m_shaderProg,"showVerticesDisplacement");

	//Textures
	/*
	m_locBlendTextures = new GLuint[4];
	m_locBlendTextures[0] = glGetUniformLocationARB(m_shaderProg,"blendTexture1");
	//glUniform1i(m_locBlendTextures[0], 1);
	m_locBlendTextures[1] = glGetUniformLocationARB(m_shaderProg,"blendTexture2");
	//glUniform1i(m_locBlendTextures[1], 2);
	m_locBlendTextures[2] = glGetUniformLocationARB(m_shaderProg,"blendTexture3");
	//glUniform1i(m_locBlendTextures[2], 3);
	m_locBlendTextures[3] = glGetUniformLocationARB(m_shaderProg,"blendTexture4");
	//glUniform1i(m_locBlendTextures[3], 4);
	*/




	



}

RenderingShader::~RenderingShader(){
	Shader::~Shader();

}