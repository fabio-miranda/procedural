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
	int m_width;
	int m_height;



public:

	SimpleSquare(short, short);
	~ SimpleSquare();
	void Render();
	

};

#endif