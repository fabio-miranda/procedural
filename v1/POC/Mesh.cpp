#include "stdafx.h"
#include "Mesh.h"
#include "Vector3.h"
#include "GL/glfw.h"
#include "Random.h"
#include <iostream>
using namespace std;



Mesh :: ~Mesh()
{

	unsigned int nBuffers[1] = { m_vboVertices};
	glDeleteBuffersARB( 1, nBuffers );						// Free The Memory

	// Delete Data
	if( m_vertices )											// Deallocate Vertex Data
		delete [] m_vertices;
	m_vertices = NULL;
	
	if( m_colorGrayScale)
		delete [] m_colorGrayScale;
	m_colorGrayScale = NULL;

	if( m_colorMix)
		delete [] m_colorMix;
	m_colorMix = NULL;

	if( m_colorGreen)
		delete [] m_colorGreen;
	m_colorGreen = NULL;

	if(m_texCoord)
		delete [] m_texCoord;
	m_texCoord = NULL;
	
	if( m_heightMap )
		delete [] m_heightMap;
	m_heightMap = NULL;
	
}

Mesh::Mesh(Vector3<float> color, Vector3<float> position, int width, int height){

	m_width = width;
	m_height = height;

	m_position = position;
	m_color = color;

	m_vertexCount = (int)(m_width * m_height * 4); //The vertices aren't shared
	m_vertices = new float[m_vertexCount * 3]; 
	
	
	m_colorGrayScale = new float[m_vertexCount * 3]; 
	m_colorMix = new float[m_vertexCount * 3]; 
	m_colorGreen = new float[m_vertexCount * 3];



	m_texCoord = new float[m_vertexCount * 3]; 
	//m_heightMap = new unsigned char[m_width * m_height * 4];
	m_heightMap = new unsigned char[m_width * m_height * 4];

	m_vboVertices = 0;

}

void Mesh::AddHeight(int x, int y, float height){
	

	m_heightMap[4*x + (4*y * m_width)] += height;

	
}

float Mesh::GetHeight(int x, int y){

	//float r = m_heightMap[(4*x + (4*y * m_height))];
	float r = m_heightMap[(4*x + (4*y * m_width))];

	return r;

}

Vector3<float> Mesh::GetColorGrayScale(int x, int y){

	float height = (GetHeight(x,y))/255.0f;

	return Vector3<float>(height * m_color.GetX(), height * m_color.GetY(), height * m_color.GetZ());
	/*
	float white = height;
	float green = 1.0 - height;
	float blue = 1.0 - green;
	green *= 1.3;

	
	
	return Vector3<float>(height * white * 0.0 + height * green * 0.0 + height * blue * 0.5,
						  height * white * 0.0 + height * green * 1.0 + height * blue * 0.2,
						  height * white * 0.0 + height * green * 0.0 + height * blue * 0.0);
	*/
	/*
	if(height <= 0.7f)
		return Vector3<float>(height * 0.2f, height * 0.2f, height);
	else if(height <= 0.95f)
		return Vector3<float>(height * 0.2f, height, height * 0.2f);
	else
		return Vector3<float>(height, height, height);
	*/

	
}

Vector3<float> Mesh::GetColorGreen(int x, int y){

	float height = (GetHeight(x,y))/255.0f;

	return Vector3<float>(0, height * m_color.GetY(), 0);

	
}

Vector3<float> Mesh::GetColorMix(int x, int y){

	float height = (GetHeight(x,y))/255.0f;

	float white = height;
	float green = 1.0 - height;
	float blue = 1.0 - green;
	green *= 1.2;

	
	
	return Vector3<float>(height * white * 0.0 + height * green * 0.0 + height * blue * 0.5 + Random::Next(0,16)/255.0f,
						  height * white * 0.0 + height * green * 1.0 + height * blue * 0.2 + Random::Next(0,16)/255.0f,
						  height * white * 0.0 + height * green * 0.0 + height * blue * 0.2 + Random::Next(0,16)/255.0f);
	
	/*
	if(height <= 0.7f)
		return Vector3<float>(height * 0.2f, height * 0.2f, height);
	else if(height <= 0.95f)
		return Vector3<float>(height * 0.2f, height, height * 0.2f);
	else
		return Vector3<float>(height, height, height);
	*/
	
}



void Mesh::SetVertexAndColor(int vertexIndex, Vector3<float> vertex){
	//int vertexBase = (3*x + 3*y*m_width);

	m_vertices[vertexIndex] = vertex.GetX() + m_position.GetX();
	m_vertices[vertexIndex+1] = vertex.GetY() + m_position.GetY();
	m_vertices[vertexIndex+2] = vertex.GetZ() + m_position.GetZ();

	m_texCoord[vertexIndex] = vertex.GetX();
	m_texCoord[vertexIndex+1] = vertex.GetZ();

	//Color
	Vector3<float> color;

	color = Mesh::GetColorGrayScale(vertex.GetX(), vertex.GetZ());
	m_colorGrayScale[vertexIndex] = color.GetX();
	m_colorGrayScale[vertexIndex+1] = color.GetY();
	m_colorGrayScale[vertexIndex+2] = color.GetZ();

	color = Mesh::GetColorGreen(vertex.GetX(), vertex.GetZ());
	m_colorGreen[vertexIndex] = color.GetX();
	m_colorGreen[vertexIndex+1] = color.GetY();
	m_colorGreen[vertexIndex+2] = color.GetZ();

	color = Mesh::GetColorMix(vertex.GetX(), vertex.GetZ());
	m_colorMix[vertexIndex] = color.GetX();
	m_colorMix[vertexIndex+1] = color.GetY();
	m_colorMix[vertexIndex+2] = color.GetZ();

}


void Mesh::BuildVBOs(){
	
	// Generate And Bind The Vertex Buffer
	glGenBuffersARB( 1, &m_vboVertices );					// Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_vboVertices );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, m_vertexCount*3*sizeof(float), m_vertices, GL_STATIC_DRAW_ARB );

	//Color buffer
	glGenBuffersARB( 1, &m_vboColorGrayScale );					// Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_vboColorGrayScale );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, m_vertexCount*3*sizeof(float), m_colorGrayScale, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &m_vboColorGreen );					// Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_vboColorGreen );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, m_vertexCount*3*sizeof(float), m_colorGreen, GL_STATIC_DRAW_ARB );

	glGenBuffersARB( 1, &m_vboColorMix );					// Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_vboColorMix );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, m_vertexCount*3*sizeof(float), m_colorMix, GL_STATIC_DRAW_ARB );

	//Texture Coordinates buffer
	glGenBuffersARB( 1, &m_vboTexCoord );					// Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_vboTexCoord );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, m_vertexCount*3*sizeof(float), m_texCoord, GL_STATIC_DRAW_ARB );

	

	// Our Copy Of The Data Is No Longer Necessary, It Is Safe In The Graphics Card
	delete [] m_vertices;
	m_vertices = NULL;

	delete [] m_colorGrayScale;
	m_colorGrayScale = NULL;

	delete [] m_colorMix;
	m_colorMix = NULL;

	delete [] m_colorGreen;
	m_colorGreen = NULL;

	delete [] m_texCoord;
	m_texCoord = NULL;
	

}

void Mesh::CopyVertexFromHeightMap(){

	float x, y, z;
	int vertexIndex = 0;
	
	for(int x_pixel=0; x_pixel<m_width -1; x_pixel++){
		for(int y_pixel=0; y_pixel<m_height -1; y_pixel++){
			//Bottom left vertex
			x = x_pixel;
			y = GetHeight(x_pixel, y_pixel);
			z = y_pixel;
			
			//color = GetColor(x, z);
			//glColor4f(color.GetX(), color.GetY(), color.GetZ(), 1.0f );
			//glVertex3i(m_position.GetX() + x,m_position.GetY() +  y,m_position.GetZ() +  z);
			SetVertexAndColor(vertexIndex, Vector3<float>(x, y, z));
			vertexIndex+=3;
			

			//Top left vertex
			x = x_pixel;
			y = GetHeight(x_pixel, y_pixel + 1);
			z = y_pixel + 1;

			//color = GetColor(x, z);
			//glColor4f(color.GetX(), color.GetY(), color.GetZ(), 1.0f );
			//glVertex3i(m_position.GetX() + x,m_position.GetY() +  y,m_position.GetZ() +  z);
			SetVertexAndColor(vertexIndex, Vector3<float>(x, y, z));
			vertexIndex+=3;

			//Top right vertex
			x = x_pixel + 1;
			y = GetHeight(x_pixel + 1, y_pixel + 1);
			z = y_pixel + 1;

			//color = GetColor(x, z);
			//glColor4f(color.GetX(), color.GetY(), color.GetZ(), 1.0f );
			//glVertex3i(m_position.GetX() + x,m_position.GetY() +  y,m_position.GetZ() +  z);
			SetVertexAndColor(vertexIndex, Vector3<float>(x, y, z));
			vertexIndex+=3;

			//Bottom right
			x = x_pixel + 1; 
			y = GetHeight(x_pixel + 1, y_pixel ); 
			z = y_pixel;

			//color = GetColor(x, z);
			//glColor4f(color.GetX(), color.GetY(), color.GetZ(), 1.0f );
			//glVertex3i(m_position.GetX() + x,m_position.GetY() +  y,m_position.GetZ() +  z);
			SetVertexAndColor(vertexIndex, Vector3<float>(x, y, z));
			vertexIndex+=3;

		}
	}


}

