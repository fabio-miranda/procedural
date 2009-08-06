#ifndef SIMPLESQUARE_H
#define SIMPLESQUARE_H


#include "Vertex.h"
#include "Vector3.h"
#include "VBO.h"
#include <list>



class SimpleSquare{
	
	/////////////
	// 3------2
	// |      |
	// |      |
	// 0------1
	////////////
private:
	float m_geomSize;
	float m_textureSize;
	Vector3<float> m_position;



public:

	SimpleSquare(Vector3<float>, float, float);
	~ SimpleSquare();
	void Render();
	

};

#endif