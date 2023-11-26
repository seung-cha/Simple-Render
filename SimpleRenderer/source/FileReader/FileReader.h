#pragma once

#include <string>

class FileReader
{
public:
	/// <summary>
	/// Return a string containing the content.
	/// Call free() to disallocate memory.
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	static const char* ReadFile(const char* path);
};