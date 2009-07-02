#ifndef CAMERA_H
#define CAMERA_H

#include "Util/Vector3.h"
#include "Util/Vector2.h"
#include "math.h"
#include "GL/glfw.h"

class Camera{

public:
	Camera(Vector3<float>, Vector3<float>);
	Vector3<float> GetPosition();
	void UpdateKeyboard();
	void UpdateMouse();
	

	Vector3<float> m_pos;
	Vector3<float> m_up;
	Vector3<float> m_rotation;
	Vector2<int> m_lastMousePos;
	float m_speed;

	float fov;


	
	

};

#endif