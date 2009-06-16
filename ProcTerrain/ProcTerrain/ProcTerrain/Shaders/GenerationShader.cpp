#include "GenerationShader.h"



GenerationShader::GenerationShader(float seed, GLuint permTextureID, GLuint permGradTextureID)
	: Shader("../../ProcTerrain/Shaders/terrainGeneration.vert", "../../ProcTerrain/Shaders/terrainGeneration.frag"){
	
	//m_locSeed = glGetUniformLocationARB(m_shaderProg,"seed");
	//m_seed = seed;

	//m_locPosition = glGetUniformLocationARB(m_shaderProg,"position");
	m_locPermTexture = glGetUniformLocationARB(m_shaderProg,"permTexture");
	m_permTextureID = permTextureID;

	m_locPermGradTexture = glGetUniformLocationARB(m_shaderProg,"permGradTexture");
	m_permGradTextureID = permGradTextureID;

	/*
	Enable();
	glBindTexture(GL_TEXTURE_2D, permTextureID);
	glUniform1i(m_locPermTexture, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	Disable();
	*/

}

GenerationShader::~GenerationShader(){
	Shader::~Shader();

}

void GenerationShader::Enable(){
	Shader::Enable();

	glBindTexture(GL_TEXTURE_2D, m_permTextureID);
	//glBindTexture(GL_TEXTURE_2D, m_permGradTextureID);

	//TODO: bind only once, when the GenerationShader is instanced
	//there is no need to do it every frame: http://www.gamedev.net/community/forums/mod/journal/journal.asp?jn=530427&reply_id=3450696
	//glUniform1i(m_locPermTexture, 0);

}

void GenerationShader::Disable(){

	glBindTexture(GL_TEXTURE_2D, 0);
	Shader::Disable();
	

}