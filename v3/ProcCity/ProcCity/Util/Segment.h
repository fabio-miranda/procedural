#ifndef SEGMENT_H
#define SEGMENT_H


#include "GL/glew.h"
#include "Vector3.h"

template <typename T>
class Segment{

private:
	Vector3<T> point1;
	Vector3<T> point2;


public:

	Segment(T x1, T y1, T z1, T x2, T y2, T z2){
		point1 = new Vector3<T>(x1, y1, z1);
		point2 = new Vector3<T>(x2, y2, z2);
	}
	

};

#endif