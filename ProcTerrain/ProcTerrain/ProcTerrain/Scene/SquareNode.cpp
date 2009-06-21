#include "SquareNode.h"


SquareNode::SquareNode(GenerationShader* generationShader, RenderingShader* renderingShader, Vector3<float> relativePosition, Vector3<float> translation, float geomSize, int textureSize, short numDivisions){
	

	
	m_ptrTerrainRenderingShader = renderingShader;
	m_relativePosition = relativePosition;
	m_globalPosition = relativePosition;
	m_globalPosition.Add(translation);

	m_geomSize = geomSize;
	m_numDivisions = numDivisions;
	m_numNeighbours = 0;
	m_textureSize = textureSize;
	
	m_gridIndex = -1; //center of the grid (currentNode)

	for(int i=0; i<8; i++){
		m_ptrNeighbours[i] = NULL;
	}
	
	//translation.Add(relativePosition);
	m_heightMap = new HeightMap(generationShader, m_globalPosition, geomSize, textureSize, 1);
	m_face = new VBOSquare(m_relativePosition, m_geomSize, m_numDivisions);


	
	
}

SquareNode::~SquareNode(){
	delete m_heightMap;


}



void SquareNode::Render(double elapsedTime){

	
	m_heightMap->Generate();
	if(m_heightMap->m_time > 1) m_heightMap->m_time -= elapsedTime;
	

	//Call the parent
	//Node::Render();
	//TODO: make sure they render only once
	
	for(int i=0; i<8; i++){
		if(m_ptrNeighbours[i] != NULL)
			m_ptrNeighbours[i]->Render(elapsedTime);
	}
	
	
	
	
	m_ptrTerrainRenderingShader->Enable();

	
	//glActiveTexture(GL_TEXTURE0);
	//glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_heightMap->m_ptrFBO->m_textureId);
	glUniform1f(m_ptrTerrainRenderingShader->m_locTime, m_heightMap->m_time);
	//TODO: do it only once, after generating the heightmap
	//there is no need to do it every frame: http://www.gamedev.net/community/forums/mod/journal/journal.asp?jn=530427&reply_id=3450696
	//glUniform1i(m_ptrTerrainRenderingShader->m_locTexture, 0);
	

	m_face->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
	m_ptrTerrainRenderingShader->Disable();
	
	
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
short SquareNode::GetNewStandingNodePosition(Vector3<float> position){
	
	//Right
	if(position.GetX() >= m_globalPosition.GetX() + m_geomSize){
		
		//return m_ptrNeighbours[6]->m_position;
		return 6;
	}
	
	//Top
	if(position.GetY() >= m_globalPosition.GetY() + m_geomSize){
		
		//return m_ptrNeighbours[4]->m_position;
		return 4;
	}

	//Bottom
	if(position.GetY() <= m_globalPosition.GetY()){
		
		//return m_ptrNeighbours[3]->m_position;
		return 3;
	}

	//Left
	if(position.GetX() <= m_globalPosition.GetX()){
		
		//return m_ptrNeighbours[1]->m_position;
		return 1;
	}

	return NULL;
}


void SquareNode::GenerateFromScratch(SquareNode* oldNode, short index, Vector3<float> relativePosition, Vector3<float> translation, short numDivisions, short numNeighbours){


	SquareNode* aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, relativePosition, translation, m_geomSize, m_textureSize, numDivisions);
	m_ptrNeighbours[index] = aux;
	//translation.Add(position);
	aux->GenerateNeighbours(aux, true, index, relativePosition, translation, numNeighbours);
	

}

void SquareNode::GenerateJustHeightMap(SquareNode* oldNode, short index, Vector3<float> relativePosition, Vector3<float> translation, short numNeighbours){

	

	if(m_ptrNeighbours[index]->m_ptrNeighbours[1] == NULL){
		delete m_ptrNeighbours[index]->m_heightMap;

		relativePosition.Add(translation);
		m_ptrNeighbours[index]->m_heightMap = new HeightMap(m_heightMap->m_ptrTerrainGenerationShader, relativePosition, m_geomSize, m_textureSize, 1);
		
	}
	else{
		oldNode->m_heightMap = m_ptrNeighbours[index]->m_heightMap;
		//m_ptrNeighbours[index]->m_heightMap = oldNode->m_heightMap;
		m_ptrNeighbours[index]->GenerateNeighbours(m_ptrNeighbours[index], false, index, relativePosition, translation, numNeighbours);
	}


}

//Instead of generating new VBOs, we just switch the heightmap from the current ones
void SquareNode::GenerateNeighbours(SquareNode* oldNode, bool generateFromScratch, short gridIndex, Vector3<float> relativePosition, Vector3<float> translation, short numNeighbours){

	m_gridIndex = gridIndex;
	m_numNeighbours = numNeighbours;

	//TODO: Make sure we don't generate nodes already generated. Re-use the already generated
	//TODO: replace the ifs and elses with a pointer to a function
	if(numNeighbours > 0){
		//Generate for the neighbours of the current node
		short numDivisions = (short)ceil(m_numDivisions / (float)conf_lodFactor);
		if(m_gridIndex != -1){
			Vector3<float> position;
			
			switch(m_gridIndex){
				case 0:
					//0
					position = Vector3<float>(relativePosition.GetX() - m_geomSize, relativePosition.GetY() - m_geomSize, 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 0, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 0, position, translation, numNeighbours-1);

					//1
					position = Vector3<float>(relativePosition.GetX() -m_geomSize, relativePosition.GetY() , 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 1, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 1, position, translation, numNeighbours-1);

					//3
					position = Vector3<float>(relativePosition.GetX() , relativePosition.GetY() - m_geomSize, 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 3, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 3, position, translation, numNeighbours-1);

					break;
					
				case 1:
					//1
					position = Vector3<float>(relativePosition.GetX() - m_geomSize, relativePosition.GetY() , 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 1, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 1, position, translation, numNeighbours-1);

					break;
				case 2:
					//2
					position = Vector3<float>(relativePosition.GetX() - m_geomSize, relativePosition.GetY() + m_geomSize, 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 2, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 2, position, translation, numNeighbours-1);

					//1
					position = Vector3<float>(relativePosition.GetX() - m_geomSize, relativePosition.GetY() , 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 1, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 1, position, translation, numNeighbours-1);

					//4
					position = Vector3<float>(relativePosition.GetX() , relativePosition.GetY() + m_geomSize, 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 4, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 4, position, translation, numNeighbours-1);

					break;
				case 3:
					//3
					position = Vector3<float>(relativePosition.GetX() , relativePosition.GetY() - m_geomSize, 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 3, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 3, position, translation, numNeighbours-1);

					break;
				case 4:
					//4
					position = Vector3<float>(relativePosition.GetX() , relativePosition.GetY() + m_geomSize, 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 4, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 4, position, translation, numNeighbours-1);

					break;
				case 5:
					//5
					position = Vector3<float>(relativePosition.GetX() + m_geomSize, relativePosition.GetY() - m_geomSize, 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 5, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 5, position, translation, numNeighbours-1);

					//6
					position = Vector3<float>(relativePosition.GetX() + m_geomSize, relativePosition.GetY() , 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 6, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 6, position, translation, numNeighbours-1);

					//3
					position = Vector3<float>(relativePosition.GetX() , relativePosition.GetY() - m_geomSize, 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 3, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 3, position, translation, numNeighbours-1);

					break;
				case 6:
					//6
					position = Vector3<float>(relativePosition.GetX()  + m_geomSize, relativePosition.GetY() , 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 6, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 6, position, translation, numNeighbours-1);

					break;
				case 7:
					//7
					position = Vector3<float>(relativePosition.GetX() + m_geomSize, relativePosition.GetY() + m_geomSize, 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 7, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 7, position, translation, numNeighbours-1);

					//6
					position = Vector3<float>(relativePosition.GetX() + m_geomSize, relativePosition.GetY() , 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 6, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 6, position, translation, numNeighbours-1);

					//4
					position = Vector3<float>(relativePosition.GetX(),relativePosition.GetY() + m_geomSize, 0);
					if(generateFromScratch) GenerateFromScratch(oldNode, 4, position, translation, numDivisions, numNeighbours-1);
					else GenerateJustHeightMap(oldNode, 4, position, translation, numNeighbours-1);

					break;
				default:
					break;
			}
			
		}
		//Generate for the current node
		else{
			SquareNode* aux;
			int cont = 0;

			for(float i=relativePosition.GetX() - m_geomSize; i<=relativePosition.GetX() + m_geomSize; i+=m_geomSize){
				for(float j=relativePosition.GetY() - m_geomSize; j<=relativePosition.GetY() + m_geomSize; j+=m_geomSize){
					
					if(i != relativePosition.GetX() || j != relativePosition.GetY()){
						if(generateFromScratch) GenerateFromScratch(this, cont, Vector3<float>(i,j,0), translation, numDivisions, numNeighbours-1);
						else GenerateJustHeightMap(this, cont, Vector3<float>(i,j,0), translation, numNeighbours-1);

						cont++;
					}
				}
			}

		}

	}
	else{
		

	}
}
