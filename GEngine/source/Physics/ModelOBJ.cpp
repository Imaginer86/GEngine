#include "ModelOBJ.h"

//#include <istream>
#include <string>
#include <sstream>
#include <fstream>

#include <list>

	// Конструктор копирования, который выполняет глубокое копирование
ModelOBJ::ModelOBJ(const ModelOBJ& x)
{
	// Копируем передаваемый объект
	trianglesN = x.trianglesN;
	Triangles = new Triangle[trianglesN];
	for (size_t i = 0; i < trianglesN; ++i)
	{
		Triangles[i].VertexT[0] = x.Triangles[i].VertexT[0];
		Triangles[i].VertexT[1] = x.Triangles[i].VertexT[1];
		Triangles[i].VertexT[2] = x.Triangles[i].VertexT[2];

		Triangles[i].NormalT[0] = x.Triangles[i].NormalT[0];
		Triangles[i].NormalT[1] = x.Triangles[i].NormalT[2];
		Triangles[i].NormalT[2] = x.Triangles[i].NormalT[1];

		Triangles[i].TexturesT[0] = x.Triangles[i].TexturesT[0];
		Triangles[i].TexturesT[1] = x.Triangles[i].TexturesT[1];
		Triangles[i].TexturesT[2] = x.Triangles[i].TexturesT[2];


	}
	vertexN = x.vertexN;
	Vertexs = new Vector3f[vertexN];
	for (size_t i = 0; i < vertexN; ++i)	Vertexs[i] = x.Vertexs[i];
	normalN = x.normalN;
	for (size_t i = 0; i < normalN; ++i)	Normals[i] = x.Normals[i];
	Normals;
	texturesN = x.texturesN;
	for (size_t i = 0; i < texturesN; ++i)	Textures[i] = x.Textures[i];
}

// Оператор присваивания копированием, который выполняет глубокое копирование
ModelOBJ& ModelOBJ::operator=(const ModelOBJ& x)
{
	// Проверка на самоприсваивание
	if (&x == this)
		return *this;

	// Удаляем всё, что к этому моменту может хранить указатель 
	delete[] Normals; delete[] Vertexs; delete[] Textures; delete[] Triangles;

	// Копируем передаваемый объект
	trianglesN = x.trianglesN;
	Triangles = new Triangle[trianglesN];
	for (size_t i = 0; i < trianglesN; ++i)
	{
		Triangles[i].VertexT[0] = x.Triangles[i].VertexT[0];
		Triangles[i].VertexT[1] = x.Triangles[i].VertexT[1];
		Triangles[i].VertexT[2] = x.Triangles[i].VertexT[2];

		Triangles[i].NormalT[0] = x.Triangles[i].NormalT[0];
		Triangles[i].NormalT[1] = x.Triangles[i].NormalT[2];
		Triangles[i].NormalT[2] = x.Triangles[i].NormalT[1];

		Triangles[i].TexturesT[0] = x.Triangles[i].TexturesT[0];
		Triangles[i].TexturesT[1] = x.Triangles[i].TexturesT[1];
		Triangles[i].TexturesT[2] = x.Triangles[i].TexturesT[2];


	}
	vertexN = x.vertexN;
	Vertexs = new Vector3f[vertexN];
	for (size_t i = 0; i < vertexN; ++i)	Vertexs[i] = x.Vertexs[i];
	normalN = x.normalN;
	for (size_t i = 0; i < normalN; ++i)	Normals[i] = x.Normals[i];
	Normals;
	texturesN = x.texturesN;
	for (size_t i = 0; i < texturesN; ++i)	Textures[i] = x.Textures[i];
	return *this;
}

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
	trianglesN = n;
	Triangles = new Triangle[n];
}

void ModelOBJ::setSizeQuads(size_t n)
{
	quadsN = n;
	Quads = new Quad[n];
}

bool ModelOBJ::Load(const char* directory, const char* fileName, bool isQuads_, bool noTextIndexs_,bool twoUV)
{
	isQuad = isQuads_;
	std::ifstream inFile;
	inFile.open(std::string(directory) + '/' + std::string(fileName), std::ios::in);

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

	size_t quadN = 0;
	std::list<Quad> QuadsL;

	size_t matN;
	std::list<MaterialMTL> MaterialsL;

	std::string str;
	while (getline(inFile, str))
	{
		if (str.empty()) continue;
		std::stringstream sstr(str);
		char c;
		sstr >> c;
		if (c == '#')	continue;
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
					normN++;
					NormalsL.push_back(n);
					if (n == VETOR3f_ZERO) //TODO
					{
						std::cerr << "Eror Load Normals Obj File " << fileName << std::endl;
						continue;
					}
				}
				else if (c1 == 't')
				{
					Vector3f t;
					if (twoUV)
					{
						sstr >> t.x >> t.y;
						t.z = 0.0f;
					}
					else
					{
						sstr >> t;
					}
					normN++;
					NormalsL.push_back(t);
					if (t == VETOR3f_ZERO)//TODO
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
			char c1, c2, c3, c4, c5;
			sstr >> c1 >> c2 >> c3 >> c4 >> c5;
			if (c1 == 't' && c2 == 'l' && c3 == 'l' && c4 == 'i' && c5 == 'b')
			{
				std::string mtlFileName;
				sstr >> mtlFileName;
				//std::cout << mtlFileName << std::endl;
				MaterialMTL material;
				Materials = material.Load((std::string(directory) + '/' + mtlFileName).c_str(), materialN);
				if (Materials == nullptr)
					std::cerr << "Error Load MAterial " << mtlFileName << std::endl;
			}
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
			//std::cout << mtl_name << std::endl;
		}
		else if (c == 's')
		{
			continue;
		}
		else if (c == 'f')
		{
			if (isQuad)
			{
				Quad tQuad;
				quadN++;
				char cc;
				size_t cv, ct, cn;
				sstr >> cv >> cc; if (noTextIndexs_) ct = 1; else sstr >> ct; sstr >> cc >> cn;
				cv--; ct--; cn--;
				tQuad.VertexT[0] = cv; tQuad.NormalT[0] = ct; tQuad.TexturesT[0] = ct;
				sstr >> cv >> cc; if (noTextIndexs_) ct = 1; else sstr >> ct; sstr >> cc >> cn;
				cv--; ct--; cn--;
				tQuad.VertexT[1] = cv; tQuad.NormalT[1] = cn; tQuad.TexturesT[1] = ct;
				sstr >> cv >> cc; if (noTextIndexs_) ct = 1; else sstr >> ct;  sstr >> cc >> cn;
				cv--; ct--; cn--;
				tQuad.VertexT[2] = cv; tQuad.NormalT[2] = cn; tQuad.TexturesT[2] = ct;
				sstr >> cv >> cc; if (noTextIndexs_) ct = 1; else sstr >> ct;  sstr >> cc >> cn;
				cv--; ct--; cn--;
				tQuad.VertexT[3] = cv; tQuad.NormalT[3] = cn; tQuad.TexturesT[3] = ct;
				QuadsL.push_back(tQuad);
			}
			else
			{
				Triangle tTriangle;
				triN++;
				char cc;
				size_t cv, ct, cn;
				sstr >> cv >> cc; if (noTextIndexs_) ct = 1; else sstr >> ct; sstr >> cc >> cn;
				cv--; ct--; cn--;
				tTriangle.VertexT[0] = cv; tTriangle.NormalT[0] = ct; tTriangle.TexturesT[0] = ct;
				sstr >> cv >> cc; if (noTextIndexs_) ct = 1; else sstr >> ct; sstr >> cc >> cn;
				cv--; ct--; cn--;
				tTriangle.VertexT[1] = cv; tTriangle.NormalT[1] = cn; tTriangle.TexturesT[1] = ct;
				sstr >> cv >> cc; if (noTextIndexs_) ct = 1; else sstr >> ct;  sstr >> cc >> cn;
				cv--; ct--; cn--;
				tTriangle.VertexT[2] = cv; tTriangle.NormalT[2] = cn; tTriangle.TexturesT[2] = ct;
				TrianglesL.push_back(tTriangle);
			}
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

	setSizeQuads(quadN);
	for (size_t i = 0; i < quadN; ++i)
	{
		Quads[i] = QuadsL.front();
		QuadsL.pop_front();
	}
	inFile.close();

	std::cout << "Vertexs: " << vertexN << " Normals: " << normalN << " Textures: " << texturesN << " Triangles: " << trianglesN << " Quads: " << quadsN << std::endl;
	return true;

}
bool ModelOBJ::Save(const char* file)
{
	std::ofstream outFile;
	outFile.open(file);
	outFile << "# File Create GEngine - it is modify obj file" << std::endl;
	outFile.close();
	return false;
}
void ModelOBJ::Draw(Render* r)
{
	//r->LoadIdentity();
	r->Translate(pos);
	Color4f color(0.25f, 1.0f, 0.5f, 1.0f);
	if (isQuad)
	{
		for (size_t i = 0; i < quadsN; ++i)
		{
			size_t va = Quads[i].VertexT[0];
			size_t vb = Quads[i].VertexT[1];
			size_t vc = Quads[i].VertexT[2];
			size_t vd = Quads[i].VertexT[3];

			Vector3f a = Vertexs[va];
			Vector3f b = Vertexs[vb];
			Vector3f c = Vertexs[vc];
			Vector3f d = Vertexs[vd];

			size_t naq = Quads[i].NormalT[0];
			size_t nbq = Quads[i].NormalT[1];
			size_t ncq = Quads[i].NormalT[2];
			size_t ndq = Quads[i].NormalT[3];

			Vector3f na = Normals[naq];
			Vector3f nb = Normals[nbq];
			Vector3f nc = Normals[ncq];
			Vector3f nd = Normals[ndq];

			r->drawQuad(a, b, c, d, na, color);
		}
	}
	else
	{
		for (size_t i = 0; i < trianglesN; ++i)
		{
			size_t va = Triangles[i].VertexT[0];
			size_t vb = Triangles[i].VertexT[1];
			size_t vc = Triangles[i].VertexT[2];

			Vector3f a = Vertexs[va];
			Vector3f b = Vertexs[vb];
			Vector3f c = Vertexs[vc];

			size_t naq = Triangles[i].NormalT[0];
			size_t nbq = Triangles[i].NormalT[1];
			size_t ncq = Triangles[i].NormalT[2];

			Vector3f na = Normals[naq];
			Vector3f nb = Normals[nbq];
			Vector3f nc = Normals[ncq];

			r->drawTriangle(a, b, c, na, nb, nc, color);
			//TTTodo
		}
	}
}