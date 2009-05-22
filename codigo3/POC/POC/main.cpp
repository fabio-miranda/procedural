// main.cpp : Defines the entry point for the console application.
//

#include "ProcTerrain/TerrainMng.h"
#include "ProcTerrain/Scene/SquareNode.h"
#include "WindowMng.h"
#include "Camera.h"


int main( int argc, char **argv ){
	
	//The WindowMng is responsable for opening and setting the window (something that the game would do, not the TerrainMng)
	WindowMng window = WindowMng(1280,720);
	window.GLInit();


	//Create the terrain
	TerrainMng* terrain = new TerrainMng();
	SquareNode* node = new SquareNode(Vector3<float>(0,0,0),50.0f, 1);
	node->GenerateNeighbours(NULL);
	//terrain->AddNode(node);
	terrain->SetCurrentNode(node);
	


	

	while(window.isRunning()){
		window.GLConfig();
		window.UpdateCamera();
		
		
		//===The important stuff
		terrain->Update(window.GetCameraPosition());
		terrain->Render();
		//===

		glfwSwapBuffers();

	}
}

