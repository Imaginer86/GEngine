#pragma once
#include "../Math/Vector3f.h"
#include "../Render/Color4f.h"

struct ModelM
{
	size_t vertexN;
	size_t normalN;
	Vector3f* Vertexs;
	Vector3f* Normals;

	struct Triangle
	{
		size_t VertexT[3];
		size_t NormalT[3];
	};

	struct Group
	{
		size_t surfacesN;
		Triangle* Surfaces;
		Color4f color;
		void setSizeSurfaces(size_t n)
		{
			surfacesN = n;
			Surfaces = new Triangle[n];
		}

		~Group() { delete[] Surfaces; }
	};

	size_t groupN;

	Group* Groups;

	~ModelM() { delete[] Groups; delete[] Normals; delete[] Vertexs; }

	void setSizeVertex(size_t n);
	void setSizeNormal(size_t n);
	void setSizeGroup(size_t n);
};
