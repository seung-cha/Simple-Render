#pragma once

#include <glad/glad.h>
#include <string>

namespace SimpleRender
{
	enum ShaderType
	{
		Vertex,
		Fragment,
		Geometry,
	};

	enum ShaderState
	{
		ShaderNew,
		ShaderCompiled,
		ShaderError
	};

	class RenderShader
	{


	public:
		RenderShader(enum ShaderType type);
		RenderShader(enum ShaderType type, std::string path);
		bool CompileShader();

		inline ShaderType Type()
		{
			return type;
		}

		inline ShaderState State()
		{
			state;
		}

		inline GLuint ID()
		{
			return shaderID;
		}

		inline std::string ShaderTypeToString(enum ShaderType type)
		{
			if(type == Vertex)
				return "Vertex";
			else if(type == Fragment)
				return "Fragment";
			else
				return "Geometry";
		}

		void ShaderSource(std::string path);

	private:
		void CreateShader();


		const char* source = nullptr;
		std::string path;
		enum ShaderState state = ShaderState::ShaderNew;
		enum ShaderType type;
		GLuint shaderID;
	};


}