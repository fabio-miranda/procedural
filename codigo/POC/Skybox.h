#ifndef SKYBOX_H
#define SKYBOX_H

#include "Vector3.h"


class Skybox{


private:
	//Textures
	GLuint m_texture0;
	GLuint m_texture1;
	GLuint m_texture2;
	GLuint m_texture3;
	GLuint m_texture4;
	GLuint m_texture5;
	
	


public:
	Skybox();
	void LoadTexture(char*, GLuint&, GLuint);
	void RenderSkybox(Vector3<float>);

	
};

#endif
