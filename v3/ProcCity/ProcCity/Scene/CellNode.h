#ifndef CellNode_H
#define CellNode_H

#include "Node.h"
#include "../Util/VBO.h"
#include "../Util/Segment.h"


class CellNode : public Node{

	

public:
	CellNode();

	//void AddSegment(Segment* segment);
	void SetVertices(int numVertices, double* vertices, double* position);

private:

	void Update();
	void Render();


	//Segment<float>* m_segments;
	double* m_vertices;
	int m_numVertices;
	Vector3<double>* m_position;
	//VBO* m_vbo;
};

#endif