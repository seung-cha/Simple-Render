#include "BackgroundUI.h"
#include "RenderApplication/RenderApplication.h"
#include "RenderScene/RenderScene.h"
#include "RenderCubemap/RenderCubemap.h"
#include "FileReader/FileReader.h"


using namespace SimpleRenderUI;


BackgroundUI::BackgroundUI(SimpleRender::RenderApplication* application, std::string title) : RenderUI(title, application)
{


}

void BackgroundUI::UpdateWidget()
{

	ImGui::Begin(title.c_str());

	if(ImGui::Button("Change Image Right"))
	{
		application->Scene->Cubemap->SetSide(SimpleRender::CubemapSide::Right, FileReader::OpenFileDialogue());
	}

	if(ImGui::Button("Change Image Left"))
	{
		application->Scene->Cubemap->SetSide(SimpleRender::CubemapSide::Left, FileReader::OpenFileDialogue());
	}

	if(ImGui::Button("Change Image Top"))
	{
		application->Scene->Cubemap->SetSide(SimpleRender::CubemapSide::Top, FileReader::OpenFileDialogue());
	}

	if(ImGui::Button("Change Image Bottom"))
	{
		application->Scene->Cubemap->SetSide(SimpleRender::CubemapSide::Bottom, FileReader::OpenFileDialogue());
	}

	if(ImGui::Button("Change Image Front"))
	{
		application->Scene->Cubemap->SetSide(SimpleRender::CubemapSide::Front, FileReader::OpenFileDialogue());
	}

	if(ImGui::Button("Change Image Back"))
	{
		application->Scene->Cubemap->SetSide(SimpleRender::CubemapSide::Back, FileReader::OpenFileDialogue());
	}


	ImGui::End();
}
