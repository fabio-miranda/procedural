#include "stdafx.h"
#include "Node.h"
#include "GL/glew.h"
#include "gl/glfw.h"
#include <IL/il.h>
#include "glsl.h"


Node::Node(){


}

void Node::Render(bool wireFrame, int colorToRender){

	//cout << &(this->m_children);
	//cout << "\n";

	for (m_iterator = m_children.begin(); m_iterator != m_children.end(); m_iterator++ )
	{

		//cout << "Caiu!!";

		Node& node = **m_iterator;

		node.Render(wireFrame,colorToRender);


		

		
	}
}

bool Node::IsWithin(Vector3<float> position){
	return false;
}

void Node::GenerateNeighbours(Node*){


}

Node* Node::FindCurrentStandingNode(Vector3<float> cam_position){
	return NULL;


}
