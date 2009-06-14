#include "RenderingShader.h"



RenderingShader::RenderingShader() : Shader("../../ProcTerrain/Shaders/terrainRendering.vert", "../../ProcTerrain/Shaders/terrainRendering.frag"){
	
	m_locTexture = glGetUniformLocationARB(m_shaderProg,"texture");



}

RenderingShader::~RenderingShader(){
	Shader::~Shader();

}