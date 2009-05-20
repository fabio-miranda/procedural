#ifndef TerrainMng_H
#define TerrainMng_H

#include "GL/glew.h"
#include "Util/Random.h"
#include "Util/Vector3.h"
#include "Scene/Node.h"



class TerrainMng{

	

public:
	TerrainMng();
	void Update(Vector3<float>);
	void Render();
	void AddNode(Node*);

private:
	Node* m_sceneGraph;
};

#endif