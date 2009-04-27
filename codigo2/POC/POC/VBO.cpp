#include "VBO.h"


VBO::VBO(){


	//m_vertexSize = vertexSize;
	//m_indexSize = indexSize;

	//m_oldVertexSize = m_vertexSize;
	//m_oldIndexSize = m_indexSize;

	//m_vertexArray = new Vertex[m_vertexSize];
	//m_indexArray = new GLuint[m_indexSize];

	// Generate And Bind The Vertex Buffer
	glGenBuffersARB( 1, &m_vboVertices );					// Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_vboVertices );			// Bind The Buffer

	// Generate And Bind The Indix Buffer
	glGenBuffersARB(1, &m_vboIndices);					// Get A Valid Name
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_vboIndices);			// Bind The Buffer


	VBO::FillBuffer();

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
int VBO::GetIndexSize(){
	return m_listIndex.size();
}


void VBO::DeleteBuffer(){

	//Delete the buffers
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_vboVertices );
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_listVertex.size()*sizeof(Vertex), NULL, GL_DYNAMIC_DRAW_ARB);

	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, m_vboIndices );
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_listIndex.size()*sizeof(GLuint), NULL, GL_DYNAMIC_DRAW_ARB);

}

void VBO::FillBuffer(){


	//Replace the buffers
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_vboVertices );
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, ((int)m_listVertex.size())*sizeof(Vertex), &m_listVertex, GL_DYNAMIC_DRAW_ARB);

	glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, m_vboIndices );
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, ((int)m_listIndex.size())*sizeof(GLuint), &m_listIndex, GL_DYNAMIC_DRAW_ARB);

	//m_oldVertexSize = m_vertexSize;
	//m_oldIndexSize = m_indexSize;

}

void VBO::Render(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer( 3, GL_FLOAT, 0, 0);

	
	glPolygonMode(GL_FRONT, GL_LINE);
	glDrawElements( GL_QUADS, m_listIndex.size(), GL_UNSIGNED_INT, 0);


	glDisableClientState(GL_VERTEX_ARRAY);

}