#ifndef CityMng_H
#define CityMng_H

#include "GL/glew.h"
#include "Util/Random.h"
#include "Util/Vector3.h"
#include "Util/Gui.h"
#include "Scene/Node.h"
#include "Scene/CellNode.h"
#include "Voronoi/VoronoiDiagramGenerator.h"
#include "Defines.h"
#include "Config.h"



class CityMng{

	

public:
	CityMng();
	void Update(Vector3<float>);
	void Render(double);


	GUI* m_gui;

private:

	void Config();
	void initLight();
	void initNodes();
	void GenerateNeighbours(short oldIndex, short newIndex);

	Vector3<float> m_translation;
	int m_size;
	Node* m_parentNode;

};

#endif