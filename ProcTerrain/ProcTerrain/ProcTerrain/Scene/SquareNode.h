#ifndef SQUARENODE_H
#define SQUARENODE_H



#include "../Util/Vertex.h"
#include "../Util/Square.h"
#include "Node.h"
#include "../Shaders/Shader.h"
#include "../Util/FBO.h"


class SquareNode{
	
	
	void Update();
	void GenerateHeightMap();
	
	

	
	Vector3<float> m_position;
	float m_size;
	short m_numNeighbours;
	

	Shader *m_ptrTerrainGenerationShader;
	Shader *m_ptrTerrainRenderingShader;
	FBO *m_ptrFBO;
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
	bool m_firstTime;
	//short m_numNeighbours;


public:
	SquareNode(Shader*, Shader*, FBO*, Vector3<float>, float, short);
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