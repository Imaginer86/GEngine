#pragma once
#include "../Math/Vector3f.h"
#include "../Render/Color4f.h"

#include "../Render/Render.h"

class ModelOBJM
{
public:
	size_t	vertexN;
	Vector3f* Vertexs;
	size_t	normalN;
	Vector3f* Normals;
	size_t	texturesN;
	Vector3f* Textures;

	struct Quad
	{
		size_t	VertexT[4];
		size_t	NormalT[4];
		size_t	TexturesT[4];
	};

	/*struct Surface
	{
		//Quad quad;
		size_t	surfacesN;
		Quad Surfaces;
		//Color4f color;
		//void setSizeSurfaces(size_t n)
		//{
			//surfacesN = n;
			//Surfaces = new Quad[n];
		//}
		Surface() :surfacesN(0){};

		~Surface() { }
	};
	*/
	size_t	quadN;
	Quad* Quads;

public:
	ModelOBJM() :vertexN(0), Vertexs(nullptr), normalN(0), Normals(nullptr), texturesN(0), Textures(nullptr), quadN(0), Quads(nullptr) {}
	~ModelOBJM() { delete[] Quads; delete[] Normals; delete[] Vertexs; delete[] Textures; }
	void setSizeVertex(size_t n);
	void setVertex(size_t i, Vector3f v);
	void setSizeNormal(size_t n);
	void setNormal(size_t i, Vector3f n);
	void setSizeTextures(size_t n);
	void setTexture(size_t i, Vector3f n);
	void setSizeQuads(size_t n);
	//void setSizeQuad(size_t g, size_t s);
	bool Load(const char* fileName);
	void Draw(Render* r);
};
