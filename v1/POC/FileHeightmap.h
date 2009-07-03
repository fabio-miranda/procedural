#ifndef FILEHEIGHTMAP_H
#define FILEHEIGHTMAP_H

#include "node.h"
#include "StaticTerrain.h"
#include "Vector3.h"

class FileHeightmap : public StaticTerrain{
private:
	char* m_imageAdress;

public:
	FileHeightmap(int, Vector3<float>, Vector3<float>, int, int, char *);
	virtual void FillHeightMap();

};

#endif
