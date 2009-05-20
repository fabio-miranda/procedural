#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Vector2.h"
#include "Vector3.h"
#include "math.h"
#include "GL/glfw.h"

class Camera{

public:
	Camera(Vector3<float>, Vector3<float>);
	void Update();
	Vector3<float> GetPosition();
	

	Vector3<float> m_pos;
	Vector3<float> m_up;
	Vector2<float> m_rotation;
	Vector2<float> m_lastMousePos;

	float fov;


private:
	void UpdateKeyboard();
	void UpdateMouse();
	

};

#endif