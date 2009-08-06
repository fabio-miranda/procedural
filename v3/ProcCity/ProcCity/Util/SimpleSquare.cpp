#include "SimpleSquare.h"


SimpleSquare::SimpleSquare(Vector3<float> position, float geomSize, float textureSize) {
	m_position = position;
	m_textureSize = textureSize;
	m_geomSize = geomSize;


}

SimpleSquare::~SimpleSquare(){

}



void SimpleSquare::Render(){
	//m_position = Vector3<float>(0,0,0);
	float offset = -5.0;
	glBegin( GL_TRIANGLES );
		glTexCoord2d(m_position.GetX() - offset,		m_position.GetY());						glVertex2f( m_position.GetX() + 0,		m_position.GetY() + 0);
		glTexCoord2d(m_position.GetX() - offset,		m_position.GetY() + m_textureSize);		glVertex2f( m_position.GetX() + m_geomSize, m_position.GetY() + 0);
		glTexCoord2d(m_position.GetX() + m_textureSize + offset,	m_position.GetY() + m_textureSize);		glVertex2f( m_position.GetX() + m_geomSize, m_position.GetY() + m_geomSize);

		glTexCoord2d(m_position.GetX() + m_textureSize + offset,	m_position.GetY() + m_textureSize);		glVertex2f( m_position.GetX() + m_geomSize, m_position.GetY() + m_geomSize);				
		glTexCoord2d(m_position.GetX() + m_textureSize + offset,	m_position.GetY());						glVertex2f( m_position.GetX() + 0,		m_position.GetY() + m_geomSize);
		glTexCoord2d(m_position.GetX() - offset,					m_position.GetY());						glVertex2f( m_position.GetX() + 0,		m_position.GetY() + 0);
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