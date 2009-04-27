#ifndef MESH_H
#define MESH_H

#include "Vector3.h"

class Mesh{


private:
	void SetVertexAndColor(int, Vector3<float>);
	

	int m_height;
	int m_width;
	Vector3<float> m_position;
	Vector3<float> m_color;

	
	


public:
	~ Mesh();
	Mesh(Vector3<float>, Vector3<float>, int, int);
	void AddHeight(int, int, float);
	float GetHeight(int, int);
	Vector3<float> GetColorGrayScale(int, int);
	Vector3<float> GetColorGreen(int, int);
	Vector3<float> GetColorMix(int, int);
	void BuildVBOs();
	void CopyVertexFromHeightMap();
	

	unsigned char* m_heightMap;
	GLuint m_vboVertices;
	GLuint m_vboColorGrayScale;
	GLuint m_vboColorGreen;
	GLuint m_vboColorMix;
	GLuint m_vboTexCoord;
	//GLuint m_vboIndices;
	int	m_vertexCount;
	float* m_vertices;
	float* m_colorGrayScale;
	float* m_colorGreen;
	float* m_colorMix;
	float* m_texCoord;

	
};

#endif
