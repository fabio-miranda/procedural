#ifndef SQUARENODE_H
#define SQUARENODE_H



#include "../Util/Vertex.h"
#include "../Util/Square.h"
#include "Node.h"


class SquareNode{
	
	
	void Update();
	
	

	
	Vector3<float> m_position;
	float m_size;
	


	//Cube
	Square* m_face;

	SquareNode* m_ptrNeighbours[8]; //pointer to the neighbours. It's easy to get a particular node, because it is in an an array:
								/*
								Left
								|   Right
								|   |
								2 4 7 -> TOP
								1 c 6
								0 3 5 -> BOTTOM
								*/
	
	short m_numDivisions;
	//short m_numNeighbours;


public:
	SquareNode(Vector3<float>, float, short);
	~ SquareNode();
	void Render();
	void GenerateNeighbours(SquareNode*, short);
	bool IsWithin(Vector3<float>);
	SquareNode* GetNewStandingNode(Vector3<float>);
	//void SetNumNeighbours(short);
	//void AddNode(int, Node*);
	//void IncreaseDivisions(int numNewDivisions);


	int m_gridIndex; //the index of the node, relative to the m_currentNode
	

};

#endif