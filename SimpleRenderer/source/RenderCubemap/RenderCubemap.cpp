#include "RenderCubemap.h"
#include <stb_image/stb_image.h>
#include <iostream>
#include "RenderCamera/RenderCamera.h"



SimpleRender::RenderCubemap::RenderCubemap()
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id); 


	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	// Create a cube
    float box[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Create cubemap shaders
	shaderProgram = std::make_unique<SimpleRender::RenderShaderProgram>();

    vert = std::make_unique<SimpleRender::RenderShader>(SimpleRender::ShaderType::Vertex, "shaders/cubemap/cubemap.vert");
    frag = std::make_unique<SimpleRender::RenderShader>(SimpleRender::ShaderType::Fragment, "shaders/cubemap/cubemap.frag");

	shaderProgram->AttachShader(vert.get());
	shaderProgram->AttachShader(frag.get());
	shaderProgram->LinkProgram();

}

SimpleRender::RenderCubemap::~RenderCubemap()
{
    glDeleteTextures(1, &id);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    for(int i = 0; i < 6; i++)
    {
        stbi_image_free(imgData[i]);
    }

}


void SimpleRender::RenderCubemap::SetSide(enum SimpleRender::CubemapSide side, std::string path)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);


    stbi_set_flip_vertically_on_load(false);
	int x, y, channel; 
	unsigned char* data = stbi_load(path.c_str(), &x, &y, &channel, 0);

	if(data)
	{
	    // Free the image previously allocated. Valid since freeing a nullptr does nothing.
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + side, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        int a;
        if(a = glGetError() != 0)
        {
            std::cout << "Unable to change the cubemap image. Verify that the height and width of the image are equal." << std::endl;
            std::cout << "Error code: " << a << std::endl << std::endl;
            stbi_image_free(data);
        }
        else
        {
	        stbi_image_free(imgData[side]);
		    imgData[side] = data;
        }

	}
	else
	{
		std::cout << "Unable to load image for cubemap" << std::endl << std::endl;
		stbi_image_free(data);
	}


	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void SimpleRender::RenderCubemap::Draw(RenderCamera* camera)
{
    glDepthMask(GL_FALSE);

    glUseProgram(shaderProgram->ID());

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.View"), 1,
        GL_FALSE, &camera->ViewMatrix()[0][0]);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID(), "transform.Perspective"), 1,
        GL_FALSE, &camera->PerspectiveMatrix()[0][0]);

    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDepthMask(GL_TRUE);


    // Unbind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}