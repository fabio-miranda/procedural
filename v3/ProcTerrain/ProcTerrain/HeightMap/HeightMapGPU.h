#ifndef HEIGHTMAPGPU_H
#define HEIGHTMAPGPU_H


#include "HeightMap.h"
#include "../Shaders/GenerationShader.h"
#include "../Util/FBO.h"
#include "../Defines.h";


class HeightMapGPU : public HeightMap {
	
	
	short m_currentIteration;
	short m_maxIterations;
	
	


public:
	HeightMapGPU(RenderingShader* renderingShader, GenerationShader* generationShader, GLuint* ptrBlendTextures,
						   Vector3<float> relativePosition, Vector3<float> translation, 
						   float geomSize, short numDivisions, short textureSize, short maxIterations,
						   int octaves, float lacunarity, float gain, float offset);

	~ HeightMapGPU();
	void Generate();
	void ReGenerate(Vector3<float> newPosition);
	void Render(double);
	void Delete();
	//void SwapFBOs(FBO* ptrNewFBO);
	void SwapHeightMap(GLuint newHeightMap);


	GenerationShader *m_ptrGenerationShader;
	FBO *m_ptrFBO;
	
	GLuint* m_ptrBlendTextures;

};

#endif