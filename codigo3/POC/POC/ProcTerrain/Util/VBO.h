#ifndef VBO_H
#define VBO_H


#include "GL/glew.h"
//#include "GL/glfw.h"
#include "Vertex.h"
#include "../Config.h"
#include <list>

class VBO{

private:
	GLuint m_vboVertices;
	GLuint m_vboIndices;

	int m_verticesSize;
	int m_indicesSize;

	GLushort* m_ptrIndices;
	Vertex* m_ptrVertices;

	//int m_vertexSize;
	//int m_indexSize;

	//The m_vertexSize and m_indexSize are modified on the CubeSphere::FillArray. This is just a preccaution to make sure
	//that we delete the right size from the buffer
	//int m_oldVertexSize;
	//int m_oldIndexSize;
	


public:

	VBO(Vertex[4], int, GLushort[4], int);
	void DeleteBuffer();
	//void InitBuffer();
	void Render();

	//Vertex* m_vertexArray;
	//GLuint* m_indexArray;

	//std::list<Vertex> m_listVertex;
	//std::list<GLuint> m_listIndex;

	//void IncreaseVertexSize(int);
	//void IncreaseIndexSize(int);

	//int GetVertexSize();
	//int GetIndexSize();
	

	
	
	

};

#endif