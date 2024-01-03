#pragma once

#include <glad/glad.h>

#include "RenderBuffer/GBuffer.h"
#include "RenderBuffer/RenderBuffer.h"

#include "RenderShaderProgram/RenderShaderProgram.h"

#include "RenderPure/Disposable.h"

namespace SimpleRender
{

	class RenderCamera;
	class RenderScene;

	/// <summary>
	/// Half-complete deferred Rendering class.
	/// GBuffer needs to be populated with data prior to calling Draw().
	/// </summary>
	class RenderDeferredRender : public SimpleRenderPure::Disposable
	{
	public:
		RenderDeferredRender(RenderScene* scene);
		/// <summary>
		///  Draw the result in DeferBuffer
		/// </summary>
		/// <param name="camera">Camera. Required for its position data.</param>
		void Draw(RenderCamera* camera, GLuint& framebuffer);

	public:
		SimpleRenderBuffer::GBuffer* GBuffer = &gBuffer;


		void Dispose()
		{
			program.Dispose();
			gBuffer.Dispose();
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);

		}


		RenderShaderProgram* ShaderProgram = &program;


	private:
		SimpleRenderBuffer::GBuffer gBuffer;

		GLuint VAO, VBO, EBO;
		RenderShaderProgram program;

		RenderScene* scene;

	};


}