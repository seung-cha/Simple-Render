#include "ScreenUI.h"

using namespace SimpleRenderUI; 

ScreenUI::ScreenUI(std::string title, SimpleRender::RenderScene* scene) : RenderUI(title, scene)
{
}

void ScreenUI::UpdateWidget()
{
	ImGui::Begin(title.c_str());


	ImGui::Image((ImTextureID)(*scene->SceneTexture), ImVec2(*scene->Width, *scene->Height), { 0, 1 }, {1, 0});

	ImGui::End();

}
void ScreenUI::ReflectUpdate()
{

}
