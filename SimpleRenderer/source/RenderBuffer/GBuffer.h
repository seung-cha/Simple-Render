#pragma once


#include "RenderBuffer.h"
#include <iostream>



namespace SimpleRenderBuffer
{
	class GBuffer : public RenderBuffer
	{
	public:
		GBuffer(const int& width, const int& height) : RenderBuffer(width, height)
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

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height,
				0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);



			// Generate and bind object + skybox texture
			glGenTextures(1, &objectTexture);
			glBindTexture(GL_TEXTURE_2D, objectTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, objectTexture, 0);



			// Generate and bind tangent texture
			glGenTextures(1, &tangentTexture);
			glBindTexture(GL_TEXTURE_2D, tangentTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, tangentTexture, 0);


			// Generate and bind biTangent map texture
			glGenTextures(1, &biTangentTexture);
			glBindTexture(GL_TEXTURE_2D, biTangentTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, biTangentTexture, 0);


			// Generate and bind normal map texture
			glGenTextures(1, &normalMapTexture);
			glBindTexture(GL_TEXTURE_2D, normalMapTexture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT6, GL_TEXTURE_2D, normalMapTexture, 0);



			glBindTexture(GL_TEXTURE_2D, 0);

			if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
			{
				std::cout << "Frame Buffer is ready for use" << std::endl << std::endl;
			}
			else
			{
				std::cout << "Frame Buffer is NOT ready for use" << std::endl << std::endl;
			}


			GLenum enums[7] = { GL_COLOR_ATTACHMENT0, 
				GL_COLOR_ATTACHMENT1, 
				GL_COLOR_ATTACHMENT2, 
				GL_COLOR_ATTACHMENT3, 
				GL_COLOR_ATTACHMENT4,
				GL_COLOR_ATTACHMENT5,
				GL_COLOR_ATTACHMENT6,
			};

			glDrawBuffers(7, enums);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

		}

		~GBuffer()
		{
			glDeleteTextures(1, &positionTexture);
			glDeleteTextures(1, &normalTexture);
			glDeleteTextures(1, &colourTexture);
			glDeleteTextures(1, &depthTexture);
			glDeleteTextures(1, &tangentTexture);
			glDeleteTextures(1, &biTangentTexture);
			glDeleteTextures(1, &normalMapTexture);
		}


	public:
		const GLuint& PositionTexture = positionTexture;
		const GLuint& NormalTexture = normalTexture;
		const GLuint& ColourTexture = colourTexture;
		const GLuint& DepthTexture = depthTexture;
		const GLuint& ObjectTexture = objectTexture;
		const GLuint& TangentTexture = tangentTexture;
		const GLuint& BiTangentTexture = biTangentTexture;
		const GLuint& NormalMapTexture = normalMapTexture;



	protected:
		GLuint 
			positionTexture, 
			normalTexture, 
			colourTexture, 
			depthTexture, 
			objectTexture, 
			tangentTexture,
			biTangentTexture,
			normalMapTexture;
	};



}