#pragma once

#include <string>

class FileReader
{
public:
	/// <summary>
	/// Return the content at the path.
	/// Call free() to disallocate memory. 
	/// Will return nullptr is error occurs.
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	static const char* ReadFile(const char* path);

	static std::string OpenFileDialogue();
	
	

};