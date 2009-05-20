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

}

void TerrainMng::Render(){

	m_sceneGraph->Render();

}

void TerrainMng::AddNode(Node* node){
	m_sceneGraph->AddNode(node);

}