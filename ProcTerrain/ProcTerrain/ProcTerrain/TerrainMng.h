#ifndef TerrainMng_H
#define TerrainMng_H

#include "GL/glew.h"
#include "Util/Random.h"
#include "Util/Vector3.h"
#include "Scene/SquareNode.h"
#include "Util/Gui.h"
#include "Shaders/GenerationShader.h"
#include "Shaders/RenderingShader.h"
#include "Util/FBO.h"
#include "Defines.h"



class TerrainMng{

	

public:
	TerrainMng();
	void Update(Vector3<float>);
	void Render(double);


	GUI* m_gui;
	RenderingShader* m_terrainRenderingShader;
	GenerationShader* m_terrainGenerationShader;
	FBO* m_fbo;
	char* m_permArray;

private:

	SquareNode* m_currentNode;

	void Config();
	void initPermAndGradTextures();
	void initLight();
	void initNodes();
	void GenerateNeighbours(short oldIndex, short newIndex);

	GLuint m_permTextureID;
	GLuint m_permGradTextureID;
	Vector3<float> m_translation;
	int m_size;

	SquareNode** m_ptrNodes; //pointer to a matriz of nodes. It's easy to get a particular node, because it is in an an array:
								/*
								Left
								|   Right
								|   |
								2 4 7 -> TOP
								1 c 6
								0 3 5 -> BOTTOM
								*/

};

#endif