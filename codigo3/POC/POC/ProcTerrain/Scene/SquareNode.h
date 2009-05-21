#ifndef SQUARENODE_H
#define SQUARENODE_H



#include "../Util/Vertex.h"
#include "../Util/Square.h"
#include "Node.h"


class SquareNode : public Node{
	
	void Render();
	void Update();

	

	float m_size;
	


	//Cube
	Square* m_face;
	int m_numDivisions;


public:
	SquareNode(Vector3<float> position, float size, int num_divisions);
	~ SquareNode();
	bool IsWithin(Vector3<float>);
	//void IncreaseDivisions(int numNewDivisions);
	

};

#endif