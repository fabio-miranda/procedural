#ifndef SQUARENODE_H
#define SQUARENODE_H



#include "../Util/Vertex.h"
#include "../Util/VBOSquare.h"
#include "../Util/HeightMap.h"
#include "Node.h"
#include "../Shaders/RenderingShader.h"
#include "../Shaders/GenerationShader.h"
#include "../Util/FBO.h"
#include <math.h>


class SquareNode{
	
	
	void Update();
	
	
	short m_numNeighbours;
	short m_numDivisions;
	VBOSquare* m_face;
	
	
	float m_geomSize;
	int m_textureSize;
	RenderingShader* m_ptrTerrainRenderingShader;

	
	



public:
	SquareNode(GenerationShader* generationShader, RenderingShader* renderingShader, Vector3<float> position, Vector3<float> translation, float geomSize, int textureSize, short numDivisions);
	~ SquareNode();
	void Render(double);
	void GenerateNeighbours(SquareNode* m_oldNode, bool generateFromScratch, short gridIndex, Vector3<float> relativePosition, Vector3<float> translation, short numNeighbours);
	void GenerateFromScratch(SquareNode* oldNode, short index, Vector3<float> position, Vector3<float> translation, short numDivisions, short numNeighbours);
	void GenerateJustHeightMap(SquareNode* oldNode, short index, Vector3<float> relativePosition, Vector3<float> translation, short numNeighbours);
	bool IsWithin(Vector3<float>);
	short GetNewStandingNodePosition(Vector3<float>);
	//void SetNumNeighbours(short);
	//void AddNode(int, Node*);
	//void IncreaseDivisions(int numNewDivisions);


	short m_gridIndex; //the index of the node, relative to the m_currentNode
	Vector3<float> m_relativePosition;
	Vector3<float> m_globalPosition;
	

	HeightMap* m_heightMap;
	

};

#endif