#include "ModelOBJ.h"

//#include <istream>
#include <string>
#include <sstream>
#include <fstream>

#include <list>

void ModelOBJ::setSizeVertex(size_t n)
{
	vertexN = n;
	Vertexs = new Vector3f[n];
}

void ModelOBJ::setVertex(size_t i, Vector3f v)
{
	Vertexs[i] = v;
}

void ModelOBJ::setSizeNormal(size_t n)
{
	normalN = n;
	Normals = new Vector3f[n];
}

void ModelOBJ::setNormal(size_t i, Vector3f n)
{
	Normals[i] = n;
}

void ModelOBJ::setSizeTextures(size_t n)
{
	texturesN = n;
	Textures = new Vector3f[n];
}

void ModelOBJ::setTexture(size_t i, Vector3f t)
{
	Textures[i] = t;
}
void ModelOBJ::setSizeTriangles(size_t n)
{
	triangleN = n;
	Triangles = new Triangle[n];
}

//void ModelOBJ::setSizeQuads(size_t g, size_t s)
//{
//	Quads[g].setSizeSurfaces(s);
//}

bool ModelOBJ::Load(const char* fileName, bool toUV)
{
	std::ifstream inFile;
	inFile.open(fileName, std::ios::in);

	if (!inFile.is_open()) return false;

	std::string mtl_name;

	size_t vertN = 0;
	std::list<Vector3f> VertexsL;
	size_t normN = 0;
	std::list<Vector3f> NormalsL;
	size_t textN = 0;
	std::list<Vector3f> TexturesL;

	size_t triN = 0;
	std::list<Triangle> TrianglesL;

	std::string str;
	while (getline(inFile, str))
	{
		std::stringstream sstr(str);
		char c;
		sstr >> c;
		if (c == '#')
		{
			continue;
		}
		else if (c == 'o')
		{
			continue;
		}
		else if (c == 'v')
		{
			Vector3f v;
			sstr >> v;
			if (v != VETOR3f_ZERO) //TODO
			{
				vertN++;
				VertexsL.push_back(v);
			}
			else
			{
				sstr.clear();
				char c1;
				sstr >> c1;
				if (c1 == 'n')
				{
					Vector3f n;
					sstr >> n;
					if (n != VETOR3f_ZERO) //TODO
					{
						normN++;
						NormalsL.push_back(n);
					}
					else
					{
						std::cerr << "Eror Load Normals Obj File " << fileName << std::endl;
						continue;						
					}
				}
				else if (c1 == 't')
				{
					Vector3f t;
					if (toUV)
					{
						sstr >> t.x >> t.y;
						t.z = 0.0f;
					}
					else
					{
						sstr >> t;
					}
					textN++;
					TexturesL.push_back(t);
					if (t != VETOR3f_ZERO)//TODO
					{

					}
					else
					{
						std::cerr << "Eror Load Textures UV Obj File " << fileName << std::endl;
						continue;						
					}
				}
				else
				{
					std::cerr << "Eror Load Obj File " << fileName << std::endl;
					continue;					
				}

			}

		}
		else if (c == 'm')
		{
			continue;
		}
		else if (c == 'g')
		{
			continue;
		}
		else if (c == 'u')
		{
			char cc;
			sstr >> cc >> cc >> cc >> cc >> cc;
			sstr >> mtl_name;
			std::cout << mtl_name << std::endl;
		}
		else if (c == 's')
		{
			continue;
		}
		else if (c == 'f')
		{
			Triangle tTriangle;
			triN++;
			char cc;
			size_t cv, ct, cn;
			sstr >> cv >> cc >> cn >> cc >> ct;
			cv--; ct--; cn--;
			tTriangle.VertexT[0] = cv; tTriangle.NormalT[0] = cn; tTriangle.TexturesT[0] = ct;
			sstr >> cv >> cc >> cn >> cc >> ct;
			cv--; ct--; cn--;
			tTriangle.VertexT[1] = cv; tTriangle.NormalT[1] = cn; tTriangle.TexturesT[1] = ct;
			sstr >> cv >> cc >> cn >> cc >> ct;
			cv--; ct--; cn--;
			tTriangle.VertexT[2] = cv; tTriangle.NormalT[2] = cn; tTriangle.TexturesT[2] = ct;
			TrianglesL.push_back(tTriangle);
		}
	}
	//TTT str.clear();

	setSizeVertex(vertN);
	for (size_t i = 0; i < vertN; ++i)
	{
		Vertexs[i] = VertexsL.front();
		VertexsL.pop_front();
	}

	setSizeNormal(normN);
	for (size_t i = 0; i < normN; ++i)
	{
		Normals[i] = NormalsL.front();
		NormalsL.pop_front();
	}

	setSizeTextures(textN);
	for (size_t i = 0; i < textN; ++i)
	{
		Textures[i] = TexturesL.front();
		TexturesL.pop_front();
	}

	setSizeTriangles(triN);
	for (size_t i = 0; i < triN; ++i)
	{
		Triangles[i] = TrianglesL.front();
		TrianglesL.pop_front();
	}

	inFile.close();

	std::cout << "Vertexs: " << vertN << " Normals: " << normN << " Textures: " << textN << " Triangles: " << triN << std::endl;
	return true;

}

bool ModelOBJ::LoadM(const char* fileName)
{
	std::ifstream inFile;
	inFile.open(fileName, std::ios::in);

	if (!inFile.is_open()) return false;

	std::string str;
	getline(inFile, str);
	getline(inFile, str);
	getline(inFile, str);//TODO
	getline(inFile, str);
	getline(inFile, str);
	getline(inFile, str);
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
	getline(inFile, str);
	std::cout << str << std::endl; //TODO
	getline(inFile, str);
	getline(inFile, str);
	getline(inFile, str);
	std::cout << str << std::endl; //TODO


	setSizeTriangles(qqadsN);

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

		char cc;
		size_t cv, ct, cn;
		inFile >> cv >> cc >> ct >> cc >> cn;
		--cv; --ct; --cn;
		Triangles[i].VertexT[0] = cv; Triangles[i].TexturesT[0] = ct; Triangles[i].NormalT[0] = cn;
		inFile >> cv >> cc >> ct >> cc >> cn;
		--cv; --ct; --cn;
		Triangles[i].VertexT[1] = cv; Triangles[i].TexturesT[1] = ct; Triangles[i].NormalT[1] = cn;
		inFile >> cv >> cc >> ct >> cc >> cn;
		--cv; --ct; --cn;
		Triangles[i].VertexT[2] = cv; Triangles[i].TexturesT[2] = ct; Triangles[i].NormalT[2] = cn;

	}
	inFile.close();
	std::cout << "Vertexs: " << vertexN << " Normals: " << normalN << " Textures: " << texturesN << " Triangles: " << triangleN << std::endl;
	return true;
}

void ModelOBJ::Draw(Render* r)
{

	Color4f color(0.25f, 1.0f, 0.5f, 1.0f);
	for (size_t i = 0; i < triangleN; ++i)
	{
		//Color4f color = Groups[i].color;
		//for (size_t j = 0; j < ; ++j)
		//{
		size_t va = Triangles[i].VertexT[0];
		size_t vb = Triangles[i].VertexT[1];
		size_t vc = Triangles[i].VertexT[2];
		//size_t vd = Quads[i].VertexT[3];
		
		Vector3f a = Vertexs[va];
		Vector3f b = Vertexs[vb];
		Vector3f c = Vertexs[vc];
		//Vector3f d = Vertexs[vd];

		size_t naq = Triangles[i].NormalT[0];
		size_t nbq = Triangles[i].NormalT[1];
		size_t ncq = Triangles[i].NormalT[2];
		//size_t ndq = Quads[i].NormalT[3];

		Vector3f na = Normals[naq];
		Vector3f nb = Normals[nbq];
		Vector3f nc = Normals[ncq];
		//Vector3f nd = Normals[ndq];
		
		r->drawTriangle(a, b, c, na, nb, nc, color);
		//r->drawTriangle(a, b, c, color);
		//r->drawTriangle(c, d, a, nc, nd, na, color);
	}
}
