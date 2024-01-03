#pragma once

#include "RenderBuffer.h"
#include <iostream>

namespace SimpleRenderBuffer
{
	class SelectionBuffer : public RenderBuffer
	{
	public:
		SelectionBuffer(int width, int height) : RenderBuffer(width, height)
		{

			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		
			glGenTextures(1, &depthTexture);
			glBindTexture(GL_TEXTURE_2D, depthTexture);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height,
				0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);



			glBindTexture(GL_TEXTURE_2D, 0);

			if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
			{
				std::cout << "Selection Buffer is ready for use" << std::endl << std::endl;
			}
			else
			{
				std::cout << "Selection Buffer is NOT ready for use" << std::endl << std::endl;
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

		}



	public:
		 GLuint& DepthTexture = depthTexture;

		 void Dispose() override
		 {
			 RenderBuffer::Dispose();
			 glDeleteTextures(1, &depthTexture);

		 }

	protected:
		GLuint depthTexture;


	};


}