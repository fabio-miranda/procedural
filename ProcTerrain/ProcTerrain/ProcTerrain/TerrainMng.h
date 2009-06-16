#ifndef TerrainMng_H
#define TerrainMng_H

#include "GL/glew.h"
#include "Util/Random.h"
#include "Util/Vector3.h"
#include "Scene/Node.h"
#include "Scene/SquareNode.h"
#include "Util/Gui.h"
#include "Shaders/GenerationShader.h"
#include "Shaders/RenderingShader.h"
#include "Util/FBO.h"



class TerrainMng{

	

public:
	TerrainMng();
	void Update(Vector3<float>);
	void Render();
	void AddNode(Node*);
	void SetCurrentNode(SquareNode*);


	GUI* m_gui;
	RenderingShader* m_terrainRenderingShader;
	GenerationShader* m_terrainGenerationShader;
	FBO* m_fbo;

private:

	Node* m_sceneGraph;
	SquareNode* m_currentNode;
	void Config();
	void initPermAndGradTextures();

	GLuint m_permTextureID;
	GLuint m_permGradTextureID;
};

#endif