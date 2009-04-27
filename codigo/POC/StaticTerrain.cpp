#include "stdafx.h"
#include "StaticTerrain.h"
#include "Heightmask.h"
#include "Vector3.h"
#include <IL/il.h>
#include <string>
#include <iostream>
using namespace std;



StaticTerrain::StaticTerrain(int renderStepSize, Vector3<float> color, Vector3<float> position, int width, int height) : Terrain(renderStepSize, color, position, width, height){

	


}

void StaticTerrain::Render(bool wireFrame, int colorToRender){

	Terrain::Render(wireFrame,colorToRender);
}

