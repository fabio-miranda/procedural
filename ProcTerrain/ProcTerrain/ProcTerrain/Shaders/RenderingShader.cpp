#include "RenderingShader.h"



RenderingShader::RenderingShader() : Shader("../../ProcTerrain/Shaders/terrainRendering.vert", "../../ProcTerrain/Shaders/terrainRendering.frag"){
	
	m_locTexture = glGetUniformLocationARB(m_shaderProg,"heightmap");
	m_locTime = glGetUniformLocationARB(m_shaderProg,"time");
	m_locGPUGenerated = glGetUniformLocationARB(m_shaderProg,"gpuGenerated");



}

RenderingShader::~RenderingShader(){
	Shader::~Shader();

}