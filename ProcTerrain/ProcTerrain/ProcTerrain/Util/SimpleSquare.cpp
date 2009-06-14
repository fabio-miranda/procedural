#include "SimpleSquare.h"


SimpleSquare::SimpleSquare(Vector3<float> position, short width, short height) {
	m_position = position;
	m_width = width;
	m_height = height;


}

SimpleSquare::~SimpleSquare(){

}



void SimpleSquare::Render(){
	//m_position = Vector3<float>(0,0,0);
	glBegin( GL_TRIANGLES );
		glTexCoord2d(0,0); glVertex2f( m_position.GetX() + 0,		m_position.GetY() + 0);
		glTexCoord2d(0,1); glVertex2f( m_position.GetX() + m_width, m_position.GetY() + 0);
		glTexCoord2d(1,1); glVertex2f( m_position.GetX() + m_width, m_position.GetY() + m_height);

		glTexCoord2d(1,1); glVertex2f( m_position.GetX() + m_width, m_position.GetY() + m_height);				
		glTexCoord2d(1,0); glVertex2f( m_position.GetX() + 0,		m_position.GetY() + m_height);
		glTexCoord2d(0,0); glVertex2f( m_position.GetX() + 0,		m_position.GetY() + 0);
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