#include <string>
#include <iostream>
#include <fstream>
//#include <sstream>
//#include <list>

#include "FileReader.h"
#include "../Render/ModelM.h"

using namespace std;

/*       Функция для чтения текстового файла в выделенный буфер char       */
char* filetobuf(char *file)
{
	char* buf = nullptr;
	std::fstream inFile;
	inFile.open(file, std::ios::binary);
	if (inFile.is_open())
	{
		inFile.seekg(0, inFile.end);
		size_t n = inFile.tellg();
		buf = new char[n + 1];
		inFile.seekg(0, inFile.beg);
		inFile.read(buf, n);
		buf[n] = '\n';
		inFile.close();
	}
	return buf;
}

bool LoadRawFile(const char * fileName, unsigned char * pHeightMap)
{
	fstream in;
	in.open(fileName, ios::in | ios::binary | ios::ate);

	if (in.is_open())
	{
		streampos size = in.tellg();
		in.seekg(0, ios::beg);
		in.read(reinterpret_cast<char*>(pHeightMap), size);
	}
	else
	{
		std::cerr << "Can't Find The Height Map!" << std::endl; //MessageBox(NULL, "Can't Find The Height Map!", "Error", MB_OK);
		return false;
	}

	if (in.eof())
	{
		std::cerr << "Failed To Get Data!" << std::endl;// MessageBox(NULL, "Failed To Get Data!", "Error", MB_OK);
		return false;
	}
	in.close();
	return true;
}

bool ReadModelOBJM(ModelM & model, const char * fileName)
{

	ifstream inFile;
	inFile.open(fileName, ios::in);

	if (!inFile.is_open()) return false;

	unsigned vertN;
	inFile >> vertN;

	model.setSizeVertex(vertN);

	for (unsigned i = 0; i < vertN; ++i)
	{
		Vector3f v;
		inFile >> v.x >> v.y >> v.z;
		model.setVertex(i, v);

	}

	unsigned normN;
	inFile >> normN;

	model.setSizeNormal(normN);

	for (unsigned i = 0; i < normN; ++i)
	{
		Vector3f n;
		inFile >> n.x >> n.y >> n.z;
		model.setNormal(i, n);
	}

	unsigned groupN;
	inFile >> groupN;

	model.setSizeGroup(groupN);

	for (unsigned i = 0; i < groupN; ++i)
	{
		char c;
		string gName;
		inFile >> c >> gName;

		unsigned surfN = 0;
		inFile >> surfN;
		model.setSizeSurface(i, surfN);

		inFile >> model.Groups[i].color.r >> model.Groups[i].color.g >> model.Groups[i].color.b >> model.Groups[i].color.a;

		for (unsigned j = 0; j < surfN; ++j)
		{
			unsigned nv, nt, nn;
			inFile >> nv >> nt >> nn;
			nv--;	nt--;	nn--;
			model.Groups[i].Surfaces[j].VertexT[0] = nv;
			model.Groups[i].Surfaces[j].NormalT[0] = nn;
			inFile >> nv >> nt >> nn;
			nv--;	nt--;	nn--;
			model.Groups[i].Surfaces[j].VertexT[1] = nv;
			model.Groups[i].Surfaces[j].NormalT[1] = nn;
			inFile >> nv >> nt >> nn;
			nv--;	nt--;	nn--;
			model.Groups[i].Surfaces[j].VertexT[2] = nv;
			model.Groups[i].Surfaces[j].NormalT[2] = nn;
		}
	}
	inFile.close();
	return true;
}

/*
void FileReader::ReadModelOBJ(Model &model, const char *fileName)
{
	std::list<Vector3f> lVertexs;
	std::list<Vector3f> lNormals;
	std::list<Group> lGroups;
	std::list<Surface> lSurface;


	ifstream infile;
	infile.open(fileName, ios::in);

	if (!infile) return;

	bool bSurface = false;
	bool bf = false;
	while (!infile.eof())
	{
		string line;
		getline(infile, line);
		stringstream sstr;
		sstr << line;
		std::string str;
		char c;
		sstr >> c;
		switch (c)
		{
		case '#':
		{
			if (bf) { bf = false;  bSurface = true; }
			Group group;
			lGroups.push_back(group);
			break;
		}
		case 'm':
		{
			sstr >> str;
			if (str == "tllib")
			{
				sstr >> str;
			}
			break;
		}
		case 'v':
		{
			char ch = static_cast<char>(sstr.peek());
			if (ch == 'n')
			{
				sstr >> ch;
				Vector3f n;
				sstr >> n.x >> n.y >> n.z;
				lNormals.push_back(n);
			}
			else if (ch == 't')
			{
				float x, y;
				sstr >> x >> y;
			}
			else
			{
				Vector3f v;
				sstr >> v.x >> v.y >> v.z;
				lVertexs.push_back(v);
			}
			break;
		}
		case 'g':
		{
			if (bf) { bf = false;  bSurface = true; }
			Group group;
			sstr >> group.name;
			lGroups.push_back(group);
			break;
		}
		case 'o':
		{
			if (bf) { bf = false;  bSurface = true; }
			Group group;
			sstr >> group.name;
			lGroups.push_back(group);
			break;
		}
		case 'u':
		{
			sstr >> str;
			if (str == "semtl")
			{

			}
			break;
		}
		case 's':
		{
			break;
		}
		case 'f':
		{
			bf = true;
			Surface surface;
			list<size_t> vert;
			list<size_t> norm;
			unsigned v, t, n;
			char ch;
			bool finish = false;
			while (!finish && !sstr.eof())
			{
				finish = false;
				sstr >> v;
				if (sstr.eof()) { finish = true; continue; }
				sstr >> ch;
				if (sstr.eof()) { finish = true; continue; }
				sstr >> t;
				if (sstr.eof()) { finish = true; continue; }
				sstr >> ch;
				if (sstr.eof()) { finish = true; continue; }
				sstr >> n;
				--v; --n;
				vert.push_back(static_cast<size_t>(v));
				norm.push_back(static_cast<size_t>(n));
			}
			surface.n = vert.size();
			if (surface.n == 5)
			{
				int tt = 0;
			}
			surface.Vertexs = new size_t[surface.n];
			surface.Normals = new size_t[surface.n];

			size_t i = 0;
			for (std::list<size_t>::iterator it = vert.begin(); it != vert.end(); ++it)
			{
				surface.Vertexs[i] = *it;
				++i;
			}

			i = 0;
			for (std::list<size_t>::iterator it = norm.begin(); it != norm.end(); ++it)
			{
				surface.Normals[i] = *it;
				++i;
			}

			lSurface.push_back(surface);

			break;
		}
		default:
		{

		}
		}

		if (!lGroups.empty())
		{
			Group groupEnd;
			groupEnd = lGroups.back();
			lGroups.pop_back();

			if (bSurface && !lSurface.empty())
			{
				bSurface = false;


				Group group;
				group = lGroups.back();
				lGroups.pop_back();
				group.size = lSurface.size();
				group.surfaces = new Surface[group.size];

				size_t i = 0;

				for (std::list<Surface>::iterator it = lSurface.begin(); it != lSurface.end(); ++it, ++i)
				{
					//group.surfaces[i].n = *it.n;
					group.surfaces[i] = *it;
				}
				lGroups.push_back(group);
				lSurface.clear();
			}

			lGroups.push_back(groupEnd);
		}
	}

	infile.close();
	lGroups.pop_back();

	size_t n = lVertexs.size();
	model.setSizeVertex(n);

	size_t i = 0;
	for (std::list<Vector3f>::iterator it = lVertexs.begin(); it != lVertexs.end(); ++it, ++i)
	{
		model.vertexs[i] = *it;
	}
	lVertexs.clear();

	model.setSizeNormal(n);
	i = 0;
	for (std::list<Vector3f>::iterator it = lNormals.begin(); it != lNormals.end(); ++it, ++i)
	{
		model.normals[i] = *it;
	}
	lNormals.clear();

	n = lGroups.size();
	model.setSizeGroup(n);
	i = 0;
	for (std::list<Group>::iterator it = lGroups.begin(); it != lGroups.end(); ++it, ++i)
	{
		model.groups[i] = *it;
	}
	lGroups.clear();

}
*/