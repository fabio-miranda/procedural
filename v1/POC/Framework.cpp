#include "stdafx.h"
#include "Framework.h"
#include "FileHeightmap.h"
#include "Vector3.h"
#include "GL/glew.h"
#include "GL/glfw.h"
//#include "AntTweakBar.h"
#include <IL/il.h>
#include "Constants.h"




Framework::Framework(int p_width, int p_height)
{
	m_width = p_width;
	m_height = p_height;

	
	//Camera
	m_camera = new Camera(Vector3<float>(10, 250, 10), Vector3<float>(0,0,0));

	
	

	

}


void Framework::Init(){
	
	int ok;

	glfwInit();

	ok = glfwOpenWindow(
							m_width, m_height,          // Width and height of window
							8, 8, 8,           // Number of red, green, and blue bits for color buffer
							8,                 // Number of bits for alpha buffer
							24,                // Number of bits for depth buffer (Z-buffer)
							0,                 // Number of bits for stencil buffer
							GLFW_WINDOW        // We want a desktop window (could be GLFW_FULLSCREEN)
						);

    // If we could not open a window, exit now
    if( !ok )
    {
        glfwTerminate();
    }

	int err=glewInit();
	if(err!=GLEW_OK)
	{
		glfwTerminate();
	}

	// Initialize AntTweakBar
    if( !TwInit(TW_OPENGL, NULL) )
    {
        // A fatal error occured 
        glfwTerminate();
    }
	TwWindowSize(m_width, m_height);


	//Initialize DevIL
	ilInit();



    // Set window title
    glfwSetWindowTitle( "POC I - Fabio Miranda" );

	// Enable sticky keys
    glfwEnable( GLFW_STICKY_KEYS );
	//glfwEnable( GLFW_KEY_REPEAT );

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


	glEnable(GL_TEXTURE_2D);

	m_isRunning = true;
	m_colorToRender = 0;




	
	//Menu
	//m_menu = new Menu();

	//Skybox
	m_skybox = new Skybox();

	


}

int Framework::Start(){
	
	Init();


	while(m_isRunning){
		DoUpdate();
		DoRender();
		glfwSwapBuffers();

		m_isRunning = (!glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED ));


	}

	glfwTerminate();
	TwTerminate();
	return 0;

}

void Framework::GLConfig(){
	double t;              // Time (in seconds)

    // Get current time
    t = glfwGetTime();

    glfwGetWindowSize( &m_width, &m_height );
    glViewport( 0, 0, m_width, m_height );

    // Clear color and depht buffers
    glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    // Set up projection matrix
    glMatrixMode( GL_PROJECTION );    // Select projection matrix
    glLoadIdentity();                 // Start with an identity matrix
    gluPerspective(                   // Set perspective view
        90.0,                         // Field of view = 65 degrees
        (double)m_width/(double)m_height, // Window aspect (assumes square pixels)
        1.0,                          // Near Z clipping plane
        10000.0                         // Far Z clippling plane
    );

    // Set up modelview matrix
	/*
    glMatrixMode( GL_MODELVIEW );     // Select modelview matrix
    glLoadIdentity();                 // Start with an identity matrix
    gluLookAt(                        // Set camera position and orientation
        0.0, 0.0, 10.0,               // Camera position (x,y,z)
        0.0, 0.0, 0.0,                // View point (x,y,z)
        0.0, 1.0, 0.0                 // Up-vector (x,y,z)
    );
	*/


	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glRotatef(m_camera->m_rotation.GetX(),1.0,0.0,0.0); //rotate our camera on teh x-axis (left and right)
	glRotatef(m_camera->m_rotation.GetY(),0.0,1.0,0.0); //rotate our camera on the y-axis (up and down)
	glTranslated(-m_camera->m_pos.GetX(),-m_camera->m_pos.GetY(),-m_camera->m_pos.GetZ()); //translate the screen to the position of our camera



	
}



void Framework::DoUpdate(){
	m_camera->Update();


	//Keyboard
	if(glfwGetKey( '1' )){
		m_wireFrame = true;

	}
	if(glfwGetKey( '2' )){
		m_wireFrame = false;
	}

	if(glfwGetKey( 'Z' ))
		m_colorToRender = COLOR_GRAYSCALE;
	else if(glfwGetKey( 'X' ))
		m_colorToRender = COLOR_MIX;
	else if(glfwGetKey( 'C' ))
		m_colorToRender = COLOR_GREEN;

}

void Framework::DoRender(){

	GLConfig();
	
	
	//Light
	//Framework::InitLight();

	//Skybox
	m_skybox->RenderSkybox(m_camera->m_pos);

	
	m_currentNode->Render(m_wireFrame, m_colorToRender);


	//See if the camera is on another node. If so, we have to generate its neighbours
	if(m_currentNode->IsWithin(m_camera->m_pos) == false){

		m_currentNode = m_currentNode->FindCurrentStandingNode(m_camera->m_pos);
	}

	

	// Draw tweak bars
    TwDraw();

	/*
	for (m_iterator = m_sceneGraph.begin(); m_iterator != m_sceneGraph.end(); m_iterator++ )
	{
		Node& node = **m_iterator;

		//cout << &node;
		//cout << "\n";

		node.Render();

		
		//See if the camera is on the node
		if(node.IsWithin(camera->m_pos)){

			//See if the node is different from the last one (so we have to generate more patchs)
			if(m_currentNode->m_position.equals(node.m_position) == false){
				//cout << "caiu";

				node.GenerateNeighbours(m_currentNode);


				m_currentNode = &node;

			}

			//node.GenerateNeighbours();
		}
	}
	*/

	
}

void Framework::InitLight(){
	//Light
	
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);


	GLfloat light_ambient[] =
	{0.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse[] =
	{1.0, 1.0, 1.0, 1.0};
	GLfloat light_specular[] =
	{1.0, 1.0, 1.0, 1.0};
	GLfloat light_position[] =
	{0.0, -1.0, 25.0, 0.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	


}