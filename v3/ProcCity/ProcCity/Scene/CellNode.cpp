#include "CellNode.h"

CellNode::CellNode(){


}


void CellNode::SetVertices(int numVertices, double* vertices, double* position){
	m_numVertices = numVertices;
	m_vertices = vertices;
	m_position = new Vector3<double>(position[0], position[1], position[2]);


}

void CellNode::Update(){
	Node::Update();

}

void CellNode::Render(){
	Node::Render();

	Vector3<double> aux;
	glBegin(GL_LINES);
	for(int i=0; i<m_numVertices; i+=3){
		
		aux = Vector3<double>(m_position->GetX() - m_vertices[i],
							  m_position->GetY() - m_vertices[i+1],
							  m_position->GetZ() - m_vertices[i+2]);
		//aux.Normalize();

		glVertex3d(m_vertices[i] + 0.15*(aux.GetX()),
				  m_vertices[i+1] + 0.15*(aux.GetY()),
				  m_vertices[i+2] + 0.15*(aux.GetZ()));
	}
	glEnd();


}

