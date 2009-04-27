#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include "node.h"
#include "Heightmask.h"
#include "Vector3.h"
#include "DynamicTerrain.h"

class PerlinNoise : public DynamicTerrain{
protected:

	float m_persistence;
	int m_octaves;
	int m_seed;

public:
	PerlinNoise(int, Vector3<float>, Vector3<float>, int, int, int, int, float);
	virtual void FillHeightMap();
	float CosineInterpolation(float, float, float);
	float GetNoise(int);
	void GenerateNeighbours(Node*);


};

#endif
