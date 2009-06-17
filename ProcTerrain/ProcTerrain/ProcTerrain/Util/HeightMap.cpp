#include "HeightMap.h"


HeightMap::HeightMap(GenerationShader* generationShader, FBO* fbo, Vector3<float> position, float size, short maxIterations){
	

	m_ptrTerrainGenerationShader = generationShader;

	//TODO: share FBOs between the nodes? Or each node has its own FBO?
	m_ptrFBO = new FBO(size, size);
	//m_ptrFBO = fbo;

	m_position = position;
	m_size = size;

	m_maxIterations = maxIterations;
	m_currentIteration = 0;
	
}

HeightMap::~HeightMap(){

}

void HeightMap::Generate(){
	
	if(m_currentIteration >= m_maxIterations){
		return;
	}
	m_currentIteration++;

	
	SimpleSquare* simpleSquare = new SimpleSquare(m_position, m_size, m_size);

	
	m_ptrFBO->Enable(m_position);
	m_ptrTerrainGenerationShader->Enable(m_position);
	//glUniform1fARB(m_ptrTerrainGenerationShader->m_locSeed, m_ptrTerrainGenerationShader->m_seed);
	
	
	simpleSquare->Render();
	

	
	m_ptrTerrainGenerationShader->Disable();
	m_ptrFBO->Disable();


	//aux
	/*
	float* aux;
	glBindTexture(GL_TEXTURE_2D, m_ptrFBO->m_textureId);
	aux = (float*)malloc(512*512*sizeof(float)*4);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, aux);
	glReadPixels(0,0,512,512,GL_RGBA,GL_FLOAT,aux);
	*/
}