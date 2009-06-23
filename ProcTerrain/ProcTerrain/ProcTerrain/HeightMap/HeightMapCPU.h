#ifndef HEIGHTMAPCPU_H
#define HEIGHTMAPCPU_H


#include "HeightMap.h"
#include "../Defines.h"
#include "../Util/Vector2.h"


class HeightMapCPU : public HeightMap{

	float noise(Vector3<float> P);
	float ridge(float h, float offset);
	float ridgedmf(Vector3<float> position);
	float CosineInterpolation(float a, float b, float x);
	float GetNoise(int i);

	int m_octaves;
	float m_offset;
	float m_lacunarity;
	float m_gain;
	float m_seed;

	char* m_ptrPermArray;



public:
	HeightMapCPU(RenderingShader* renderingShader, 
						   Vector3<float> relativePosition, Vector3<float> translation, 
						   float geomSize, short numDivisions);
	~ HeightMapCPU();
	void Generate();
	void Render(double);


};

#endif