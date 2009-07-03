#ifndef VERTEX_H
#define VERTEX_H


#include "GL/glew.h"
#include "GL/glfw.h"

struct Vertex
{
   float x, y, z;
   //GLuint color;
   //float s, t;
   //float padding[2]; //Performance: this way, the struct is 32 bytes (http://www.ati.com/developer/gdc/PerformanceTuning.pdf)
};

static Vertex* MidPoint(Vertex a, Vertex b){

	Vertex* aux = new Vertex();
	
	aux->x = (a.x + b.x) / 2.0f;
	aux->y = (a.y + b.y) / 2.0f;
	aux->z = (a.z + b.z) / 2.0f;


	return aux;


}



#endif
