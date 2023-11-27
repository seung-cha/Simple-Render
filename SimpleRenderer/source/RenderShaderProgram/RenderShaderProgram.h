#pragma once

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

		inline GLuint ID()
		{
			return programID;
		}


		
	private:



		GLuint programID;
		RenderShader* shaders[3] = {nullptr, nullptr, nullptr};

		
	};

}