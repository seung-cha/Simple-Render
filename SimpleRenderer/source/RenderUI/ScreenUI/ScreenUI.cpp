#include "ScreenUI.h"
#include <iostream>

#include "RenderScene/RenderScene.h"
#include "RenderApplication/RenderApplication.h"
#include "RenderObject/RenderObject.h"

#include "ImGuizmo.h"

using namespace SimpleRenderUI; 
using namespace std;

ScreenUI::ScreenUI(SimpleRender::RenderApplication* application, std::string title) : RenderUI(title, application), camera(application), DiscreteMouseInput(application)
{

	// Initialise the frame buffer for this viewport
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer); 

	glGenTextures(1, &screenTexture);
	glBindTexture(GL_TEXTURE_2D, screenTexture);


	// Make width/height customisable.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);

	// Make a render buffer
	glGenRenderbuffers(1, &screenRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, screenRenderbuffer);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);


	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, screenRenderbuffer);


	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "Frame buffer is not ready for this viewport!" << endl << endl;
	}

	InitialiseSelectionBuffer();

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


	if(pressed)
	{
		pressed = false;
		if(mousePos[0] >= pos.x && mousePos[1] >= pos.y && mousePos[0] <= windowSize.x && mousePos[1] <=windowSize.y)
		{

				ImVec2 progress = { (mousePos[0] - pos.x) / size.x, (mousePos[1] - pos.y) / size.y};


				std::cout << "T: " << progress.x << ", " << progress.y << std::endl;

				int res[2] = { progress.x * application->Status->FixedWidth, progress.y * application->Status->FixedHeight };
				//std::cout << "Mapped: " << res[0] << ", " << res[1] << std::endl;


				unsigned char col[4];


				glBindFramebuffer(GL_READ_FRAMEBUFFER, selectionBuffer.framebuffer);
				glReadPixels(res[0], application->Status->FixedHeight - res[1], 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &col);
				glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);


				cout << "Pixel data at < " << res[0] << ", " << application->Status->FixedHeight - res[1] << " >:"
					<< static_cast<int>(col[0]) << std::endl;
		}

	}
	



	ImVec2 s = ImGui::GetWindowSize();

	ImGui::Image(ImTextureID(screenTexture), s, { 0, 1 }, {1, 0});
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


void ScreenUI::InitialiseSelectionBuffer()
{
	glGenFramebuffers(1, &selectionBuffer.framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, selectionBuffer.framebuffer);

	glGenTextures(1, &selectionBuffer.renderTexture);
	glBindTexture(GL_TEXTURE_2D, selectionBuffer.renderTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, application->Status->FixedWidth,
		application->Status->FixedHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, selectionBuffer.renderTexture, 0);


	// Gen renderbuffer
	glGenRenderbuffers(1, &selectionBuffer.renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, selectionBuffer.renderbuffer);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, application->Status->FixedWidth, application->Status->FixedHeight);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, selectionBuffer.renderbuffer);


	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "Selection Buffer is not ready for this viewport!" << endl << endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	else
	{
		cout << "Selection Buffer is ready for this viewport!" << endl << endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
	

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

	// Draw the scene first and then ID scene
	application->Scene->DrawScene(&camera, framebuffer);

	application->Scene->DrawIDScene(&camera, selectionBuffer.renderbuffer);

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