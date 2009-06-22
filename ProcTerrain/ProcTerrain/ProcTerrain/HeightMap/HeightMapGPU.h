#ifndef HEIGHTMAPGPU_H
#define HEIGHTMAPGPU_H


#include "HeightMap.h"
#include "../Shaders/GenerationShader.h"
#include "../Util/FBO.h"
#include "../Defines.h";


class HeightMapGPU : public HeightMap {
	
	
	float m_textureSize;
	
	short m_currentIteration;
	short m_maxIterations;
	
	


public:
	HeightMapGPU(RenderingShader* renderingShader, GenerationShader* generationShader,
						   Vector3<float> relativePosition, Vector3<float> translation, 
						   float geomSize, short numDivisions, short textureSize, short maxIterations);

	~ HeightMapGPU();
	void Generate();
	void ReGenerate(Vector3<float> newPosition);
	void Render(double);
	void Delete();
	void SwapFBOs(FBO* ptrNewFBO);


	GenerationShader *m_ptrGenerationShader;
	FBO *m_ptrFBO;

};

#endif