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
	//m_vboMesh = new VBO();
	
	
	float sizeby2 = m_size/2.0f;

	m_vertices[0].x = m_position.GetX() - sizeby2; m_vertices[0].y = m_position.GetY() + sizeby2;	m_vertices[0].z = m_position.GetZ();
	m_vertices[1].x = m_position.GetX() + sizeby2; m_vertices[1].y = m_position.GetY() + sizeby2;	m_vertices[1].z = m_position.GetZ();
	m_vertices[2].x = m_position.GetX() + sizeby2; m_vertices[2].y = m_position.GetY() - sizeby2; m_vertices[2].z = m_position.GetZ();
	m_vertices[3].x = m_position.GetX() - sizeby2; m_vertices[3].y = m_position.GetY() - sizeby2; m_vertices[3].z = m_position.GetZ();

	//m_listVertexEndPosition = m_vboMesh->m_listVertex.end();
	
	

	//m_vboMesh->m_listVertex.push_back(*vertices[0]);
	//m_vboMesh->m_listVertex.push_back(*vertices[1]);
	//m_vboMesh->m_listVertex.push_back(*vertices[2]);
	//m_vboMesh->m_listVertex.push_back(*vertices[3]);

	m_indices[0] = 0;
	m_indices[1] = 1;
	m_indices[2] = 2;
	m_indices[3] = 2;
	m_indices[4] = 3;
	m_indices[5] = 0;

	
	//m_listIndexEndPosition = m_vboMesh->m_listIndex.end();

	//m_vboMesh->m_listIndex.push_back(*indices[0]);
	//m_vboMesh->m_listIndex.push_back(*indices[1]);
	//m_vboMesh->m_listIndex.push_back(*indices[2]);
	//m_vboMesh->m_listIndex.push_back(*indices[3]);

	
	//m_vboMesh->FillBuffer();
	
	m_vboMesh = new VBO(m_vertices, 4, m_indices, 6);


}

void Square::Init(){


	m_isSplit = false;
	/*
	for(int i=0; i<4; i++){
		m_vertices[i] = new Vertex();
		m_indices[i] = new GLuint();
	}
	*/

}

Square::~Square(){
	m_vboMesh->DeleteBuffer();

}

void Square::Render(){
	
	m_vboMesh->Render();
	/*
	glBegin( GL_TRIANGLES );

		glVertex3f(-25.0f, 25.0f, 0.0f);				// Top Left
		glVertex3f( 25.0f, 25.0f, 0.0f);				// Top Right
		glVertex3f( 25.0f,-25.0f, 0.0f);				// Bottom Right
		//glVertex3f(-25.0f,-25.0f, 0.0f);

	glEnd();
	*/
}

/*
void Square::FillArray(VBO* m_vboMesh){


	//int vertexSize = m_vboMesh->m_listVertex.size();
	int indexSize = m_vboMesh->m_listIndex.size();


	for(int i=0; i<4; i++){
		if(*m_indices[i] >= m_vboMesh->m_listVertex.size())
			m_vboMesh->m_listVertex.push_back(*m_vertices[i]);
	}
	
	if(m_isSplit){

		for(int i=0; i<4; i++){
			m_squares[i]->FillArray(m_vboMesh);
		}
	}
	else{
		//We only draw the ones in the bottom of the graph
		for(int i=0; i<4; i++){
			m_vboMesh->m_listIndex.push_back(*m_indices[i]);
		}

	}
}
*/

/*
void Square::SplitSquareIn4(){

	//m_parentCube->IncreaseDivisions(4);
	//num_divisions *=4;

	m_isSplit = true;

	for(int i=0; i<4; i++){
		m_squares[i] = new Square(m_size / 2.0f);
		m_squares[i]->m_parent = this;
	}
*/
	//Delete the positions on the index array
	/*
	advance(m_listIndexEndPosition, -4);
	advance(m_listVertexEndPosition, -4);
	for(int i=0; i<4; i++){
		m_listIndexEndPosition = m_vboMesh->m_listIndex.erase(m_listIndexEndPosition);
		m_listVertexEndPosition = m_vboMesh->m_listVertex.erase(m_listVertexEndPosition);
	}
	*/
	
	/////////////
	// 3------2
	// |      |
	// |      |
	// 0------1
	////////////
/*
	//0
	m_squares[0]->m_vertices[0] = m_vertices[0];
	m_vboMesh->m_listVertex.push_back(*m_squares[0]->m_vertices[0]);
	m_squares[0]->m_indices[0] = m_indices[0];
	m_vboMesh->m_listIndex.push_back(*m_squares[0]->m_indices[0]);

	m_squares[0]->m_vertices[1] = MidPoint(*(m_squares[0]->m_vertices[0]), *(m_vertices[1]));
	m_vboMesh->m_listVertex.push_back(*m_squares[0]->m_vertices[1]);
	*m_squares[0]->m_indices[1] = m_vboMesh->m_listVertex.size() -1;
	m_vboMesh->m_listIndex.push_back(*m_squares[0]->m_indices[1]);

	m_squares[0]->m_vertices[2] = MidPoint(*(m_vertices[0]), *(m_vertices[2]));
	m_vboMesh->m_listVertex.push_back(*m_squares[0]->m_vertices[2]);
	*m_squares[0]->m_indices[2] = m_vboMesh->m_listVertex.size() -1;
	m_vboMesh->m_listIndex.push_back(*m_squares[0]->m_indices[2]);

	m_squares[0]->m_vertices[3] = MidPoint(*(m_vertices[0]), *(m_vertices[3]));
	m_vboMesh->m_listVertex.push_back(*m_squares[0]->m_vertices[3]);
	*m_squares[0]->m_indices[3] = m_vboMesh->m_listVertex.size()-1;
	m_vboMesh->m_listIndex.push_back(*m_squares[0]->m_indices[3]);

	//1
	m_squares[1]->m_vertices[0] = m_squares[0]->m_vertices[1];
	m_squares[1]->m_indices[0] = m_squares[0]->m_indices[1];
	m_vboMesh->m_listIndex.push_back(*m_squares[1]->m_indices[0]);

	m_squares[1]->m_vertices[1] = m_vertices[1];
	m_vboMesh->m_listVertex.push_back(*m_squares[1]->m_vertices[1]);
	m_squares[1]->m_indices[1] = m_indices[1];
	m_vboMesh->m_listIndex.push_back(*m_squares[1]->m_indices[1]);

	m_squares[1]->m_vertices[2] = MidPoint(*(m_vertices[1]), *(m_vertices[2]));
	m_vboMesh->m_listVertex.push_back(*m_squares[1]->m_vertices[2]);
	*m_squares[1]->m_indices[2] = m_vboMesh->m_listVertex.size()-1;
	m_vboMesh->m_listIndex.push_back(*m_squares[1]->m_indices[2]);


	m_squares[1]->m_vertices[3] = m_squares[0]->m_vertices[2];
	m_squares[1]->m_indices[3] = m_squares[0]->m_indices[2];
	m_vboMesh->m_listIndex.push_back(*m_squares[1]->m_indices[3]);

	//2
	m_squares[2]->m_vertices[0] = m_squares[0]->m_vertices[2];
	m_squares[2]->m_indices[0] = m_squares[0]->m_indices[2];
	m_vboMesh->m_listIndex.push_back(*m_squares[2]->m_indices[0]);

	m_squares[2]->m_vertices[1] = m_squares[1]->m_vertices[2];
	m_squares[2]->m_indices[1] = m_squares[1]->m_indices[2];
	m_vboMesh->m_listIndex.push_back(*m_squares[2]->m_indices[1]);

	m_squares[2]->m_vertices[2] = m_vertices[2];
	m_vboMesh->m_listVertex.push_back(*m_squares[2]->m_vertices[2]);
	m_squares[2]->m_indices[2] = m_indices[2];
	m_vboMesh->m_listIndex.push_back(*m_squares[2]->m_indices[2]);

	m_squares[2]->m_vertices[3] = MidPoint(*(m_vertices[2]), *(m_vertices[3]));
	m_vboMesh->m_listVertex.push_back(*m_squares[2]->m_vertices[3]);
	*m_squares[2]->m_indices[3] = m_vboMesh->m_listVertex.size()-1;
	m_vboMesh->m_listIndex.push_back(*m_squares[2]->m_indices[3]);


	//3
	m_squares[3]->m_vertices[0] = m_squares[0]->m_vertices[3];
	m_squares[3]->m_indices[0] = m_squares[0]->m_indices[3];
	m_vboMesh->m_listIndex.push_back(*m_squares[3]->m_indices[0]);

	m_squares[3]->m_vertices[1] = m_squares[0]->m_vertices[2];
	m_squares[3]->m_indices[1] = m_squares[0]->m_indices[2];
	m_vboMesh->m_listIndex.push_back(*m_squares[3]->m_indices[1]);

	m_squares[3]->m_vertices[2] = m_squares[2]->m_vertices[3];
	m_squares[3]->m_indices[2] = m_squares[2]->m_indices[3];
	m_vboMesh->m_listIndex.push_back(*m_squares[3]->m_indices[2]);

	m_squares[3]->m_vertices[3] = m_vertices[3];
	m_vboMesh->m_listVertex.push_back(*m_squares[3]->m_vertices[3]);
	m_squares[3]->m_indices[3] = m_indices[3];
	m_vboMesh->m_listIndex.push_back(*m_squares[3]->m_indices[3]);


}
*/