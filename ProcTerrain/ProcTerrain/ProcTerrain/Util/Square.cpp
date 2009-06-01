#include "Square.h"

Square::Square(){
	Init();

}

Square::Square(float size){
	Init();

	m_size = size;

}

Square::Square(Vector3<float> position, float size, int numDivisions) {
	Init();

	m_position = position;	
	m_size = size;
	m_numDivisions = numDivisions;
	//m_vboMesh = new VBO();
	
	int numVertices = 4 + (m_numDivisions-1)*4 + (m_numDivisions-1)*(m_numDivisions-1);
	int numIndices = m_numDivisions*m_numDivisions*6;

	m_vertices = new Vertex[numVertices];
	m_indices = new GLushort[numIndices];

	float sizeby2 = m_size/2.0f;
	float divisionSize = m_size/m_numDivisions;
	int cont = 0;
	for(float i=-sizeby2; i<=sizeby2; i+=divisionSize){
		for(float j=-sizeby2; j<=sizeby2; j+=divisionSize){
			m_vertices[cont].x = m_position.GetX() +i; m_vertices[cont].y = m_position.GetY() +j;	m_vertices[cont].z = m_position.GetZ();
			m_vertices[cont].v = (i+sizeby2) / m_size; m_vertices[cont].u = (j+sizeby2) / m_size;

			cont++;

		}
	}

	cont = 0; //counts the number of squares rendered
	int coluns = 0; //counts the coluns rendered

	//numIndices = 18;
	//numVertices = 8;
	for(int i=0; i<numIndices; i+=6){
		m_indices[i] = cont + coluns;
		m_indices[i+1] = cont + coluns + 1 + m_numDivisions;
		m_indices[i+2] = cont + coluns + 2 + m_numDivisions;
	
		m_indices[i+3] = cont + coluns + 2 + m_numDivisions;
		m_indices[i+4] = cont + coluns + 1;
		m_indices[i+5] = cont + coluns;

		cont++;
		
		//If it reaches the limit of the square, it adds two to the count
		if(cont % m_numDivisions == 0)
			coluns++;
	}
	
	/*
	m_indices[0] = 0;
	m_indices[1] = 2;
	m_indices[2] = 3;
	m_indices[3] = 3;
	m_indices[4] = 1;
	m_indices[5] = 0;
	*/
	
	m_vboMesh = new VBO(m_vertices, numVertices, m_indices, numIndices);


}

Square::~Square(){
	m_vboMesh->DeleteBuffer();

	delete [] m_vertices;
	delete [] m_indices;

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



void Square::Render(){
	
	//m_vboMesh->Render();
	glBegin( GL_TRIANGLES );

		glTexCoord2d(0.0,0.0); glVertex3f(0, 0, 0.0f);				// Top Left
		glTexCoord2d(1.0,0.0); glVertex3f( 250, 0, 0.0f);				// Top Right
		glTexCoord2d(1.0,1.0); glVertex3f( 250,250, 0.0f);				// Bottom Right
		glTexCoord2d(0.0,1.0); glVertex3f(0,250, 0.0f);
	glEnd();
	
	
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