#include "GenerationShader.h"



GenerationShader::GenerationShader(float seed) : Shader("../../ProcTerrain/Shaders/terrainGeneration.vert", "../../ProcTerrain/Shaders/terrainGeneration.frag"){
	
	//m_locSeed = glGetUniformLocationARB(m_shaderProg,"seed");
	//m_seed = seed;

	//m_locPosition = glGetUniformLocationARB(m_shaderProg,"position");


}

GenerationShader::~GenerationShader(){
	Shader::~Shader();

}