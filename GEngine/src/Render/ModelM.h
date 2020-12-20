#pragma once
#include "../Math/Vector3f.h"
#include "../Render/Color4f.h"

#include "../Render/Render.h"

class ModelM
{
public:
	unsigned vertexN;
	unsigned normalN;
	Vector3f* Vertexs;
	Vector3f* Normals;
	struct Triangle
	{
		unsigned VertexT[3];
		unsigned NormalT[3];
	};

	struct Group
	{
		unsigned surfacesN;
		Triangle* Surfaces;
		Color4f color;
		void setSizeSurfaces(unsigned n)
		{
			surfacesN = n;
			Surfaces = new Triangle[n];
		}

		~Group() { delete[] Surfaces; }
	};

	unsigned groupN;
	Group* Groups;



public:
	ModelM() {}
	~ModelM() { delete[] Groups; delete[] Normals; delete[] Vertexs; }
	void setSizeVertex(unsigned n);
	void setVertex(unsigned i, Vector3f v);
	void setSizeNormal(unsigned n);
	void setNormal(unsigned i, Vector3f n);
	void setSizeGroup(unsigned n);
	void setSizeSurface(unsigned g, unsigned s);
	void Draw(Render* r);
};
