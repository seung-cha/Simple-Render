#pragma once

#include <string>
#include <glad/glad.h>
#include "RenderShader/RenderShader.h"


namespace SimpleRender
{
	enum ShaderProgramState
	{
		ShaderProgramNew,
		ShaderProgramLinked,
		ShaderProgramError
	};

	class RenderShaderProgram
	{
	public:

		RenderShaderProgram();

		void AttachShader(RenderShader* shader);

		void LinkProgram();

		inline bool IsShaderAttached(enum ShaderType type)
		{
			return shaders[type];
		}

		inline bool IsShaderAttached(int index)
		{
			return shaders[index];
		}



		inline GLuint ID()
		{
			return programID;
		}

		inline enum ShaderProgramState State()
		{
			return state;
		}
 
		static inline std::string ShaderProgramStateToString(enum ShaderProgramState state)
		{
			if(state == ShaderProgramNew)
				return "New";
			else if(state == ShaderProgramLinked)
				return "Linked";
			else
				return "Error";
		}


		
	private:


		enum ShaderProgramState state = ShaderProgramNew;
		GLuint programID;
		RenderShader* shaders[3] = {nullptr, nullptr, nullptr};

		
	};

}