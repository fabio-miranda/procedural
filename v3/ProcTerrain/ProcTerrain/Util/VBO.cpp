#include "VBO.h"


VBO::VBO(Vertex vertices[], int verticesSize, GLushort indices[], int indicesSize){

	m_verticesSize = verticesSize;
	m_indicesSize = indicesSize;
	m_ptrIndices = indices;
	m_ptrVertices = vertices;

	// Generate And Bind The Vertex Buffer
	glGenBuffersARB( 1, &m_vboVertices );					// Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_vboVertices );			// Bind The Buffer
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_verticesSize*sizeof(Vertex), vertices, GL_STATIC_DRAW_ARB);

	// Generate And Bind The Indix Buffer
	glGenBuffersARB(1, &m_vboIndices);					// Get A Valid Name
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_vboIndices);			// Bind The Buffer
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_indicesSize*sizeof(GLushort), indices, GL_STATIC_DRAW_ARB);



}
/*
void VBO::IncreaseVertexSize(int add){
	m_vertexSize+=add;
}

void VBO::IncreaseIndexSize(int add){
	m_indexSize+=add;
}

int VBO::GetVertexSize(){
	return m_vertexSize;
}
*/
/*
int VBO::GetIndexSize(){
	return m_listIndex.size();
}
*/

VBO::~VBO(){
	DeleteBuffer();

	delete [] m_ptrIndices;
	delete [] m_ptrVertices;

}


void VBO::DeleteBuffer(){

	//Delete the buffers
	//glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_vboVertices );
	//glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_listVertex.size()*sizeof(Vertex), NULL, GL_DYNAMIC_DRAW_ARB);
	glDeleteBuffersARB(1, &m_vboVertices);

	//glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, m_vboIndices );
	//glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_listIndex.size()*sizeof(GLuint), NULL, GL_DYNAMIC_DRAW_ARB);
	glDeleteBuffersARB(1, &m_vboIndices);

}


void VBO::Render(){

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_vboIndices);
	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_vboVertices);
	

	glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), &m_ptrVertices[0].x);
	glTexCoordPointer(2,GL_FLOAT,sizeof(Vertex),&m_ptrVertices[0].u);
	
	
	//glIndexPointer(GL_UNSIGNED_SHORT, 0, 0);

	//TODO: remove the if/else verification each frame (passing the conf_wire_frame to the glPolygonMode
	if(conf_showWireFrame)
		glPolygonMode(GL_FRONT, GL_LINE);
	else
		glPolygonMode(GL_FRONT, GL_FILL);
		

	glDrawElements( GL_TRIANGLES, m_indicesSize, GL_UNSIGNED_SHORT, m_ptrIndices);


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	
	
	glPolygonMode(GL_FRONT, GL_FILL);
	
}