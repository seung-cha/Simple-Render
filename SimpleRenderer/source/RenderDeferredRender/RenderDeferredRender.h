#pragma once

#include <glad/glad.h>

#include "RenderBuffer/GBuffer.h"
#include "RenderBuffer/RenderBuffer.h"

#include "RenderShaderProgram/RenderShaderProgram.h"
#include <memory>


namespace SimpleRender
{

	class RenderCamera;
	class RenderScene;

	/// <summary>
	/// Half-complete deferred Rendering class.
	/// GBuffer needs to be populated with data prior to calling Draw().
	/// </summary>
	class RenderDeferredRender
	{
	public:
		RenderDeferredRender(RenderScene* scene);
		~RenderDeferredRender();
		/// <summary>
		///  Draw the result in DeferBuffer
		/// </summary>
		/// <param name="camera">Camera. Required for its position data.</param>
		void Draw(RenderCamera* const& camera, const GLuint& framebuffer);

	public:

		const std::unique_ptr<SimpleRenderBuffer::GBuffer>& GBuffer = gBuffer;
		const std::unique_ptr<RenderShaderProgram>& ShaderProgram = program;


	private:
		std::unique_ptr<SimpleRenderBuffer::GBuffer> gBuffer;
		std::unique_ptr<RenderShaderProgram> program;

		GLuint VAO, VBO, EBO;

		RenderScene* scene;

	};


}