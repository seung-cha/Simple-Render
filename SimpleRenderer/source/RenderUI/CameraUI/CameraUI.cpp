#include "CameraUI.h"



using namespace SimpleRenderUI;

CameraUI::CameraUI(SimpleRender::RenderScene* scene, std::string title) : RenderUI(title, scene)
{
	this->cam = scene->ActiveCamera;
	fov = cam->FOV();
}

void CameraUI::UpdateWidget()
{
	ImGui::Begin(title.c_str());

	ImGui::DragFloat("FOV", &fov);

	ImGui::End();

}