#ifndef HEIGHTMAPCPU_H
#define HEIGHTMAPCPU_H


#include "HeightMap.h"
#include "../Defines.h"


class HeightMapCPU : public HeightMap{


public:
	HeightMapCPU(RenderingShader* renderingShader, 
						   Vector3<float> relativePosition, Vector3<float> translation, 
						   float geomSize, short numDivisions);
	~ HeightMapCPU();
	void Generate();
	void Render(double);


};

#endif