#include "FileReader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>


using namespace std; 

const char* FileReader::ReadFile(const char* path)
{
	ifstream file;
	file.open(path);

	if(!file.is_open())
	{
		cerr << "Could not open the file: " << path << endl;
		return nullptr;
	}

	try
	{
		ostringstream strStream;
		strStream << file.rdbuf();
		file.close();


		return _strdup(strStream.str().c_str());
	}
	catch (exception e)
	{
		cerr << "Could read from the file: " << path << endl;
	}
	
	file.close();
	return nullptr;
}

string FileReader::OpenFileDialogue()
{
	// Direct copy from a tutorial by The Cherno
	// https://youtu.be/zn7N7zHgCcs?si=Mf70bKsJdPrk0woi

	// Should come back to understand it later.

	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);

	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "";
	ofn.nFilterIndex = 1;

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if(GetOpenFileNameA(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}

	return "";
}