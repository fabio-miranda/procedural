#include "SquareNode.h"


SquareNode::SquareNode(GenerationShader* generationShader, RenderingShader* renderingShader, FBO* fbo, Vector3<float> position, float size, int textureSize, short numDivisions){
	

	m_heightMap = new HeightMap(generationShader, fbo, position, textureSize, 1);
	m_ptrTerrainRenderingShader = renderingShader;

	m_position = position;
	m_size = size;
	m_numDivisions = numDivisions;
	m_numNeighbours = 0;
	m_textureSize = textureSize;
	m_face = new VBOSquare(m_position, m_size, m_numDivisions);
	m_gridIndex = -1; //center of the grid (currentNode)

	for(int i=0; i<8; i++){
		m_ptrNeighbours[i] = NULL;
	}

	
	
}

SquareNode::~SquareNode(){
	delete m_heightMap;


}



void SquareNode::Render(){

	
	m_heightMap->Generate();
	

	//Call the parent
	//Node::Render();
	//TODO: make sure they render only once
	
	for(int i=0; i<8; i++){
		if(m_ptrNeighbours[i] != NULL)
			m_ptrNeighbours[i]->Render();
	}
	
	
	
	
	m_ptrTerrainRenderingShader->Enable();

	
	//glActiveTexture(GL_TEXTURE0);
	//glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_heightMap->m_ptrFBO->m_textureId);
	//TODO: do it only once, after generating the heightmap
	//there is no need to do it every frame: http://www.gamedev.net/community/forums/mod/journal/journal.asp?jn=530427&reply_id=3450696
	//glUniform1i(m_ptrTerrainRenderingShader->m_locTexture, 0);
	

	m_face->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
	m_ptrTerrainRenderingShader->Disable();
	
	
}

bool SquareNode::IsWithin(Vector3<float> position){
	if(position.GetX()  >= m_position.GetX() && position.GetX() <= m_position.GetX() + m_size)
		if(position.GetY()  >= m_position.GetY() && position.GetY() <= m_position.GetY() + m_size)
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
SquareNode* SquareNode::GetNewStandingNode(Vector3<float> position){
	
	//Right
	if(position.GetX() >= m_position.GetX() + m_size){
		
		return m_ptrNeighbours[6];
	}
	
	//Top
	if(position.GetY() >= m_position.GetY() + m_size){
		
		return m_ptrNeighbours[4];
	}

	//Bottom
	if(position.GetY() <= m_position.GetY()){
		
		return m_ptrNeighbours[3];
	}

	//Left
	if(position.GetX() <= m_position.GetX()){
		
		return m_ptrNeighbours[1];
	}
}

//TODO: Instead of generating new VBOs, we just switch the FBOs from the current ones
void SquareNode::SwitchFBOs(){



}

void SquareNode::GenerateNeighbours(SquareNode* m_oldNode, short numNeighbours, short gridIndex){

	m_gridIndex = gridIndex;
	m_numNeighbours = numNeighbours;

	//TODO: Make sure we don't generate nodes already generated. Re-use the already generated
	if(numNeighbours > 0){
		//Generate for the neighbours of the current node
		short numDivisions = ceil(m_numDivisions / (float)conf_lodFactor);
		if(m_gridIndex != -1){
			SquareNode* aux;
			Vector3<float> position;

			switch(m_gridIndex){
				case 0:
					//0
					position = Vector3<float>(m_position.GetX() - m_size, m_position.GetY() - m_size, 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[0] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 0);

					//1
					position = Vector3<float>(m_position.GetX() - m_size, m_position.GetY(), 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[1] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 1);

					//3
					position = Vector3<float>(m_position.GetX(), m_position.GetY() - m_size, 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[3] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 3);
					break;
					
				case 1:
					//1
					position = Vector3<float>(m_position.GetX() - m_size, m_position.GetY(), 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[1] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 1);
					break;
				case 2:
					//2
					position = Vector3<float>(m_position.GetX() - m_size, m_position.GetY() + m_size, 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[2] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 2);

					//1
					position = Vector3<float>(m_position.GetX() - m_size, m_position.GetY(), 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[1] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 1);

					//4
					position = Vector3<float>(m_position.GetX(), m_position.GetY() + m_size, 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[4] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 4);
					break;
				case 3:
					//3
					position = Vector3<float>(m_position.GetX(), m_position.GetY() - m_size, 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[3] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 3);
					break;
				case 4:
					//4
					position = Vector3<float>(m_position.GetX(), m_position.GetY() + m_size, 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[4] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 4);
					break;
				case 5:
					//5
					position = Vector3<float>(m_position.GetX() + m_size, m_position.GetY() - m_size, 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[5] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 5);

					//6
					position = Vector3<float>(m_position.GetX() + m_size, m_position.GetY(), 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[6] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 6);

					//3
					position = Vector3<float>(m_position.GetX(), m_position.GetY() - m_size, 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[3] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 3);
					break;
				case 6:
					//6
					position = Vector3<float>(m_position.GetX() + m_size, m_position.GetY(), 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[6] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 6);
					break;
				case 7:
					//7
					position = Vector3<float>(m_position.GetX() + m_size, m_position.GetY() + m_size, 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[7] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 7);

					//6
					position = Vector3<float>(m_position.GetX() + m_size, m_position.GetY(), 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[6] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 6);

					//4
					position = Vector3<float>(m_position.GetX(), m_position.GetY() + m_size, 0);
					aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, position,m_size, m_textureSize, numDivisions);
					m_ptrNeighbours[4] = aux;
					aux->GenerateNeighbours(this, numNeighbours-1, 4);
					break;
				default:
					break;
			}
		}
		//Generate for the current node
		else{
			SquareNode* aux;
			int cont = 0;

			for(float i=m_position.GetX() - m_size; i<=m_position.GetX() + m_size; i+=m_size){
				for(float j=m_position.GetY() - m_size; j<=m_position.GetY() + m_size; j+=m_size){
					
					if(i != m_position.GetX() || j != m_position.GetY()){
						aux = new SquareNode(m_heightMap->m_ptrTerrainGenerationShader, m_ptrTerrainRenderingShader, m_heightMap->m_ptrFBO, Vector3<float>(i,j,0),m_size, m_textureSize, numDivisions);
						m_ptrNeighbours[cont] = aux;
						aux->GenerateNeighbours(this, numNeighbours-1, cont);

						cont++;
					}
				}
			}

		}

	}


	
	


}
