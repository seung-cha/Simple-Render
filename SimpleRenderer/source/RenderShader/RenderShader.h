#pragma once

#include <glad/glad.h>
#include <string>
#include "RenderPure/Disposable.h"
#include <unordered_set>

namespace SimpleRender
{
	class RenderShaderProgram;

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
		~RenderShader();
		bool CompileShader();

		inline ShaderType Type()
		{
			return type;
		}

		inline ShaderState State()
		{
			return state;
		}

		inline GLuint ID()
		{
			return shaderID;
		}

		inline std::string Path()
		{
			return path;
		}

		inline std::string Source()
		{
			return source;
		}

		static inline std::string ShaderTypeToString(enum ShaderType type)
		{
			if(type == Vertex)
				return "Vertex";
			else if(type == Fragment)
				return "Fragment";
			else
				return "Geometry";
		}

		void ShaderSource(std::string path);



		std::unordered_set<RenderShaderProgram*>* const ParentShaderPrograms = &parentShaderPrograms;

	private:
		void CreateShader();
		std::unordered_set<RenderShaderProgram*> parentShaderPrograms;

		std::string source = "";
		std::string path;
		enum ShaderState state = ShaderState::ShaderNew;
		enum ShaderType type;
		GLuint shaderID;
	};


}