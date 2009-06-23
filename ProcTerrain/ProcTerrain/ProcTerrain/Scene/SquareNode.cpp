#include "SquareNode.h"



SquareNode::SquareNode(int index, GenerationShader* generationShader, RenderingShader* renderingShader, Vector3<float> relativePosition, Vector3<float> translation, float geomSize, int textureSize, short numDivisions, SquareNode* neighbLeft, SquareNode* neighbDown){
	
	
	m_ptrRenderingShader = renderingShader;
	m_ptrGenerationShader = generationShader;
	m_relativePosition = relativePosition;
	m_globalPosition = relativePosition;
	m_globalPosition.Add(translation);

	m_geomSize = geomSize;
	m_numDivisions = numDivisions;
	m_numNeighbours = 0;
	m_textureSize = textureSize;
	
	m_gridIndex = index; //center of the grid (currentNode)

	/*
	for(int i=0; i<8; i++){
		m_ptrNeighbours[i] = NULL;
	}
	*/
	
	//translation.Add(relativePosition);
	//m_heightMap = new HeightMap(generationShader, m_globalPosition, m_geomSize, textureSize, 1);
	//m_face = new VBOSquare(m_relativePosition, m_geomSize, m_numDivisions);


	
	
}

//TODO: Delete properly
SquareNode::~SquareNode(){
	delete m_heightMap;


}

void SquareNode::ReGenerate(Vector3<float> globalPosition){

	//Generate on GPU
	m_heightMap->ReGenerate(globalPosition);
	//m_heightMap = new HeightMapGPU(m_ptrRenderingShader,m_ptrGenerationShader, relativePosition, translation, m_geomSize, m_numDivisions, m_textureSize, 1);

}

void SquareNode::GenerateGPU(Vector3<float> relativePosition, Vector3<float> translation, int octaves, float lacunarity, float gain, float offset){

	//Generate on GPU
	m_heightMap = new HeightMapGPU(m_ptrRenderingShader,m_ptrGenerationShader, relativePosition, translation, m_geomSize, m_numDivisions, m_textureSize, 1,
									octaves, lacunarity, gain, offset);


}

void SquareNode::GenerateCPU(Vector3<float> relativePosition, Vector3<float> translation, char* ptrPermArray, int octaves, float lacunarity, float gain, float offset){
	
	//Generate on CPU
	m_heightMap = new HeightMapCPU(m_ptrRenderingShader, relativePosition, translation, m_geomSize, m_numDivisions, ptrPermArray,
									octaves, lacunarity, gain, offset);

}



void SquareNode::Render(double elapsedTime){

	
	m_heightMap->Generate();
	
	m_heightMap->Render(elapsedTime);

	
	
	
	
}

bool SquareNode::IsWithin(Vector3<float> position){
	if(position.GetX()  >= m_globalPosition.GetX() && position.GetX() <= m_globalPosition.GetX() + m_geomSize)
		if(position.GetY()  >= m_globalPosition.GetY() && position.GetY() <= m_globalPosition.GetY() + m_geomSize)
			return true;


	return false;

}

/*
Left
|   Right
|   |
2 4 7 -> TOP
1 c 6
0 3 5 -> BOTTOM
*/
short SquareNode::GetNewStandingNodePosition(Vector3<float> position, short gridSize){
	
	//Right
	if(position.GetX() >= m_globalPosition.GetX() + m_geomSize){
		
		//return m_ptrNeighbours[6]->m_position;
		return m_gridIndex+gridSize;
	}
	
	//Top
	if(position.GetY() >= m_globalPosition.GetY() + m_geomSize){
		
		//return m_ptrNeighbours[4]->m_position;
		return m_gridIndex+1;
	}

	//Bottom
	if(position.GetY() <= m_globalPosition.GetY()){
		
		//return m_ptrNeighbours[3]->m_position;
		return m_gridIndex-1;
	}

	//Left
	if(position.GetX() <= m_globalPosition.GetX()){
		
		//return m_ptrNeighbours[1]->m_position;
		return m_gridIndex-gridSize;
	}

	return NULL;
}