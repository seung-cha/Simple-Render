#pragma once

#include <glad/glad.h>

#include "RenderBuffer/GBuffer.h"
#include "RenderBuffer/RenderBuffer.h"

#include "RenderShaderProgram/RenderShaderProgram.h"

namespace SimpleRender
{
	/// <summary>
	/// Half-complete deferred Rendering class.
	/// GBuffer needs to be populated with data prior to calling Draw().
	/// </summary>
	class RenderDeferredRender
	{
	public:
		RenderDeferredRender(int width, int height);
		/// <summary>
		/// Draw the result in DeferBuffer
		/// </summary>
		void Draw();

	public:
		SimpleRenderBuffer::DeferBuffer& DeferBuffer = deferBuffer;
		SimpleRenderBuffer::GBuffer& GBuffer = gBuffer;


	private:
		SimpleRenderBuffer::DeferBuffer deferBuffer;
		SimpleRenderBuffer::GBuffer gBuffer;

		GLuint VAO, VBO, EBO;
		RenderShaderProgram program;

	};


}