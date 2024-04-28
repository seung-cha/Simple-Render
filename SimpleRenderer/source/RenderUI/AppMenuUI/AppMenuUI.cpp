#include "AppMenuUI.h"
#include "RenderApplication/RenderApplication.h"
#include "FileReader/FileReader.h"
#include <imgui.h>

using namespace SimpleRenderUI;

AppMenuUI::AppMenuUI(SimpleRender::RenderApplication* const& application, const std::string& title) : RenderUI(title, application)
{
}


void AppMenuUI::UpdateWidget()
{
	if(ImGui::BeginMainMenuBar())
	{
		if(ImGui::BeginMenu("Project"))
		{

			ShowMenuWidget();

			ImGui::EndMenu();
		}



		ImGui::EndMainMenuBar();
	}


}


void AppMenuUI::ShowMenuWidget()
{
	if(application->Status->SaveFile.size() == 0)
	{
		ImGui::Text("Save File not Targeted!");
	}
	else
	{
		ImGui::Text("Save File Targeted!");
	}


	if(ImGui::Button("Save Project"))
	{
		application->SaveScene();

		ImGui::CloseCurrentPopup();
	}


	if(ImGui::Button("Save Project As"))
	{
		application->SaveSceneAs();
		ImGui::CloseCurrentPopup();
	}


	if(ImGui::Button("Load Project"))
	{
		application->LoadScene();

		ImGui::CloseCurrentPopup();
	}

}
