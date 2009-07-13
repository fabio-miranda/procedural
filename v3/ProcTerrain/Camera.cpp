#include "Camera.h"
#include <iostream>
using namespace std;

Camera::Camera(Vector3<float> position, Vector3<float> up){
	m_pos = position;
	m_up = up;
	m_rotation = Vector3<float>(0,0,1);
	m_speed = 0.01f;
	m_benchmark = false;

}


void Camera::UpdateKeyboard(){
	
	if(m_benchmark){
		float z_rotation;
		z_rotation = (m_rotation.GetZ() / 180 * 3.141592654f);
		m_pos.AddX(float(sin(z_rotation)) * m_speed);
		m_pos.AddY(float(cos(z_rotation)) * m_speed) ;

	}

	if(glfwGetKey( 'W' )){
		
		float z_rotation;
		z_rotation = (m_rotation.GetZ() / 180 * 3.141592654f);
		m_pos.AddX(float(sin(z_rotation)) * m_speed);
		m_pos.AddY(float(cos(z_rotation)) * m_speed) ;

		m_benchmark = true;
		
		/*
		float x_rotation;
		x_rotation = (m_rotation.GetX() / 180 * 3.141592654f);
		m_pos.AddY(float(cos(x_rotation)) * m_speed);
		m_pos.AddZ(float(sin(x_rotation)) * m_speed);
		*/
	}
	if(glfwGetKey( 'S' )){
		
		float z_rotation;
		z_rotation = (m_rotation.GetZ() / 180 * 3.141592654f);
		m_pos.AddX(-float(sin(z_rotation)) * m_speed);
		m_pos.AddY(-float(cos(z_rotation)) * m_speed) ;
		
		/*
		float x_rotation;
		x_rotation = (m_rotation.GetX() / 180 * 3.141592654f);
		m_pos.AddY(-float(cos(x_rotation)) * m_speed);
		m_pos.AddZ(-float(sin(x_rotation)) * m_speed);
		*/
	}
	if(glfwGetKey( 'A' )){
		float z_rotation;
		z_rotation = (m_rotation.GetZ() / 180 * 3.141592654f);
		m_pos.AddX(-float(cos(z_rotation)) * m_speed);
		m_pos.AddY(float(sin(z_rotation)) * m_speed);


	}
	if(glfwGetKey( 'D' )){
		float z_rotation;
		z_rotation = (m_rotation.GetZ() / 180 * 3.141592654f);
		m_pos.AddX(float(cos(z_rotation)) * m_speed);
		m_pos.AddY(-float(sin(z_rotation)) * m_speed);

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
		m_pos.AddZ(-m_speed) ;
	}
	else if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)){
		m_pos.AddZ(m_speed) ;
	}
	

	m_lastMousePos.SetX(x);
	m_lastMousePos.SetY(y);
	
	
}

Vector3<float> Camera::GetPosition(){
	return m_pos;

}