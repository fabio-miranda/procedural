#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "vector"
#include "Camera.h"
#include "Menu.h"
#include "Node.h"
#include "Skybox.h"
using namespace::std;

class Framework{

protected:
	int m_width;
	int m_height;
	
	//vector<Node*> m_sceneGraph;
	//vector<Node*>::iterator m_iterator;

	Camera* m_camera;
	Menu* m_menu;
	Skybox* m_skybox;
	Node* m_currentNode;
	

	bool m_isRunning;
	bool m_wireFrame;
	int m_colorToRender;


	Framework(int, int);
	virtual void Init();
	void DoUpdate();
	void DoRender();
	void GLConfig();
	void Light();
	void InitLight();

public:
	

	virtual int Start();

};

#endif