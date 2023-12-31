#include "ScreenUI.h"
#include <iostream>

#include "RenderScene/RenderScene.h"
#include "RenderApplication/RenderApplication.h"
#include "RenderObject/RenderObject.h"

#include "ImGuizmo.h"


// To delete
#include "RenderShader/RenderShader.h"

using namespace SimpleRenderUI; 
using namespace std;

ScreenUI::ScreenUI(SimpleRender::RenderApplication* application, std::string title) :
	RenderUI(title, application), 
	camera(application), 
	DiscreteMouseInput(application), 
	selectionBuffer(application->Status->FixedWidth, application->Status->FixedHeight),
	gBuffer(application->Status->FixedWidth, application->Status->FixedHeight)
{

	// Initialise the frame buffer for this viewport
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer); 

	glGenTextures(1, &screenTexture);
	glBindTexture(GL_TEXTURE_2D, screenTexture);


	// Make width/height customisable.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, application->Status->FixedWidth, application->Status->FixedHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);

	// Make a render buffer
	glGenRenderbuffers(1, &screenRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, screenRenderbuffer);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, application->Status->FixedWidth, application->Status->FixedHeight);


	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, screenRenderbuffer);


	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "Frame buffer is not ready for this viewport!" << endl << endl;
	}


	InitDeferredRender();




}

void ScreenUI::UpdateWidget()
{

	ImGui::Begin(title.c_str(), 0,  ImGuiWindowFlags_NoScrollbar);


	ImVec2 size = ImGui::GetWindowSize();
	ImVec2 pos = ImGui::GetWindowPos();
	

	/*std::cout << "Window Size: " << size.x << ", " << size.y << std::endl;
	std::cout << "Window Pos: " << pos.x << ", " << pos.y << std::endl;
	cout << "Cursor: " << application->Status->Mouse->xPos << ", " << application->Status->Mouse->yPos << std::endl;*/

	int mousePos[2] = {application->Status->Mouse->xPos, application->Status->Mouse->yPos};
	ImVec2 windowSize = { size.x + pos.x, size.y + pos.y };



	// Object selection
	if(pressed)
	{
		pressed = false;
		if(mousePos[0] >= pos.x && mousePos[1] >= pos.y && mousePos[0] <= windowSize.x && mousePos[1] <=windowSize.y && !ImGuizmo::IsOver())
		{

				ImVec2 progress = { (mousePos[0] - pos.x) / size.x, (mousePos[1] - pos.y) / size.y};


				std::cout << "T: " << progress.x << ", " << progress.y << std::endl;

				int res[2] = { progress.x * application->Status->FixedWidth, progress.y * application->Status->FixedHeight };
				//std::cout << "Mapped: " << res[0] << ", " << res[1] << std::endl;


				unsigned char col[4];


				glBindFramebuffer(GL_READ_FRAMEBUFFER, selectionBuffer.Framebuffer);
				glReadPixels(res[0], application->Status->FixedHeight - res[1], 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &col);
				glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);


				cout << "Pixel data at < " << res[0] << ", " << application->Status->FixedHeight - res[1] << " >:"
					<< static_cast<int>(col[0]) << std::endl;

				if(static_cast<int>(col[0]) != 0)
					application->Scene->ActiveObject = (*application->Scene->SceneObjects)[static_cast<int>(col[0] - 1)];
				else
					application->Scene->ActiveObject = nullptr;
		}

	}
	



	ImVec2 s = ImGui::GetWindowSize();

	ImGui::Image(ImTextureID(deferTexture), s, {0, 1}, {1, 0});
	RenderScene();
	RenderGizmo();

	
	ImGui::End();

}
void ScreenUI::ReflectUpdate()
{

	
	/*glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
	unsigned char col[4];

	glReadPixels(application->Status->Mouse->xPos, application->Status->Height - application->Status->Mouse->yPos, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &col);

	cout << "Pixel data at < " << application->Status->Mouse->xPos << ", " << application->Status->Mouse->yPos << " >:"
		<< static_cast<int>(col[0]) << std::endl;

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);*/



}


void SimpleRenderUI::ScreenUI::OnDiscreteMouseInput(GLFWwindow* window, int button, int action, int mods)
{

	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		pressed = true;
	}

}


void ScreenUI::RenderScene()
{

	camera.Active = ImGui::IsWindowFocused();
	camera.Update();

	// Draw the scene first and then ID scene and then G buffer
	application->Scene->DrawScene(&camera, framebuffer);

	application->Scene->DrawIDScene(&camera, selectionBuffer.Framebuffer);

	application->Scene->DrawGBufferScene(&camera, gBuffer.Framebuffer);
	

	DeferredRender();

}

void ScreenUI::RenderGizmo()
{
	ImGuizmo::SetDrawlist();

	ImVec2 s = ImGui::GetWindowSize();
	ImVec2 p = ImGui::GetWindowPos();


	ImGuizmo::SetRect(p.x, p.y, s.x, s.y);

	if(application->Scene->ActiveObject)
	{
		ImGuizmo::Manipulate(&camera.ViewMatrix()[0][0], &camera.PerspectiveMatrix()[0][0],
			ImGuizmo::TRANSLATE, ImGuizmo::LOCAL, &application->Scene->ActiveObject->Matrix[0][0]);
	}

}





void ScreenUI::InitDeferredRender()
{
	SimpleRender::RenderShader vertShader(SimpleRender::ShaderType::Vertex, "shaders/deferred_render/deferred_render.vert");
	SimpleRender::RenderShader fragShader(SimpleRender::ShaderType::Fragment, "shaders/deferred_render/deferred_render.frag");

	deferShaderProgram.AttachShader(&vertShader);
	deferShaderProgram.AttachShader(&fragShader);

	deferShaderProgram.LinkProgram();


	glGenFramebuffers(1, &deferFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, deferFramebuffer);


	glGenTextures(1, &deferTexture);
	glBindTexture(GL_TEXTURE_2D, deferTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, application->Status->FixedWidth,
		application->Status->FixedHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);


	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, deferTexture, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "Defer Buffer is not ready for this viewport!" << endl << endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	else
	{
		cout << "Defer Buffer is ready for this viewport!" << endl << endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}


	float quadVertices[] = {
		// positions        // texture Coords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};

	unsigned int indices[] = { 0, 1, 2, 1, 2, 3 };


	glGenVertexArrays(1, &deferVAO);
	glBindVertexArray(deferVAO);

	GLuint VBO, EBO;

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


	//std::cout << "Error: " << glGetError() << std::endl;
}


void ScreenUI::DeferredRender()
{

	glBindFramebuffer(GL_FRAMEBUFFER, deferFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glDisable(GL_DEPTH_TEST);

	glUseProgram(deferShaderProgram.ID());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gBuffer.PositionTexture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gBuffer.NormalTexture);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gBuffer.ColourTexture);

	glUniform1i(glGetUniformLocation(deferShaderProgram.ID(), "position"), 0);
	glUniform1i(glGetUniformLocation(deferShaderProgram.ID(), "normal"), 1);
	glUniform1i(glGetUniformLocation(deferShaderProgram.ID(), "colour"), 2);

	
	glBindVertexArray(deferVAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_DEPTH_BUFFER_BIT);


	//std::cout << "Error: " << glGetError() << std::endl;

}