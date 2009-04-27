#include "stdafx.h"
#include "StaticTerrain.h"
#include "Heightmask.h"
#include "Vector3.h"
#include "Mesh.h"
#include <IL/il.h>
#include <string>
#include <iostream>
#include "GL/glfw.h"
#include "Constants.h"
using namespace std;



Terrain::Terrain(int renderStepSize, Vector3<float> color, Vector3<float> position, int width, int height){


	m_color = color;
	m_hasHeightmask = false;
	m_position = position;
	//m_heightmask = null;
	m_width = width;
	m_height = height;
	//m_heightMap = new unsigned char[m_width * m_height * 4];]

	m_mesh = new Mesh(color, position, width, height);

	m_renderStepSize = renderStepSize;


}

Terrain :: ~Terrain()
{
	if(m_mesh)
		delete m_mesh;
	m_mesh = NULL;
}

void Terrain::InsertNode(Node* node){

	this->m_children.insert(m_children.end(), node);

	//cout << " Memoria: ";
	//cout << &(*m_children[0]);


	//cout << "\n";



}

Node* Terrain::FindCurrentStandingNode(Vector3<float> cam_position){
	
	for (m_iterator = m_children.begin(); m_iterator != m_children.end(); m_iterator++ )
	{

		Node& node = **m_iterator;
		
		if(node.IsWithin(cam_position)){
			//cout << "caiu!!";

			node.GenerateNeighbours(this);

			return &node;


		}	
	}

	return NULL;


}

void Terrain::Render(bool wireFrame, int colorToRender){

	Node::Render(wireFrame, colorToRender);
	
	
	
	//glBegin( GL_QUADS );
	
	//int x_pixel, y_pixel;
	
	
	/*
	for(int x_pixel = 0; x_pixel < m_width - m_stepSize; x_pixel+= m_stepSize){
		for(int y_pixel = 0; y_pixel < m_height - m_stepSize; y_pixel+= m_stepSize){
			
			if(m_hasHeightmask){
				if(m_heightmask.GetBoolValue(x_pixel, y_pixel))
					RenderQuad(x_pixel, y_pixel);
			}
			else{
				RenderQuad(x_pixel, y_pixel);
			}
				
		}

	}
	*/
	
	

	

	
	
	//Shaders
	/*
	if(m_shader){
		m_shader->begin();

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,m_texture0);
		

		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,m_texture1);
		
		glActiveTextureARB(GL_TEXTURE2_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,m_texture2);
		
		
		m_shader->setUniform1ui("tex0", m_texture0);
		m_shader->setUniform1ui("tex1", m_texture1);
		m_shader->setUniform1ui("tex2", m_texture2);
		
		
	}	
	*/
	
	//Light
	/*
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE ) ;
	glColor3f(.55,.55,.55);
	*/

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState( GL_TEXTURE_COORD_ARRAY );


	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_mesh->m_vboVertices); //vertices
	glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL);

	if(colorToRender == COLOR_GRAYSCALE)
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_mesh->m_vboColorGrayScale); //colors
	else if(colorToRender == COLOR_GREEN)
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_mesh->m_vboColorGreen); //colors
	else if(colorToRender == COLOR_MIX)
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_mesh->m_vboColorMix); //colors

	glColorPointer(3, GL_FLOAT, 0, (char *) NULL);

	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_mesh->m_vboTexCoord); //texCoords
	//glTexCoordPointer(3, GL_FLOAT, 0, (char *) NULL);
	
	

	//temp:
	//glVertexPointer( 3, GL_FLOAT, 0, m_mesh->m_vertices );

	if(wireFrame)
		glDrawArrays( GL_LINES, 0, m_mesh->m_vertexCount);
	else
		glDrawArrays( GL_QUADS, 0, m_mesh->m_vertexCount);


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState( GL_TEXTURE_COORD_ARRAY );


	//if (m_shader) m_shader->end();


	
	//glEnd();
	
	


}
/*
int Terrain::GetHeight(int x, int y){

	int r = m_heightMap[(4*x + (4*y * m_height))];

	return r;

}

Vector3<float> Terrain::GetColor(int x, int y){

	float height = (GetHeight(x,y))/255.0f;

	return Vector3<float>(height, height, height);

}
*/
/*
int Terrain::GetArrayPosition(int x, int y){

	return 4 * x + 4 * y * m_width;

}
*/

void Terrain::SetHeightMask(Heightmask heightmask){
	m_hasHeightmask = true;

	m_heightmask = heightmask;

}





bool Terrain::IsWithin(Vector3<float> position){
	
	if(position.GetX() > this->m_position.GetX() && position.GetX() < this->m_position.GetX() + this->m_width)
		if(position.GetZ() > this->m_position.GetZ() && position.GetZ() < this->m_position.GetZ() + this->m_height)
			return true;


	return false;


}


void Terrain::Normalize(float maxHeight, float minHeight){

	//Get the lowest and highest values
	float highest = maxHeight;
	float lowest = minHeight;
	float aux = 0;

	for(int x = 0; x<m_width; x++){
		for(int y=0; y<m_height; y++){
			aux = m_mesh->GetHeight(x, y);
			
			if(m_mesh->GetHeight(x, y) > maxHeight){
				highest = m_mesh->GetHeight(x, y);
			}

			if(m_mesh->GetHeight(x, y) < minHeight){
				lowest = m_mesh->GetHeight(x, y);
			}
		}
	}


	//Normalize
	float diff = highest - lowest;
	float scale = maxHeight - minHeight;
	
	for(int x = 0; x<m_width; x++){
		for(int y=0; y<m_height; y++){
			aux = m_mesh->GetHeight(x, y);

			//m_mesh->SetHeight(x, y, (aux - lowest) / (diff * scale) + minHeight);


		}
	}


}
/*
void Terrain::SetShader(){
	
	cwc::glShaderManager SM;


	m_shader = SM.loadfromFile("multiTexture.vert","multiTexture.frag"); // load (and compile, link) from file

	

	if (m_shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";

	m_programObj = m_shader->GetProgramObject();

	LoadTexture("../POC/Content/Textures/dirt.png", m_texture0, GL_TEXTURE0_ARB);
	LoadTexture("../POC/Content/Textures/grass.png", m_texture1, GL_TEXTURE1_ARB);
	LoadTexture("../POC/Content/Textures/snow.png", m_texture2, GL_TEXTURE2_ARB);

	
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_texture0);
	m_shader->setUniform1ui("tex0", m_texture0, 0);
	//glDisable(GL_TEXTURE_2D);
	
	
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, m_texture1);
	m_shader->setUniform1ui("tex1", m_texture1, 1);
	//glDisable(GL_TEXTURE_2D);
	
	
	//glActiveTexture(GL_TEXTURE2);
	//glBindTexture(GL_TEXTURE_2D, m_texture2);
	m_shader->setUniform1ui("tex2", m_texture2, 2);
	//glDisable(GL_TEXTURE_2D);
	

}
*/


void Terrain::LoadTexture(char* end, GLuint& texture, GLuint textureIndex){
	//Load textures
	ILuint image_name;

	//ilInit(); /* Initialization of DevIL */
	ilGenImages(1, &image_name); /* Generation of one image name */
	ilBindImage(image_name); /* Binding of image name */
	if(!ilLoadImage(end)){ /* Loading of image "image.jpg" */
		glfwTerminate();

	}

	//glActiveTextureARB(textureIndex);
	glGenTextures(1, &texture); /* Texture name generation */
    //glBindTexture(GL_TEXTURE_2D, texture); /* Binding of texture name */
	
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), 
					ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());



	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	
	ilDeleteImages(1, &image_name); /* Because we have already copied image data into texture data
    we can release memory used by image. */
	
}

