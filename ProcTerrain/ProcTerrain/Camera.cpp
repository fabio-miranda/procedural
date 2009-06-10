#include "Camera.h"
#include <iostream>
using namespace std;

Camera::Camera(Vector3<float> position, Vector3<float> up){
	m_pos = position;
	m_up = up;
	m_rotation = Vector3<float>(0,0);
	m_speed = 0.1f;

}


void Camera::UpdateKeyboard(){
	

	if(glfwGetKey( 'W' )){
		/*
		float x_rotation, y_rotation;
		y_rotation = (m_rotation.GetY() / 180 * 3.141592654f);
		x_rotation = (m_rotation.GetX() / 180 * 3.141592654f);
		m_pos.AddX(float(sin(y_rotation)) * m_speed) ;
		m_pos.AddZ(-float(cos(y_rotation)) * m_speed) ;
		m_pos.AddY(-float(sin(x_rotation)) * m_speed) ;
		*/
		
		float x_rotation;
		x_rotation = (m_rotation.GetX() / 180 * 3.141592654f);
		m_pos.AddY(float(cos(x_rotation)) * m_speed);
		m_pos.AddZ(float(sin(x_rotation)) * m_speed);
	}
	if(glfwGetKey( 'S' )){
		/*
		float x_rotation, y_rotation;
		y_rotation = (m_rotation.GetY() / 180 * 3.141592654f);
		x_rotation = (m_rotation.GetX() / 180 * 3.141592654f);
		m_pos.AddX(-float(sin(y_rotation)) * m_speed) ;
		m_pos.AddZ(float(cos(y_rotation)) * m_speed) ;
		m_pos.AddY(float(sin(x_rotation)) * m_speed) ;
		*/
		
		float x_rotation;
		x_rotation = (m_rotation.GetX() / 180 * 3.141592654f);
		m_pos.AddY(-float(cos(x_rotation)) * m_speed);
		m_pos.AddZ(-float(sin(x_rotation)) * m_speed);

	}
	if(glfwGetKey( 'A' )){
		float y_rotation;
		y_rotation = (m_rotation.GetY() / 180 * 3.141592654f);
		m_pos.AddX(-float(cos(y_rotation)) * m_speed);
		m_pos.AddZ(-float(sin(y_rotation)) * m_speed);


	}
	if(glfwGetKey( 'D' )){
		float y_rotation;
		y_rotation = (m_rotation.GetY() / 180 * 3.141592654f);
		m_pos.AddX(float(cos(y_rotation)) * m_speed);
		m_pos.AddZ(float(sin(y_rotation)) * m_speed);

	}
}

void Camera::UpdateMouse(){
	int x, y;
	
	glfwGetMousePos(&x,&y);
	
	if(glfwGetKey(GLFW_KEY_LSHIFT)){
		int diffx=x-m_lastMousePos.GetX();
		int diffy=y-m_lastMousePos.GetY();
		
		m_rotation.AddX((float)diffy);
		m_rotation.AddZ((float)diffx);
	}

	if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)){
		float x_rotation, y_rotation;
		y_rotation = (m_rotation.GetY() / 180 * 3.141592654f);
		x_rotation = (m_rotation.GetX() / 180 * 3.141592654f);
		m_pos.AddX(float(sin(y_rotation)) * m_speed) ;
		m_pos.AddZ(-float(cos(y_rotation)) * m_speed) ;
		m_pos.AddY(-float(sin(x_rotation)) * m_speed) ;
	}
	else if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)){
		float x_rotation, y_rotation;
		y_rotation = (m_rotation.GetY() / 180 * 3.141592654f);
		x_rotation = (m_rotation.GetX() / 180 * 3.141592654f);
		m_pos.AddX(-float(sin(y_rotation)) * m_speed) ;
		m_pos.AddZ(float(cos(y_rotation)) * m_speed) ;
		m_pos.AddY(float(sin(x_rotation)) * m_speed) ;
	}
	

	m_lastMousePos.SetX(x);
	m_lastMousePos.SetY(y);
	
	
}

Vector3<float> Camera::GetPosition(){
	return m_pos;

}