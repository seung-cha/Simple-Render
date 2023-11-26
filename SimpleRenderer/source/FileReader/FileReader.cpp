#include "FileReader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std; 

const char* FileReader::ReadFile(const char* path)
{
	ifstream file;
	file.open(path);

	if(!file.is_open())
	{
		cerr << "Could not open the file: " << path << endl;
		return "";
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
	return "";
}