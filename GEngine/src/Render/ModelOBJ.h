#pragma once
#include "../Math/Vector3f.h"
#include "../Render/Color4f.h"

#include "../Render/Render.h"

class ModelOBJ
{
public:
	size_t	vertexN;
	Vector3f*	Vertexs;
	size_t	normalN;
	Vector3f*	Normals;
	size_t	texturesN;
	Vector3f* Textures;
	
	struct Triangle
	{
		size_t	VertexT[3];
		size_t	NormalT[3];
		size_t	TexturesT[3];
	};
	size_t	triangleN;
	Triangle* Triangles;

public:
	ModelOBJ():vertexN(0), Vertexs(nullptr), normalN(0), Normals(nullptr), texturesN(0), Textures(nullptr), triangleN(0), Triangles(nullptr) {}
	~ModelOBJ() { delete[] Normals; delete[] Vertexs; delete[] Textures; delete[] Triangles; }
	void setSizeVertex(size_t n);
	void setVertex(size_t i, Vector3f v);
	void setSizeNormal(size_t n);
	void setNormal(size_t i, Vector3f n);
	void setSizeTextures(size_t n);
	void setTexture(size_t i, Vector3f n);
	void setSizeTriangles(size_t n);
	//void setSizeQuad(size_t g, size_t s);
	bool Load(const char* fileName);
	void Draw(Render* r);
};