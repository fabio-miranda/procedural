#ifndef SQUARENODE_H
#define SQUARENODE_H



#include "../Util/Vertex.h"
#include "../Util/VBOSquare.h"
#include "../HeightMap/HeightMapGPU.h"
#include "../HeightMap/HeightMapCPU.h"
#include "../Shaders/RenderingShader.h"
#include "../Shaders/GenerationShader.h"
#include "../Util/FBO.h"
#include <windows.h>
#include <math.h>
#include <pthread.h>
#include <sched.h>



class SquareNode{
	
	
	void Update();
	
	
	short m_numNeighbours;
	short m_numDivisions;
	
	
	float m_geomSize;
	int m_textureSize;
	RenderingShader* m_ptrRenderingShader;
	GenerationShader* m_ptrGenerationShader;
	GLuint* m_ptrBlendTexturesId;
	char* m_ptrPermArray;

	
	



public:
	SquareNode(int index, GenerationShader* generationShader, RenderingShader* renderingShader, GLuint* ptrBlendTexturesId, char* ptrPermArray,
				Vector3<float> position, Vector3<float> translation, float geomSize, int textureSize, short numDivisions, SquareNode* neighbLeft, SquareNode* neighbDown);
	~ SquareNode();
	void Render(double);
	//void GenerateGPU(Vector3<float> relativePosition, Vector3<float> translation, int octaves, float lacunarity, float gain, float offset);
	//void GenerateCPU(Vector3<float> relativePosition, Vector3<float> translation, char* ptrPermArray, int octaves, float lacunarity, float gain, float offset);
	void Generate(Vector3<float> relativePosition, int octaves, float lacunarity, float gain, float offset);
	void ReGenerate(Vector3<float> newPosition);
	bool IsWithin(Vector3<float>);
	short GetNewStandingNodePosition(Vector3<float>, short);
	void Delete();

	//void SetNumNeighbours(short);
	//void AddNode(int, Node*);
	//void IncreaseDivisions(int numNewDivisions);


	int m_gridIndex; //the index of the node, relative to the m_currentNode
	Vector3<float> m_relativePosition;
	Vector3<float> m_globalPosition;
	

	HeightMap* m_heightMap;
	

};

#endif