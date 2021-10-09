#pragma once
#include "../Math/Vector3f.h"
#include "../Render/Color4f.h"

#include "../Render/Render.h"


class ModelOBJ
{
public:
	struct Triangle
	{
		size_t	VertexT[3];
		size_t	NormalT[3];
		size_t	TexturesT[3];
	};
public:
	size_t	triangleN;
	Triangle* Triangles;
	size_t	vertexN;
	Vector3f*	Vertexs;
	size_t	normalN;
	Vector3f*	Normals;
	size_t	texturesN;
	Vector3f* Textures;
	



public:
	//ModelOBJ() {}
	ModelOBJ():vertexN(0), Vertexs(nullptr), normalN(0), Normals(nullptr), texturesN(0), Textures(nullptr), triangleN(0), Triangles(nullptr) {}
	~ModelOBJ() { delete[] Normals; delete[] Vertexs; delete[] Textures; delete[] Triangles; }

	// Конструктор копирования, который выполняет глубокое копирование
	ModelOBJ(const ModelOBJ& x)
	{
		// Копируем передаваемый объект
		triangleN = x.triangleN;
		Triangles = new Triangle[triangleN];
		for (size_t i = 0; i < triangleN; ++i)
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
	ModelOBJ& operator=(const ModelOBJ& x)
	{
		// Проверка на самоприсваивание
		if (&x == this)
			return *this;

		// Удаляем всё, что к этому моменту может хранить указатель 
		delete[] Normals; delete[] Vertexs; delete[] Textures; delete[] Triangles;
		
		// Копируем передаваемый объект
		triangleN = x.triangleN;
		Triangles = new Triangle[triangleN];
		for (size_t i = 0; i < triangleN; ++i)
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
	void setSizeVertex(size_t n);
	void setVertex(size_t i, Vector3f v);
	void setSizeNormal(size_t n);
	void setNormal(size_t i, Vector3f n);
	void setSizeTextures(size_t n);
	void setTexture(size_t i, Vector3f n);
	void setSizeTriangles(size_t n);
	//void setSizeQuad(size_t g, size_t s);
	bool Load(const char* fileName, bool twoUV = false, bool noTextIndexs = false);
	bool LoadM(const char* fileName);
	void Draw(Render* r);
};
