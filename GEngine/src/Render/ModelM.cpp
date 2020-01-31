#include "ModelM.h"

void ModelM::setSizeVertex(size_t n)
{
	vertexN = n;
	Vertexs = new Vector3f[n];
}

void ModelM::setSizeNormal(size_t n)
{
	normalN = n;
	Normals = new Vector3f[n];
}

void ModelM::setSizeGroup(size_t n)
{
	groupN = n;
	Groups = new Group[n];
}
