#include "RenderDeferredRender.h"



SimpleRender::RenderDeferredRender::RenderDeferredRender(int width, int height) :
	deferBuffer(width, height),
	gBuffer(width, height)
{

	SimpleRender::RenderShader vertShader(SimpleRender::ShaderType::Vertex, "shaders/deferred_render/deferred_render.vert");
	SimpleRender::RenderShader fragShader(SimpleRender::ShaderType::Fragment, "shaders/deferred_render/deferred_render.frag");

	program.AttachShader(&vertShader);
	program.AttachShader(&fragShader);

	program.LinkProgram();



	float quadVertices[] = {
		// positions        // texture Coords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};

	unsigned int indices[] = { 0, 1, 2, 1, 2, 3 };


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	// USE EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void SimpleRender::RenderDeferredRender::Draw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, deferBuffer.Framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program.ID());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gBuffer.PositionTexture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gBuffer.NormalTexture);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gBuffer.ColourTexture);

	glUniform1i(glGetUniformLocation(program.ID(), "position"), 0);
	glUniform1i(glGetUniformLocation(program.ID(), "normal"), 1);
	glUniform1i(glGetUniformLocation(program.ID(), "colour"), 2);


	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}