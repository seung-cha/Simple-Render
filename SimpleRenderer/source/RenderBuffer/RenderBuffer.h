#pragma once

#include <glad/glad.h>
#include "RenderPure/Disposable.h"


namespace SimpleRenderBuffer
{



	class RenderBuffer
	{

	public:
		/// <summary>
		/// Create a framebuffer and texture of provided size.
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		RenderBuffer(const int& width, const int& height)
		{
			glGenFramebuffers(1, &framebuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
				0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

			glBindTexture(GL_TEXTURE_2D, 0);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);



		}

		virtual ~RenderBuffer()
		{
			glDeleteFramebuffers(1, &framebuffer);
			glDeleteFramebuffers(1, &texture);
		}


	public:
		 const GLuint& Framebuffer = framebuffer;
		 const GLuint& Texture = texture;

	public:


	protected:
		GLuint framebuffer, texture;
	};

	/// <summary>
	/// Buffer class for deferred rendering.
	/// it is just a typedef for RenderBuffer class.
	/// </summary>
	using DeferBuffer = RenderBuffer;

}