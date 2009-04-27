#include "Square.h"

Square::Square(){
	Init();

}

Square::Square(float size){
	Init();

	m_size = size;

}

Square::Square(Vector3<float> position, float size) {
	Init();

	m_position = position;	
	m_size = size;
	


	m_vertices[0]->x = m_position.GetX();		   m_vertices[0]->y = m_position.GetY();			m_vertices[0]->z = m_position.GetZ();
	m_vertices[1]->x = m_position.GetX() + m_size; m_vertices[1]->y = m_position.GetY();			m_vertices[1]->z = m_position.GetZ();
	m_vertices[2]->x = m_position.GetX() + m_size; m_vertices[2]->y = m_position.GetY() + m_size;   m_vertices[2]->z = m_position.GetZ();
	m_vertices[3]->x = m_position.GetX();		   m_vertices[3]->y = m_position.GetY() + m_size;	m_vertices[3]->z = m_position.GetZ();

	*m_indices[0] = 0;
	*m_indices[1] = 1;
	*m_indices[2] = 2;
	*m_indices[3] = 3;


}

void Square::Init(){


	m_isSplit = false;

	for(int i=0; i<4; i++){
		m_vertices[i] = new Vertex();
		m_indices[i] = new GLuint();
	}

}

Square::~Square(){


}


void Square::FillArray(VBO* vboMesh){


	//int vertexSize = vboMesh->m_vectorVertex.size();
	int indexSize = vboMesh->m_vectorIndex.size();


	for(int i=0; i<4; i++){
		if(*m_indices[i] >= vboMesh->m_vectorVertex.size())
			vboMesh->m_vectorVertex.push_back(*m_vertices[i]);
	}
	
	if(m_isSplit){

		for(int i=0; i<4; i++){
			m_squares[i]->FillArray(vboMesh);
		}
	}
	else{
		//We only draw the ones in the bottom of the graph
		for(int i=0; i<4; i++){
			vboMesh->m_vectorIndex.push_back(*m_indices[i]);
		}

	}
	
	
	

}


void Square::SplitSquareIn4(int& num_divisions){

	//m_parentCube->IncreaseDivisions(4);
	num_divisions *=4;

	m_isSplit = true;

	for(int i=0; i<4; i++){
		m_squares[i] = new Square(m_size / 2.0f);
		m_squares[i]->m_parent = this;
	}
	
	/////////////
	// 3------2
	// |      |
	// |      |
	// 0------1
	////////////

	//0
	m_squares[0]->m_vertices[0] = m_vertices[0];
	m_squares[0]->m_indices[0] = m_indices[0];
	m_squares[0]->m_vertices[1] = MidPoint(*(m_squares[0]->m_vertices[0]), *(m_vertices[1]));
	*m_squares[0]->m_indices[1] = num_divisions;
	m_squares[0]->m_vertices[2] = MidPoint(*(m_vertices[0]), *(m_vertices[2]));
	*m_squares[0]->m_indices[2] = num_divisions + 1;
	m_squares[0]->m_vertices[3] = MidPoint(*(m_vertices[0]), *(m_vertices[3]));
	*m_squares[0]->m_indices[3] = num_divisions + 2;

	//1
	m_squares[1]->m_vertices[0] = m_squares[0]->m_vertices[1];
	m_squares[1]->m_indices[0] = m_squares[0]->m_indices[1];
	m_squares[1]->m_vertices[1] = m_vertices[1];
	m_squares[1]->m_indices[1] = m_indices[1];
	m_squares[1]->m_vertices[2] = MidPoint(*(m_vertices[1]), *(m_vertices[2]));
	*m_squares[1]->m_indices[2] = num_divisions + 3;
	m_squares[1]->m_vertices[3] = m_squares[0]->m_vertices[2];
	m_squares[1]->m_indices[3] = m_squares[0]->m_indices[2];

	//2
	m_squares[2]->m_vertices[0] = m_squares[0]->m_vertices[2];
	m_squares[2]->m_indices[0] = m_squares[0]->m_indices[2];
	m_squares[2]->m_vertices[1] = m_squares[1]->m_vertices[2];
	m_squares[2]->m_indices[1] = m_squares[1]->m_indices[2];
	m_squares[2]->m_vertices[2] = m_vertices[2];
	m_squares[2]->m_indices[2] = m_indices[2];
	m_squares[2]->m_vertices[3] = MidPoint(*(m_vertices[2]), *(m_vertices[3]));
	*m_squares[2]->m_indices[3] = num_divisions + 4;

	//3
	m_squares[3]->m_vertices[0] = m_squares[0]->m_vertices[3];
	m_squares[3]->m_indices[0] = m_squares[0]->m_indices[3];
	m_squares[3]->m_vertices[1] = m_squares[0]->m_vertices[2];
	m_squares[3]->m_indices[1] = m_squares[0]->m_indices[2];
	m_squares[3]->m_vertices[2] = m_squares[2]->m_vertices[3];
	m_squares[3]->m_indices[2] = m_squares[2]->m_indices[3];
	m_squares[3]->m_vertices[3] = m_vertices[3];
	m_squares[3]->m_indices[3] = m_indices[3];


}
