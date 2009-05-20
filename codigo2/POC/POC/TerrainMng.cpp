#include "TerrainMng.h"


TerrainMng::TerrainMng()
{
	m_sceneGraph = new Node();


}



void TerrainMng::Update(Vector3<float> currentPosition){

}

void TerrainMng::Render(){

	m_sceneGraph->Render();

}