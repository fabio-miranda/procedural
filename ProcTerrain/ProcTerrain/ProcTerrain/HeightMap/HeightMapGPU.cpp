#include "HeightMapGPU.h"



HeightMapGPU::HeightMapGPU(RenderingShader* renderingShader, GenerationShader* generationShader,
						   Vector3<float> relativePosition, Vector3<float> globalPosition, 
						   float geomSize, short numDivisions, short textureSize, short maxIterations)
						   : HeightMap(renderingShader, relativePosition, globalPosition, geomSize, numDivisions){
	

	m_gpuOrCpu = GPU;
	m_ptrGenerationShader = generationShader;
	m_textureSize = textureSize;

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
	m_time = 2.0f;

}

void HeightMapGPU::SwapFBOs(FBO* ptrNewFBO){
	m_ptrFBO = ptrNewFBO;

}


void HeightMapGPU::Generate(){

	if(m_generated) return;


	//Simple square has to have the same size as the FBO
	SimpleSquare* simpleSquare = new SimpleSquare(m_globalPosition, m_textureSize, m_geomSize);

	
	m_ptrFBO->Enable(m_globalPosition);
	m_ptrGenerationShader->Enable();
	
	
	simpleSquare->Render();
	

	m_ptrGenerationShader->Disable();
	m_ptrFBO->Disable();

	m_currentIteration++;
	if(m_currentIteration >= m_maxIterations){
		m_generated = true;
	}
	

}

void HeightMapGPU::Render(double elapsedTime){
	if(m_time > 1) m_time -= elapsedTime;

	//m_ptrRenderingShader->Enable();

	//glActiveTexture(GL_TEXTURE0);
	//glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_ptrFBO->m_textureId);
	glUniform1f(m_ptrRenderingShader->m_locTime, m_time);
	glUniform1f(m_ptrRenderingShader->m_locGPUGenerated, 1.0);
	//TODO: do it only once, after generating the heightmap
	//there is no need to do it every frame: http://www.gamedev.net/community/forums/mod/journal/journal.asp?jn=530427&reply_id=3450696
	//glUniform1i(m_ptrTerrainRenderingShader->m_locTexture, 0);
	

	m_face->Render();

	glBindTexture(GL_TEXTURE_2D, 0);

	//m_ptrRenderingShader->Disable();

}

void HeightMapGPU::Delete(){
	delete m_ptrFBO;

}