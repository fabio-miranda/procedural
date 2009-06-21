#ifndef VBOSQUARE_H
#define VBOSQUARE_H


#include "Vertex.h"
#include "Vector3.h"
#include "VBO.h"
#include <math.h>
#include <list>



class VBOSquare{
	
	/////////////
	// 3------2
	// |      |
	// |      |
	// 0------1
	////////////
private:
	void Init();
		
	Vertex* m_vertices;
	GLushort* m_indices;
	
	Vector3<float> m_position;
	VBO* m_vboMesh;
	float m_size;
	int m_numDivisions;
	bool m_isSplit;
	//std::list<GLuint>::iterator m_listIndexEndPosition;
	//std::list<Vertex>::iterator m_listVertexEndPosition;



public:

	VBOSquare();
	VBOSquare(float size);
	VBOSquare(Vector3<float> position, float size, int numDivisions);
	~ VBOSquare();
	//void FillArray(VBO*);
	//void SplitSquareIn4();
	void Render();

	//Square* m_squares[4]; //The subdivisions of the big square
	//Square* m_parent;
	

};

#endif