#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H



#include "../Util/Vertex.h"
#include "../Util/SimpleSquare.h"
#include "../Shaders/GenerationShader.h"
#include "../Util/FBO.h"


class HeightMap{
	
	
	Vector3<float> m_position;
	float m_size;
	
	short m_currentIteration;
	short m_maxIterations;

	


public:
	HeightMap(GenerationShader*, FBO*, Vector3<float>, float, short);
	~ HeightMap();
	void Generate();

	GenerationShader *m_ptrTerrainGenerationShader;
	FBO *m_ptrFBO;

};

#endif