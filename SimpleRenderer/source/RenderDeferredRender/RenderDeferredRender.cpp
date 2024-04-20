#include "RenderDeferredRender.h"
#include "RenderCamera/RenderCamera.h"

#include "RenderScene/RenderScene.h"
#include "RenderApplication/RenderApplication.h"


SimpleRender::RenderDeferredRender::RenderDeferredRender(RenderScene* scene)
{
	this->scene = scene;

	program = std::make_unique<SimpleRender::RenderShaderProgram>();

	program->AttachShader(new SimpleRender::RenderShader(SimpleRender::ShaderType::Vertex, "shaders/deferred_render/deferred_render.vert"));
	program->AttachShader(new SimpleRender::RenderShader(SimpleRender::ShaderType::Fragment, "shaders/deferred_render/deferred_render.frag"));

	program->LinkProgram();


	gBuffer = std::make_unique<SimpleRenderBuffer::GBuffer>(scene->Application->Status->FixedWidth, scene->Application->Status->FixedHeight);


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

SimpleRender::RenderDeferredRender::~RenderDeferredRender()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


void SimpleRender::RenderDeferredRender::Draw(SimpleRender::RenderCamera* const& camera, const GLuint& framebuffer)
{
	scene->DrawGBufferScene(camera, gBuffer->Framebuffer);
	
	program->ApplyUniformVariables();

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program->ID());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gBuffer->PositionTexture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gBuffer->NormalTexture);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gBuffer->ColourTexture);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, gBuffer->ObjectTexture);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, gBuffer->TangentTexture);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, gBuffer->BiTangentTexture);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, gBuffer->NormalMapTexture);

	glUniform1i(glGetUniformLocation(program->ID(), "Rendering.Position"), 0);
	glUniform1i(glGetUniformLocation(program->ID(), "Rendering.Normal"), 1);
	glUniform1i(glGetUniformLocation(program->ID(), "Rendering.Colour"), 2);
	glUniform1i(glGetUniformLocation(program->ID(), "Rendering.Object"), 3);
	glUniform1i(glGetUniformLocation(program->ID(), "Rendering.Tangent"), 4);
	glUniform1i(glGetUniformLocation(program->ID(), "Rendering.BiTangent"), 5);
	glUniform1i(glGetUniformLocation(program->ID(), "Rendering.NormalMap"), 6);




	glUniform3fv(glGetUniformLocation(program->ID(), "Rendering.ViewPosition"), 1, &camera->Position()[0]);


	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}