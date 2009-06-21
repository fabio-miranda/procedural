#include "HeightMap.h"


HeightMap::HeightMap(GenerationShader* generationShader, Vector3<float> position, float geomSize, short textureSize, short maxIterations){
	

	m_ptrTerrainGenerationShader = generationShader;

	//TODO: share FBOs between the nodes? Or each node has its own FBO?
	m_ptrFBO = new FBO(textureSize, textureSize);
	//m_ptrFBO = fbo;

	m_position = position;
	m_geomSize = geomSize;
	m_textureSize = textureSize;

	m_maxIterations = maxIterations;
	m_currentIteration = 0;

	m_time = 2.0f; //time since the generation of the heightmap

	
	
}

HeightMap::~HeightMap(){

}

void HeightMap::Generate(){
	
	if(m_currentIteration >= m_maxIterations){
		return;
	}
	m_currentIteration++;
	
	//Simple square has to have the same size as the FBO
	SimpleSquare* simpleSquare = new SimpleSquare(m_position, m_textureSize, m_geomSize);

	
	m_ptrFBO->Enable(m_position);
	m_ptrTerrainGenerationShader->Enable();
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