#include "HeightMap.h"


HeightMap::HeightMap(RenderingShader* renderingShader, Vector3<float> relativePosition, Vector3<float> translation, 
					 float geomSize, short numDivisions,
					 int octaves, float lacunarity, float gain, float offset){
	

	m_ptrRenderingShader = renderingShader;

	m_relativePosition = relativePosition;
	m_globalPosition = relativePosition;
	m_globalPosition.Add(translation);

	m_geomSize = geomSize;
	m_generated = false;
	m_numDivisions = numDivisions;

	m_time = 5.0f; //time since the generation of the heightmap

	m_face = new VBOSquare(m_relativePosition, m_geomSize, m_numDivisions);

	//
	m_octaves = octaves;
	m_lacunarity = lacunarity;
	m_gain = gain;
	m_offset = offset;
	
	
}

//TODO: delete properly
HeightMap::~HeightMap(){

}

void HeightMap::Render(double elapsedTime){

}

void HeightMap::Generate(){

}

void HeightMap::ReGenerate(Vector3<float> newPosition){

}

void HeightMap::Delete(){

}
