#include "VBO.h"


VBO::VBO(Vertex vertices[4], int verticesSize, GLushort indices[4], int indicesSize){

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
	
	//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_vboIndices);
	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_vboVertices);
	

    glVertexPointer( 3, GL_FLOAT, 0, m_ptrVertices);

	
	
	//glIndexPointer(GL_UNSIGNED_SHORT, 0, 0);

	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	glDrawElements( PRIMITIVE_RENDER, m_indicesSize, GL_UNSIGNED_SHORT, m_ptrIndices);


	glDisableClientState(GL_VERTEX_ARRAY);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
	
	
	
	
}