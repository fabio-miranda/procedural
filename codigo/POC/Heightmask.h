#ifndef HEIGHTMASK_H
#define HEIGHTMASK_H

#include <vector>
#include "Node.h"
#include "Vector3.h"
using namespace::std;


class Heightmask{
private:
	unsigned char* m_imageData;
	int m_height;
	int m_width;

	
public:
	Heightmask();
	Heightmask(char*);
	bool GetBoolValue(int, int);


};

#endif