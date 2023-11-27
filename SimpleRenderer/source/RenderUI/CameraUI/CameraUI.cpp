#include "CameraUI.h"



using namespace SimpleRenderUI;


void CameraUI::UpdateWidget()
{
	ImGui::Begin(title.c_str());

	ImGui::DragFloat("FOV", &fov);

	ImGui::End();

}