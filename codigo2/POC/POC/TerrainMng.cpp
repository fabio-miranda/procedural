#include "TerrainMng.h"


TerrainMng::TerrainMng()
{
	m_sceneGraph = new Node();


}



void TerrainMng::Update(){

}

void TerrainMng::Render(){

	m_sceneGraph->Render();

}