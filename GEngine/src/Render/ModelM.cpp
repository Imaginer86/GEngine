#include "ModelM.h"

void ModelM::setSizeVertex(unsigned n)
{
	vertexN = n;
	Vertexs = new Vector3f[n];
}

void ModelM::setVertex(unsigned i, Vector3f v)
{
	Vertexs[i] = v;
}

void ModelM::setSizeNormal(unsigned n)
{
	normalN = n;
	Normals = new Vector3f[n];
}

void ModelM::setNormal(unsigned i, Vector3f n)
{
	Normals[i] = n;
}

void ModelM::setSizeGroup(unsigned n)
{
	groupN = n;
	Groups = new Group[n];
}

void ModelM::setSizeSurface(unsigned g, unsigned s)
{
	Groups[g].setSizeSurfaces(s);
}

void ModelM::Draw(Render* r)
{
	/*
	float xmin = 0;
	float ymin = 0;
	float zmin = 0;
	float xmax = 0;
	float ymax = 0;
	float zmax = 0;
	*/
	for (size_t i = 0; i < groupN; ++i)
	{
		Color4f color = Groups[i].color;
		for (size_t j = 0; j < Groups[i].surfacesN; ++j)
		{
			Vector3f a = Vertexs[Groups[i].Surfaces[j].VertexT[0]];
			Vector3f b = Vertexs[Groups[i].Surfaces[j].VertexT[1]];
			Vector3f c = Vertexs[Groups[i].Surfaces[j].VertexT[2]];

			Vector3f na = Normals[Groups[i].Surfaces[j].NormalT[0]];
			Vector3f nb = Normals[Groups[i].Surfaces[j].NormalT[1]];
			Vector3f nc = Normals[Groups[i].Surfaces[j].NormalT[2]];

			r->drawTriangle(a, b, c, na, nb, nc, color);

			/*
			if (a.x < xmin) xmin = a.x;
			if (b.x < xmin) xmin = b.x;
			if (c.x < xmin) xmin = c.x;
			if (a.y < ymin) ymin = a.y;
			if (b.y < ymin) ymin = b.y;
			if (c.y < ymin) ymin = c.y;
			if (a.z < zmin) zmin = a.z;
			if (b.z < zmin) zmin = b.z;
			if (c.z < zmin) zmin = c.z;

			if (a.x > xmax) xmax = a.x;
			if (b.x > xmax) xmax = b.x;
			if (c.x > xmax) xmax = c.x;
			if (a.y > ymax) ymax = a.y;
			if (b.y > ymax) ymax = b.y;
			if (c.y > ymax) ymax = c.y;
			if (a.z > zmax) zmax = a.z;
			if (b.z > zmax) zmax = b.z;
			if (c.z > zmax) zmax = c.z;
			*/
		}
	}
}
