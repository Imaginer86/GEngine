#include <string>
#include <iostream>
#include <fstream>
//#include <sstream>
//#include <list>

#include "FileReader.h"

using namespace std;

/*       Функция для чтения текстового файла в выделенный буфер char       */
/*
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
*/

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