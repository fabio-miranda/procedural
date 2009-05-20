#ifndef SQUARE_H
#define SQUARE_H


#include "Vertex.h"
#include "Vector3.h"
#include "VBO.h"
#include <list>



class Square{
	
	/////////////
	// 3------2
	// |      |
	// |      |
	// 0------1
	////////////
private:
	void Init();
		
	//Vertex* m_vertices[4];
	//GLuint* m_indices[4];
	
	Vector3<float> m_position;
	VBO* m_vboMesh;
	float m_size;
	bool m_isSplit;
	//std::list<GLuint>::iterator m_listIndexEndPosition;
	//std::list<Vertex>::iterator m_listVertexEndPosition;



public:

	Square();
	Square(float size);
	Square(Vector3<float> position, float size);
	~ Square();
	//void FillArray(VBO*);
	//void SplitSquareIn4();
	void Render();

	//Square* m_squares[4]; //The subdivisions of the big square
	//Square* m_parent;
	

};

#endif