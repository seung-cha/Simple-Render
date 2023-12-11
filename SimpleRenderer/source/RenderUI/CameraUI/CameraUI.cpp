#include "CameraUI.h"

#include "RenderApplication/RenderApplication.h"
#include "RenderScene/RenderScene.h"


using namespace SimpleRenderUI;

CameraUI::CameraUI(SimpleRender::RenderApplication* application, std::string title) : RenderUI(title, application)
{
	this->cam = application->Scene->ActiveCamera;
	fov = cam->FOV();
}

void CameraUI::UpdateWidget()
{
	ImGui::Begin(title.c_str());

	ImGui::DragFloat("FOV", &fov);

	ImGui::End();

}