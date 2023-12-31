#pragma once


#include "RenderBuffer.h"
#include <iostream>

namespace SimpleRenderBuffer
{
	class GBuffer : public RenderBuffer
	{
	public:
		GBuffer(int width, int height) : RenderBuffer(width, height)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);


			// Initialise Position Texture
			glGenTextures(1, &positionTexture);
			glBindTexture(GL_TEXTURE_2D, positionTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 
				width, height, 0, GL_RGBA, GL_FLOAT, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, positionTexture, 0);


			// Initialise Normal Texture
			glGenTextures(1, &normalTexture);
			glBindTexture(GL_TEXTURE_2D, normalTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height,
				0, GL_RGBA, GL_FLOAT, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normalTexture, 0);


			// Generate color + specular texture
			glGenTextures(1, &colourTexture);
			glBindTexture(GL_TEXTURE_2D, colourTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
				0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, colourTexture, 0);



			// Generate and bind depth texture
			glGenTextures(1, &depthTexture);
			glBindTexture(GL_TEXTURE_2D, depthTexture);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height,
				0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);




			glBindTexture(GL_TEXTURE_2D, 0);


			if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
			{
				std::cout << "Frame Buffer is ready for use" << std::endl << std::endl;
			}
			else
			{
				std::cout << "Frame Buffer is NOT ready for use" << std::endl << std::endl;
			}


			GLenum enums[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
			glDrawBuffers(3, enums);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);


		}



	public:
		GLuint& PositionTexture = positionTexture;
		GLuint& NormalTexture = normalTexture;
		GLuint& ColourTexture = colourTexture;
		GLuint& DepthTexture = depthTexture;

	protected:
		GLuint positionTexture, normalTexture, colourTexture, depthTexture;
	};



}