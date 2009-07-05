#include "HeightMapGPU.h"



HeightMapGPU::HeightMapGPU(RenderingShader* renderingShader, GenerationShader* generationShader, GLuint* ptrBlendTextures,
						   Vector3<float> relativePosition, Vector3<float> globalPosition, 
						   float geomSize, short numDivisions, short textureSize, short maxIterations,
						   int octaves, float lacunarity, float gain, float offset)
						   : HeightMap(renderingShader, relativePosition, globalPosition, geomSize, numDivisions, textureSize, octaves, lacunarity, gain, offset){
	

	m_gpuOrCpu = GPU;
	m_ptrGenerationShader = generationShader;
	m_ptrBlendTextures = ptrBlendTextures;

	//TODO: share FBOs between the nodes? Or each node has its own FBO?
	m_ptrFBO = new FBO(textureSize, textureSize);
	//m_ptrFBO = fbo;



	m_maxIterations = maxIterations;
	m_currentIteration = 0;

	
	
}

//TODO: delete properly
HeightMapGPU::~HeightMapGPU(){

}

void HeightMapGPU::ReGenerate(Vector3<float> newPosition){
	
	m_ptrFBO = new FBO(m_textureSize, m_textureSize);
	m_globalPosition = newPosition;
	m_generated = false;
	m_time = 5.0f;

}

void HeightMapGPU::SwapHeightMap(GLuint newHeightMapId){
	//m_ptrFBO = ptrNewFBO;
	m_ptrFBO->m_textureId = newHeightMapId;

}

//TODO: calculate the normal of the heightmap on the generation shader (instead of calculating it each frame on the rendering shader)
void HeightMapGPU::Generate(){

	if(m_generated) return;

	float time = glfwGetTime();


	//Simple square has to have the same size as the FBO
	SimpleSquare* simpleSquare = new SimpleSquare(m_globalPosition, m_textureSize, m_geomSize);

	
	m_ptrFBO->Enable(m_globalPosition);
	m_ptrGenerationShader->Enable();
	
	//Uniform variables
	glUniform1i(m_ptrGenerationShader->m_locOctaves, m_octaves);
	glUniform1f(m_ptrGenerationShader->m_locLacunarity, m_lacunarity);
	glUniform1f(m_ptrGenerationShader->m_locGain, m_gain);
	glUniform1f(m_ptrGenerationShader->m_locOffset, m_offset);
	
	simpleSquare->Render();
	

	m_ptrGenerationShader->Disable();
	m_ptrFBO->Disable();

	m_currentIteration++;
	if(m_currentIteration >= m_maxIterations){
		m_generated = true;
	}

	//glFinish();

	time = glfwGetTime() - time;
	cout << time * 1000.0f;
	cout << "\n";
	

}

void HeightMapGPU::Render(double elapsedTime){
	if(m_time > 1) m_time -= elapsedTime;


	//m_ptrRenderingShader->Enable();

	glEnable(GL_TEXTURE_2D);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_ptrFBO->m_textureId);
	
	glUniform1f(m_ptrRenderingShader->m_locTime, m_time);
	glUniform1f(m_ptrRenderingShader->m_locGPUGenerated, 1.0);
	glUniform1f(m_ptrRenderingShader->m_locShowHeightMap, conf_showHeightMap);
	glUniform1f(m_ptrRenderingShader->m_locShowLight, conf_showLight);
	glUniform1f(m_ptrRenderingShader->m_locShowBlendTexture, conf_showBlendTexture);
	glUniform1f(m_ptrRenderingShader->m_locShowVerticesDisplacement, conf_showVerticesDisplacement);
	
	/*
	for(int i=0; i<4; i++)
	{
		glUniform1i(m_ptrRenderingShader->m_locBlendTextures[i], 0);
		glActiveTexture(GL_TEXTURE1+i);
		glBindTexture(GL_TEXTURE_2D, m_ptrBlendTextures[i]);
		
	}
	*/
	
	
	

	
	//TODO: do it only once, after generating the heightmap
	//there is no need to do it every frame: http://www.gamedev.net/community/forums/mod/journal/journal.asp?jn=530427&reply_id=3450696
	//glUniform1i(m_ptrTerrainRenderingShader->m_locTexture, 0);
	

	m_face->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	//m_ptrRenderingShader->Disable();

}

void HeightMapGPU::Delete(){
	delete m_ptrFBO;

}