#ifndef FAULTFORMATION_H
#define FAULTFORMATION_H

#include "node.h"
#include "StaticTerrain.h"
#include "Vector3.h"

class FaultFormation : public StaticTerrain{

private:
	float m_minDelta;
	float m_maxDelta ;
	int m_iterNumber;
	int m_filterStep;
	float m_filterValue;

	void FilterHeightMap();



public:
	FaultFormation(int, Vector3<float>, Vector3<float>, int, int, float, float, int, int, float);
	virtual void FillHeightMap();

};

#endif
