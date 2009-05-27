#include "FBO.h"


FBO::FBO(){

	GLint maxbuffers;
	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxbuffers);
	

	/*
	glGenFramebuffersEXT(1, &m_fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);

	int width = 512;
	int height = 512;

	


	//Init the array to see if a current attachment is being used or not, because OpenGL can only render to 16 textures using the same FBO
	m_usedAttachments[0].beingUsed = false; m_usedAttachments[0].attachment = GL_COLOR_ATTACHMENT0_EXT;
	m_usedAttachments[1].beingUsed = false; m_usedAttachments[1].attachment = GL_COLOR_ATTACHMENT1_EXT;
	m_usedAttachments[2].beingUsed = false; m_usedAttachments[2].attachment = GL_COLOR_ATTACHMENT2_EXT;
	m_usedAttachments[3].beingUsed = false; m_usedAttachments[3].attachment = GL_COLOR_ATTACHMENT3_EXT;
	m_usedAttachments[4].beingUsed = false; m_usedAttachments[4].attachment = GL_COLOR_ATTACHMENT4_EXT;
	m_usedAttachments[5].beingUsed = false; m_usedAttachments[5].attachment = GL_COLOR_ATTACHMENT5_EXT;
	m_usedAttachments[6].beingUsed = false; m_usedAttachments[6].attachment = GL_COLOR_ATTACHMENT6_EXT;
	m_usedAttachments[7].beingUsed = false; m_usedAttachments[7].attachment = GL_COLOR_ATTACHMENT7_EXT;
	m_usedAttachments[8].beingUsed = false; m_usedAttachments[8].attachment = GL_COLOR_ATTACHMENT8_EXT;
	m_usedAttachments[9].beingUsed = false; m_usedAttachments[9].attachment = GL_COLOR_ATTACHMENT9_EXT;
	m_usedAttachments[10].beingUsed = false; m_usedAttachments[10].attachment = GL_COLOR_ATTACHMENT10_EXT;
	m_usedAttachments[11].beingUsed = false; m_usedAttachments[11].attachment = GL_COLOR_ATTACHMENT11_EXT;
	m_usedAttachments[12].beingUsed = false; m_usedAttachments[12].attachment = GL_COLOR_ATTACHMENT12_EXT;
	m_usedAttachments[13].beingUsed = false; m_usedAttachments[13].attachment = GL_COLOR_ATTACHMENT13_EXT;
	m_usedAttachments[14].beingUsed = false; m_usedAttachments[14].attachment = GL_COLOR_ATTACHMENT14_EXT;
	m_usedAttachments[15].beingUsed = false; m_usedAttachments[15].attachment = GL_COLOR_ATTACHMENT15_EXT;
	*/

}

FBO::~FBO(){
	DeleteBuffer();

}

void FBO::BindTexture(GLuint m_textureId){
	
	for(int i=0; i<16; i++){
		if(m_usedAttachments[i].beingUsed == false){
			m_usedAttachments[i].beingUsed = true;
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, m_usedAttachments[i].attachment, GL_TEXTURE_2D, m_textureId, 0);

			return;
		}
	}


}

void FBO::Enable(){
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
}

void FBO::Disable(){
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

}



void FBO::DeleteBuffer(){

}
