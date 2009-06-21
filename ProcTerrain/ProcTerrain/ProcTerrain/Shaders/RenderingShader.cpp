#include "RenderingShader.h"



RenderingShader::RenderingShader() : Shader("../../ProcTerrain/Shaders/terrainRendering.vert", "../../ProcTerrain/Shaders/terrainRendering.frag"){
	
	m_locTexture = glGetUniformLocationARB(m_shaderProg,"heightmap");
	m_locTime = glGetUniformLocationARB(m_shaderProg,"time");



}

RenderingShader::~RenderingShader(){
	Shader::~Shader();

}