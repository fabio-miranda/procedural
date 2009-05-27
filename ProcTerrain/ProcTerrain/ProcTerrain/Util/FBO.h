#ifndef FBO_H
#define FBO_H


#include "GL/glew.h"
//#include "GL/glfw.h"
#include "Vertex.h"
#include "../Config.h"


typedef struct{
	bool beingUsed;
	GLenum attachment;
} FBOAttachment;


class FBO{

private:
	GLuint m_fbo;
	FBOAttachment m_usedAttachments[16];


public:

	FBO();
	~FBO();
	void DeleteBuffer();
	void BindTexture(GLuint);
	void Enable();
	void Disable();
	
	

};

#endif