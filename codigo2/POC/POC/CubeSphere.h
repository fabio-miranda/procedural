#ifndef CUBESPHERE_H
#define CUBESPHERE_H



#include "Vertex.h"
#include "Square.h"
#include "node.h"
#include "GL/glew.h"
#include "GL/glfw.h"




class CubeSphere : public Node{
	
	void Render();
	void Update();

	

	float m_size;
	


	//Cube
	Square* m_faces[6];
	int m_numDivisions;


public:
	CubeSphere(Vector3<float> position, float size, int num_divisions);
	~ CubeSphere();
	//void IncreaseDivisions(int numNewDivisions);
	

};

#endif