#ifndef STATICTERRAIN_H
#define STATICTERRAIN_H

#include "node.h"
#include "Heightmask.h"
#include "Vector3.h"
#include "Terrain.h"

class StaticTerrain : public Terrain{
protected:
	virtual void Render(bool,int);
	

public:
	StaticTerrain(int, Vector3<float>, Vector3<float>, int, int);
	virtual void FillHeightMap() = 0;
	


};

#endif
