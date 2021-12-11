#pragma once
#include <string>
#include <iostream>
#include <fstream>

namespace Core
{
	using namespace std;

	bool LoadRawFile(const char* fileName, char* pHeightMap)
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
}