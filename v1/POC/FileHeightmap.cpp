#include "stdafx.h"
#include "FileHeightmap.h"
#include "Heightmask.h"
#include "Vector3.h"
#include <IL/il.h>
#include <string>
#include <iostream>
#include "GL/glfw.h"
using namespace std;



FileHeightmap::FileHeightmap(int renderStepSize, Vector3<float> color, Vector3<float> position, int width, int height, char* image_adress) : StaticTerrain(renderStepSize, color, position, width, height){

	m_imageAdress = image_adress;
	


}

void FileHeightmap::FillHeightMap(){
	//ilInit();
	ilEnable(IL_ORIGIN_SET);
	// Generate a new image Id and bind it with the
	// current image.
	ILuint imgId;
	ilGenImages(1,&imgId);
	ilBindImage(imgId);

	if(!ilLoadImage(m_imageAdress))
    {
        glfwTerminate();
		exit(GL_FALSE);
    }

	m_width = ilGetInteger(IL_IMAGE_WIDTH);
	m_height = ilGetInteger(IL_IMAGE_HEIGHT);
	
	//m_heightMap = new unsigned char[m_width * m_height * 4];
	

	ilCopyPixels(0, 0, 0, m_width, m_height, 1, IL_RGBA, IL_UNSIGNED_BYTE, m_mesh->m_heightMap);
	
	// Finally, delete the DevIL image data.
	ilDeleteImage(imgId);

	//m_mesh->BuildVBOs();

	

}