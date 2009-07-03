#include "stdafx.h"
#include "Heightmask.h"
#include "Vector3.h"
#include <IL/il.h>
#include "GL/glfw.h"
using namespace std;


Heightmask::Heightmask(){

}

Heightmask::Heightmask(char* image_adress){


	//ilInit();
	ilEnable(IL_ORIGIN_SET);
	// Generate a new image Id and bind it with the
	// current image.
	ILuint imgId;
	ilGenImages(1,&imgId);
	ilBindImage(imgId);

	if(!ilLoadImage(image_adress))
    {
        glfwTerminate();
		exit(GL_FALSE);
    }

	m_width = ilGetInteger(IL_IMAGE_WIDTH);
	m_height = ilGetInteger(IL_IMAGE_HEIGHT);
	
	m_imageData = new unsigned char[m_width * m_height * 5];
	ilCopyPixels(0, 0, 0, m_width, m_height, 1, IL_RGBA, IL_UNSIGNED_BYTE, m_imageData);
	
	// Finally, delete the DevIL image data.
	ilDeleteImage(imgId);


}

bool Heightmask::GetBoolValue(int x, int y){

	if(x > m_width || y > m_height){
		return false;
	}

	int r = m_imageData[(4*x + (4*y * m_height))];

	if(r > 127)
		return true;
	else
		return false;

}