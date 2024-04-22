#pragma once

#include <stdexcept>
#include <string>


namespace RenderExceptions
{
	class InvalidFile : public std::runtime_error
	{
	public:
		InvalidFile(const std::string& error) : std::runtime_error(error)
		{

		}


	};


}
