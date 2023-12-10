#include "BackgroundUI.h"



using namespace SimpleRenderUI;


BackgroundUI::BackgroundUI(SimpleRender::RenderScene* scene, std::string title) : RenderUI(title, scene)
{
	background = glm::vec3(0.54f, 0.7f, 0.12f);
	colourFlags = 0;

}

void BackgroundUI::UpdateWidget()
{

	ImGui::Begin(title.c_str());
	ImGui::ColorPicker3("Background Colour", &background[0]);
	ImGui::End();
}
