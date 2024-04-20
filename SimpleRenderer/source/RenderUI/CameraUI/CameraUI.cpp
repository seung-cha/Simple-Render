#include "CameraUI.h"

#include "RenderApplication/RenderApplication.h"
#include "RenderScene/RenderScene.h"


using namespace SimpleRenderUI;

CameraUI::CameraUI(SimpleRender::RenderApplication* const& application, const std::string& title) : RenderUI(title, application)
{

}

void CameraUI::UpdateWidget()
{
	ImGui::Begin(title.c_str());



	ImGui::End();

}