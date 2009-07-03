#ifndef DYNAMICTERRAIN_H
#define DYNAMICTERRAIN_H

#include "node.h"
#include "Heightmask.h"
#include "Vector3.h"
#include "Terrain.h"

class DynamicTerrain : public Terrain{
protected:
	virtual void Render(bool,int);

public:
	DynamicTerrain(int, Vector3<float>, Vector3<float>, int, int);
	virtual void FillHeightMap() = 0;
	
	//void SetHeightMask(Heightmask);
	//int GetHeight(int, int);
	//Vector3<float> GetColor(int, int);


};

#endif
