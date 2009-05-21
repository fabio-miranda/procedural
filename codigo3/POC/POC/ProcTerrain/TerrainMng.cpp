#include "TerrainMng.h"


TerrainMng::TerrainMng()
{
	//Init glew
	int err=glewInit();
	if(err!=GLEW_OK)
	{
		//exit();
	}

	m_sceneGraph = new Node(Vector3<float>(0, 0, 0));
	
	

}



void TerrainMng::Update(Vector3<float> currentPosition){
	
	//See if the camera is on another node. If so, we have to generate its neighbours
	if(m_currentNode->IsWithin(currentPosition) == false){
		m_currentNode = m_currentNode->FindCurrentNode(currentPosition);
	}
	

}

void TerrainMng::Render(){

	m_sceneGraph->Render();

}

void TerrainMng::AddNode(Node* node){
	m_sceneGraph->AddNode(node);

}

void TerrainMng::SetCurrentNode(Node* node){
	m_currentNode = node;

}

