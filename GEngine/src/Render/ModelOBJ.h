#pragma once
#include "../Math/Vector3f.h"
#include "../Render/Color4f.h"

#include "../Render/Render.h"
#include "MaterialMTL.h"


class ModelOBJ
{
public:
	struct Triangle
	{
		size_t	VertexT[3];
		size_t	NormalT[3];
		size_t	TexturesT[3];
	};
	struct Quad
	{
		size_t	VertexT[4];
		size_t	NormalT[4];
		size_t	TexturesT[4];
	};
public:
	bool isQuad = false;
	size_t	trianglesN;
	Triangle* Triangles;
	size_t quadsN;
	Quad* Quads;
	size_t	vertexN;
	Vector3f*	Vertexs;
	size_t	normalN;
	Vector3f*	Normals;
	size_t	texturesN;
	Vector3f* Textures;

	size_t materialN;
	MaterialMTL::MTL* Materials;

public:
	//ModelOBJ() {}
	ModelOBJ():vertexN(0), Vertexs(nullptr), normalN(0), Normals(nullptr), texturesN(0), Textures(nullptr), quadsN(0), Quads(nullptr), trianglesN(0), Triangles(nullptr), materialN(0), Materials(nullptr) {}
	~ModelOBJ() { delete[] Normals; delete[] Vertexs; delete[] Textures; delete[] Triangles; delete[] Quads; delete[] Materials; }

	ModelOBJ(const ModelOBJ& x);
	ModelOBJ& operator=(const ModelOBJ& x);

	void setSizeVertex(size_t n);
	void setVertex(size_t i, Vector3f v);
	void setSizeNormal(size_t n);
	void setNormal(size_t i, Vector3f n);
	void setSizeTextures(size_t n);
	void setTexture(size_t i, Vector3f n);
	void setSizeTriangles(size_t n);
	void setSizeQuads(size_t n);
	//void setSizeQuad(size_t g, size_t s);
	bool Load(const char* directory, const char* fileName, bool isQuads = false, bool noTextIndexs = false,  bool twoUV = false);
	//bool LoadM(const char* fileName);
	void Draw(Render* r);
};
