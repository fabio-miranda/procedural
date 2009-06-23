#ifndef HEIGHTMAPCPU_H
#define HEIGHTMAPCPU_H


#include "HeightMap.h"
#include "../Defines.h"
#include "../Util/Vector2.h"


class HeightMapCPU : public HeightMap{

	float noise(Vector3<float> P);
	float fade(float t);
	float ridge(float h, float offset);
	float ridgedmf(Vector3<float> position);
	Vector2<float> mix(Vector2<float> a, Vector2<float> b, float weight);
	float mix(float a, float b, float weight);

	char* m_ptrPermArray;



public:
	HeightMapCPU(RenderingShader* renderingShader, 
						   Vector3<float> relativePosition, Vector3<float> translation, 
						   float geomSize, short numDivisions, char* ptrPermArray,
						   int octaves, float lacunarity, float gain, float offset);
	~ HeightMapCPU();
	void Generate();
	void Render(double);


};

#endif