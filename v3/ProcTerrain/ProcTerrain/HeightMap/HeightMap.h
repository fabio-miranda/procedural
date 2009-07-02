#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H



#include "../Util/Vertex.h"
#include "../Util/SimpleSquare.h"
#include "../Shaders/RenderingShader.h"
#include "../Util/FBO.h"
#include "../Util/VBOSquare.h"


#include "GL/glfw.h"
#include <iostream>
using namespace std;


class HeightMap{
	

protected:
	Vector3<float> m_relativePosition;
	Vector3<float> m_globalPosition;
	

	VBOSquare* m_face;

	RenderingShader *m_ptrRenderingShader;

	
	float m_geomSize;
	bool m_generated;
	
	short m_numDivisions;


	//
	int m_octaves;
	float m_lacunarity;
	float m_gain;
	float m_offset;
	


public:
	HeightMap(RenderingShader* renderingShader,
				Vector3<float> relativePosition, Vector3<float> translation,
				float geomSize, short numDivisions,
				int octaves, float lacunarity, float gain, float offset);
	~ HeightMap();
	virtual void Generate();
	virtual void ReGenerate(Vector3<float> newPosition);
	virtual void Render(double);
	virtual void Delete();

	double m_time;
	bool m_gpuOrCpu;

	

};

#endif