#include "FileReader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>



std::string FileReader::ReadFile(const std::string& path)
{
	std::ifstream file;
	file.open(path);

	if(!file.is_open())
	{
		std::cerr << "Could not open the file: " << path << std::endl;
		return "";
	}

	try
	{
		std::ostringstream strStream;
		strStream << file.rdbuf();
		file.close();


		return std::string(strStream.str());
	}
	catch (std::exception e)
	{
		std::cerr << "Could read from the file: " << path << std::endl;
	}
	
	file.close();
	return nullptr;
}

std::string FileReader::OpenFileDialogue()
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

std::string FileReader::OpenSaveFileDialogue()
{


	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);

	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "*.json";
	ofn.nFilterIndex = 1;

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

	if(GetSaveFileNameA(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}

	return "";
}