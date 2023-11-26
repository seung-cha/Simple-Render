#pragma once

#include <glad/glad.h>
#include <string>

namespace SimpleRender
{
	enum ShaderType
	{
		Vertex,
		Fragment,
		Geometry
	};

	enum ShaderState
	{
		New,
		Compiled,
		Error
	};

	class RenderShader
	{


	public:
		RenderShader(enum ShaderType type);
		RenderShader(enum ShaderType type, std::string source);
		bool CompileShader();


	private:
		void CreateShader();

		std::string source = "";
		enum ShaderState state = ShaderState::New;
		enum ShaderType type;
		GLuint shaderID;
	};


}