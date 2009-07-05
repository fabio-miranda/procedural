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
	//Vector2<float> mix(Vector2<float> a, Vector2<float> b, float weight);
	float mix(float a, float b, float weight);
	double grad(int hash, float x, float y, float z) ;

	char* m_ptrPermArray;
	char* m_heightMap;
	GLuint m_textureId;
	GLuint m_pboId;



public:
	HeightMapCPU(RenderingShader* renderingShader, char *ptrPermArray,
						   Vector3<float> relativePosition, Vector3<float> translation, 
						   float geomSize, short numDivisions, short textureSize, 
						   int octaves, float lacunarity, float gain, float offset);
	~ HeightMapCPU();
	void Generate();
	void Render(double);
	void InitTexture();


};

#endif