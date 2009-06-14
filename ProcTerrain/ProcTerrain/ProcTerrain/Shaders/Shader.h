#ifndef Shader_H
#define Shader_H

#include "GL/glew.h"
#include "../Util/textfile.h"


class Shader{
	
	
public:
	Shader();
	Shader(char*, char*);
	~Shader();
	void Enable();
	void Disable();

	GLhandleARB m_shaderProg;



private:
	GLhandleARB m_shaderVert;
	GLhandleARB m_shaderFrag;
	
	

};


#endif