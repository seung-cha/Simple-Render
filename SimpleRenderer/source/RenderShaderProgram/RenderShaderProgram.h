#pragma once

#include <glad/glad.h>
#include "RenderShader/RenderShader.h"


namespace SimpleRender
{
	class RenderShaderProgram
	{
	public:
		RenderShaderProgram();

		
	private:
		GLuint programID;

	};

}