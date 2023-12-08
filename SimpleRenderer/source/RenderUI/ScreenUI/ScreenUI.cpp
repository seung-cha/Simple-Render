#include "ScreenUI.h"

using namespace SimpleRenderUI; 

ScreenUI::ScreenUI(std::string title, SimpleRender::RenderScene* scene) : RenderUI(title, scene)
{
}

void ScreenUI::UpdateWidget()
{

	

	//ImGui::SetNextWindowSize(v->WorkSize);
	//ImGui::SetNextWindowPos(v->WorkPos);

	ImGui::Begin(title.c_str(), 0,  ImGuiWindowFlags_NoScrollbar);


	ImVec2 s = ImGui::GetWindowSize();
	ImGui::Image((ImTextureID)(*scene->SceneTexture), s, { 0, 1 }, {1, 0});
	


	ImGui::End();

}
void ScreenUI::ReflectUpdate()
{

}
