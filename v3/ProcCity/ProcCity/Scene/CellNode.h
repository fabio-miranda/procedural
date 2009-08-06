#ifndef CellNode_H
#define CellNode_H


#include "../Util/VBO.h"
#include "../Util/Segment.h"


class CellNode : public Node{

	

public:
	CellNode();

	void AddSegment();

private:

	void Update();
	void Render();


	Segment<float>* m_segments;
	VBO* m_vbo;
};

#endif