#pragma once
#include <string>
#include <iostream>
#include <fstream>

namespace Core
{

	bool LoadRawFile(const char* fileName, char* pHeightMap)
	{
		std::fstream in;
		in.open(fileName, std::ios::in | std::ios::binary | std::ios::ate);

		if (in.is_open())
		{
			std::streampos size = in.tellg();
			in.seekg(0, std::ios::beg);
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