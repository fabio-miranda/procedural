#ifndef TerrainMng_H
#define TerrainMng_H


#include "Random.h"
#include "Vector3.h"
#include "Node.h"
#include "GL/glew.h"
#include "GL/glfw.h"


class TerrainMng{

	

public:
	TerrainMng();
	void Update(Vector3<float>);
	void Render();

private:
	Node* m_sceneGraph;
};

#endif