#include "SquareNode.h"


SquareNode::SquareNode(Vector3<float> position, float size, int num_divisions) : Node(position){
	
	m_size = size;
	m_numDivisions = num_divisions;
	m_face = new Square(position, size);

	

	//m_face->SplitSquareIn4();
	//m_faces[0]->m_squares[0]->SplitSquareIn4(m_numDivisions);

	

	//Fill the arrays with the new data
	/*
	for(int i=0; i<1; i++){
		m_faces[i]->FillArray(m_vboMesh);
	}
	*/

	//m_vboMesh->FillBuffer();

	
	

}

SquareNode::~SquareNode(){
	//m_vboMesh->DeleteBuffer();

	//glDeleteBuffersARB(1, &m_vboColors);
	//m_vboColors =0;

}




void SquareNode::Render(){
	
	//Call the parent
	Node::Render();

	m_face->Render();

}

bool SquareNode::IsWithin(Vector3<float> position){
	if(position.GetX()  >= m_position.GetX() & position.GetX() <= m_position.GetX() + m_size)
		if(position.GetY()  >= m_position.GetY() & position.GetY() <= m_position.GetY() + m_size)
			return true;


	return false;

}
