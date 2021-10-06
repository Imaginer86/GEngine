#pragma once
#include "../Math/Vector3f.h"
#include "../Render/Color4f.h"

#include "../Render/Render.h"

class ModelM
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
		size_t	VertexT[4];
		size_t	NormalT[4];
		size_t	TexturesT[4];
	};

	struct Group
	{
		size_t	surfacesN;
		Triangle* Surfaces;
		Color4f color;
		void setSizeSurfaces(size_t n)
		{
			surfacesN = n;
			Surfaces = new Triangle[n];
		}

		~Group() { delete[] Surfaces; }
	};

	size_t	groupN;
	Group* Groups;



public:
	ModelM() {}
	~ModelM() { delete[] Groups; delete[] Normals; delete[] Vertexs; delete[] Textures; }
	void setSizeVertex(size_t n);
	void setVertex(size_t i, Vector3f v);
	void setSizeNormal(size_t n);
	void setNormal(size_t i, Vector3f n);
	void setSizeTextures(size_t n);
	void setTexture(size_t i, Vector3f n);
	void setSizeGroup(size_t n);
	void setSizeSurface(size_t g, size_t s);
	void Draw(Render* r);
};
