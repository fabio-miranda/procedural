#include "SimpleSquare.h"


SimpleSquare::SimpleSquare(short width, short height) {
	m_width = width;
	m_height = height;


}

SimpleSquare::~SimpleSquare(){

}



void SimpleSquare::Render(){
	
	glBegin( GL_TRIANGLES );

		glTexCoord2d(0,1); glVertex2f(0, 0);
		glTexCoord2d(0,1); glVertex2f( m_width, 0);
		glTexCoord2d(1,1); glVertex2f( m_width,m_height);

		glTexCoord2d(1,1); glVertex2f( m_width,m_height);				
		glTexCoord2d(1,0); glVertex2f(0,m_height);
		glTexCoord2d(0,0); glVertex2f(0,0);
	glEnd();
	
	/*
	glBegin( GL_TRIANGLES );

		glTexCoord2d(0.0,0.0); glVertex3f(-25, -25, 0.0f);
		glTexCoord2d(0.0,1.0); glVertex3f( 25, -25, 0.0f);
		glTexCoord2d(1.0,1.0); glVertex3f( 25,25, 0.0f);

		glTexCoord2d(1.0,1.0); glVertex3f( 25,25, 0.0f);
		glTexCoord2d(1.0,0); glVertex3f( -25,25, 0.0f);
		glTexCoord2d(0.0,0.0); glVertex3f(-25, -25, 0.0f);
	glEnd();
	*/
}