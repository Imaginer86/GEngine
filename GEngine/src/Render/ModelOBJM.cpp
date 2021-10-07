#include "ModelOBJM.h"

//#include <istream>
#include <string>
//#include <sstream>
#include <fstream>

void ModelOBJM::setSizeVertex(size_t n)
{
	vertexN = n;
	Vertexs = new Vector3f[n];
}

void ModelOBJM::setVertex(size_t i, Vector3f v)
{
	Vertexs[i] = v;
}

void ModelOBJM::setSizeNormal(size_t n)
{
	normalN = n;
	Normals = new Vector3f[n];
}

void ModelOBJM::setNormal(size_t i, Vector3f n)
{
	Normals[i] = n;
}

void ModelOBJM::setSizeTextures(size_t n)
{
	texturesN = n;
	Textures = new Vector3f[n];
}

void ModelOBJM::setTexture(size_t i, Vector3f t)
{
	Textures[i] = t;
}
void ModelOBJM::setSizeQuads(size_t n)
{
	quadN = n;
	Quads = new Quad[n];
}

//void ModelOBJM::setSizeQuads(size_t g, size_t s)
//{
//	Quads[g].setSizeSurfaces(s);
//}

bool ModelOBJM::Load(const char* fileName)
{
	std::ifstream inFile;
	inFile.open(fileName, std::ios::in);

	if (!inFile.is_open()) return false;

	std::string str;
	inFile >> str >> str >> str >> str;
	//getline(inFile, str);
	//getline(inFile, str);
	//getline(inFile, str);
	//getline(inFile, str);
	//std::cout << str << std::endl;
	//getline(inFile, str);
	//std::cout << str;
	size_t vertN;
	inFile >> vertN;
	if (!vertN) return false;

	setSizeVertex(vertN);
	for (size_t i = 0; i < vertN; ++i)
	{
		char c;
		inFile >> c;
		if (c != 'v') {
			std::cerr << "Failed Loaf OBJ model vertexs" << std::endl;
			return false;
		}
		Vector3f v;
		inFile >> v;
		setVertex(i, v);
	}
	//getline(inFile, str);
	//std::cout << str;

	size_t normN;
	inFile >> normN;
	if (!normN) return false;

	setSizeNormal(normN);

	for (size_t i = 0; i < normN; ++i)
	{
		char c1, c2;
		inFile >> c1 >> c2;
		if (c1 != 'v' || c2 != 'n') {
			std::cerr << "Failed Loaf OBJ model normals" << std::endl;
			return false;
		}
		Vector3f n;
		inFile >> n;
		setNormal(i, n);
	}
	//getline(inFile, str);
	//std::cout << str;

	size_t textN;
	inFile >> textN;
	if (!textN) return false;

	setSizeTextures(textN);

	for (size_t i = 0; i < textN; ++i)
	{
		char c1, c2;
		inFile >> c1 >> c2;
		if (c1 != 'v' || c2 != 't') {
			std::cerr << "Failed Loaf OBJ model textures" << std::endl;
			return false;
		}
		Vector3f t;
		inFile >> t.x >> t.y >> t.z;
		setTexture(i, t);
	}

	size_t qqadsN;
	inFile >> qqadsN;
	if (!qqadsN) return false;
	//getline(inFile, str);
	inFile >> str >> str;
	std::cout << str;

	setSizeQuads(qqadsN);

	//TODO
	std::string mtl_name;
	//getline(inFile, mtl_name);
	inFile >> str >> str;
	inFile >> str >> str;
	inFile >> str >> mtl_name;
	std::cout << mtl_name << std::endl;

	for (size_t i = 0; i < qqadsN; ++i)
	{
		char c;
		//string gName;
		inFile >> c;// >> gName;
		if (c == 's')
		{
			--i;
			size_t t;
			inFile >> t;
			continue;
		}

		//size_t t;
		//inFile >> t;
		size_t nv, nt, nn;
		inFile >> nv >> c >> nt >> c >> nn;
		nv--;	nt--;	nn--;

		Quads[i].VertexT[0] = nv;
		Quads[i].NormalT[0] = nn;
		Quads[i].TexturesT[0] = nt;
		inFile >> nv >> c >> nt >> c >> nn;
		nv--;	nt--;	nn--;
		Quads[i].VertexT[1] = nv;
		Quads[i].NormalT[1] = nn;
		Quads[i].TexturesT[1] = nt;
		inFile >> nv >> c >> nt >> c >> nn;
		nv--;	nt--;	nn--;
		Quads[i].VertexT[2] = nv;
		Quads[i].NormalT[2] = nn;
		Quads[i].TexturesT[2] = nt;
		//inFile >> nv >> c >> nt >> c >> nn;
		//nv--;	nt--;	nn--;
		//Quads[i].VertexT[3] = nv;
		//Quads[i].NormalT[3] = nn;
		//Quads[i].TexturesT[3] = nt;
	}
	inFile.close();
	return true;

}

void ModelOBJM::Draw(Render* r)
{

	Color4f color(0.25f, 1.0f, 0.5f, 1.0f);
	for (size_t i = 0; i < quadN; ++i)
	{
		//Color4f color = Groups[i].color;
		//for (size_t j = 0; j < ; ++j)
		//{
		size_t va = Quads[i].VertexT[0];
		size_t vb = Quads[i].VertexT[1];
		size_t vc = Quads[i].VertexT[2];
		//size_t vd = Quads[i].VertexT[3];
		
		Vector3f a = Vertexs[va];
		Vector3f b = Vertexs[vb];
		Vector3f c = Vertexs[vc];
		//Vector3f d = Vertexs[vd];

		size_t naq = Quads[i].NormalT[0];
		size_t nbq = Quads[i].NormalT[1];
		size_t ncq = Quads[i].NormalT[2];
		//size_t ndq = Quads[i].NormalT[3];

		Vector3f na = Normals[naq];
		Vector3f nb = Normals[nbq];
		Vector3f nc = Normals[ncq];
		//Vector3f nd = Normals[ndq];
		
		r->drawTriangle(a, b, c, na, nb, nc, color);
		//r->drawTriangle(c, d, a, nc, nd, na, color);
	}
}
