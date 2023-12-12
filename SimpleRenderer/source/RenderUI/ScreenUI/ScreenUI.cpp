#include "ScreenUI.h"
#include <iostream>

#include "RenderScene/RenderScene.h"
#include "RenderApplication/RenderApplication.h"

using namespace SimpleRenderUI; 
using namespace std;

ScreenUI::ScreenUI(SimpleRender::RenderApplication* application, std::string title) : RenderUI(title, application), camera(application)
{
	// Initialise the frame buffer for this viewport
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer); 

	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);


	// Make width/height customisable.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	// Make a render buffer
	GLuint renderbuffer;
	glGenRenderbuffers(1, &renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);


	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);


	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "Frame buffer is not ready for this viewport!" << endl << endl;
	}


}

void ScreenUI::UpdateWidget()
{

	

	//ImGui::SetNextWindowSize(v->WorkSize);
	//ImGui::SetNextWindowPos(v->WorkPos);

	ImGui::Begin(title.c_str(), 0,  ImGuiWindowFlags_NoScrollbar);

	ImVec2 s = ImGui::GetWindowSize();
	ImGui::Image((ImTextureID)(*application->Scene->SceneTexture), s, { 0, 1 }, {1, 0});
	


	ImGui::End();

}
void ScreenUI::ReflectUpdate()
{

}
