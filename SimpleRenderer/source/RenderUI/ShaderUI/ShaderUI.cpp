#include "ShaderUI.h"
#include <string>
#include <vector>
#include <sstream>
#include "FileReader/FileReader.h"

#include "RenderApplication/RenderApplication.h"
#include "RenderScene/RenderScene.h"

using namespace SimpleRenderUI;
using namespace SimpleRender;
using namespace std;


ShaderUI::ShaderUI(SimpleRender::RenderApplication* const& application, const std::string& title) : RenderUI(title, application)
{

}

void ShaderUI::UpdateWidget()
{
	ImGui::Begin(title.c_str());

	if(ImGui::IsWindowAppearing())
	{
		application->Scene->ActiveShader = nullptr;
	}

	ShaderProgramsWidget();

	ShadersWidget(ShaderType::Vertex);
	ShadersWidget(ShaderType::Fragment);
	ShadersWidget(ShaderType::Geometry);


	if(application->Scene->ActiveShader)
	{
		FocusedShaderDetails();
	}

	if(application->Scene->ActiveShaderProgram)
	{
		FocusedShaderProgramDetails();
	}


	ImGui::End();

}


void ShaderUI::ShadersWidget(enum ShaderType type)
{
	//string title = RenderShader::ShaderTypeToString(type);
	////vector<RenderShader*>* shaders = application->Scene->GetShadersOfType(type);

	//ImGui::SeparatorText(title.c_str());

	//for(int i = 0; i < shaders->size(); i++)
	//{

	//	ostringstream s;
	//	s << title << i;
	//	if(ImGui::Button(s.str().c_str(), ImVec2(64.0f, 64.0f)))
	//	{
	//		if(application->Scene->ActiveShader == (*shaders)[i])
	//			application->Scene->ActiveShader = nullptr;
	//		else
	//			application->Scene->ActiveShader = (*shaders)[i];

	//		cout << "Pressed" << endl;
	//	}

	//	ImGui::SameLine();
	//}

	//// button to create a new shader
	//ostringstream s;
	//s << "New " << title;

	//if(ImGui::Button(s.str().c_str(), ImVec2(64.0f, 64.0f)))
	//{
	//	//vector<RenderShader*>* vec = application->Scene->GetShadersOfType(type);
	//	//vec->push_back(new RenderShader(type));

	//	//std::cout << application->Scene->GetShadersOfType(type)->size() << endl;
	//}

}

void ShaderUI::FocusedShaderDetails()
{
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_FrameBg));
	ImGui::BeginChild("ShaderDetails", ImVec2(ImGui::GetContentRegionAvail().x, 320.0f));

	ImGui::Text("Type: ");
	ImGui::SameLine();
	ImGui::Text(RenderShader::ShaderTypeToString(application->Scene->ActiveShader->Type()).c_str());

	ImGui::Text("Path: ");
	ImGui::SameLine();
	ImGui::Text(application->Scene->ActiveShader->Path().c_str());

	ImGui::Text("Source: ");
	ImGui::Text(application->Scene->ActiveShader->Source() != "" ? application->Scene->ActiveShader->Source().c_str() : "This shader does not have a source.");

	if(application->Scene->ActiveShader->State() == ShaderState::ShaderNew)
	{
		ImGui::Text("This shader is newly created.");
	}

	else if(application->Scene->ActiveShader->State() == ShaderState::ShaderError)
	{
		ImGui::Text("This shader contains errors.");
	}
	else
	{
		ImGui::Text("This shader is compiled.");
	}

	if(ImGui::Button("Replace source"))
	{
		application->Scene->ActiveShader->ShaderSource(FileReader::OpenFileDialogue());
		application->Scene->ActiveShader->CompileShader();
	}

	if(ImGui::Button("DELETE THIS SHADER"))
	{
		auto shaders = application->Scene->GetShadersOfType(application->Scene->ActiveShader->Type());
		for(unsigned int i = 0; i < shaders->size(); i++)
		{
			if(application->Scene->ActiveShader == (*shaders)[i].get())
			{
				shaders->erase(shaders->begin() + i);
				break;
			}
		}


		delete application->Scene->ActiveShader;
		application->Scene->ActiveShader = nullptr;
	}


	ImGui::EndChild();
	ImGui::PopStyleColor();
	
}

void ShaderUI::ShaderProgramsWidget()
{
	ImGui::SeparatorText("Shader Program");

	//for(unsigned int i = 0; i < application->Scene->SceneShaderPrograms->size(); i++)
	//{
	//	ostringstream stream;
	//	stream << "Program" << i;

	//	if(ImGui::Button(stream.str().c_str(), ImVec2(64.0f, 64.0f)))
	//	{
	//		// Deselect if the same item is pressed.
	//		if(application->Scene->ActiveShaderProgram == (*application->Scene->SceneShaderPrograms)[i].get())
	//			application->Scene->ActiveShaderProgram = nullptr;
	//		else
	//			application->Scene->ActiveShaderProgram = (*application->Scene->SceneShaderPrograms)[i];
	//	}

	//	ImGui::SameLine();
	//}

	//if(ImGui::Button("New Program", ImVec2(64.0f, 64.0f)))
	//{
	//	printf("ShaderUI NewProgram button clicked. Implement this functionality after refactoring code\n");
	//	//vector<RenderShaderProgram*>* vec = application->Scene->SceneShaderPrograms;
	//	//vec->push_back(new RenderShaderProgram());

	//}

}

void ShaderUI::FocusedShaderProgramDetails()
{
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_FrameBg));
	ImGui::BeginChild("ShaderProgramDetails", ImVec2(ImGui::GetContentRegionAvail().x, 320.0f));

	string stateStr = RenderShaderProgram::ShaderProgramStateToString(application->Scene->ActiveShaderProgram->State());

	ImGui::Text("State: ");
	ImGui::SameLine();
	ImGui::Text(stateStr.c_str());

	ImGui::SeparatorText("Shader attachment status");

	ImGui::Text("Vertex: ");
	ImGui::SameLine();
	ImGui::Text(application->Scene->ActiveShaderProgram->IsShaderAttached(ShaderType::Vertex) ? "O" : "X");

	ImGui::Text("Fragment: ");
	ImGui::SameLine();
	ImGui::Text(application->Scene->ActiveShaderProgram->IsShaderAttached(ShaderType::Fragment) ? "O" : "X");

	ImGui::Text("Geometry: ");
	ImGui::SameLine();
	ImGui::Text(application->Scene->ActiveShaderProgram->IsShaderAttached(ShaderType::Geometry) ? "O" : "X");

	if(application->Scene->ActiveShader)
	{
		if(ImGui::Button("Replace shader with the selected one"))
		{
			application->Scene->ActiveShaderProgram->AttachShader(application->Scene->ActiveShader);
			application->Scene->ActiveShaderProgram->LinkProgram();
		}
	}

	if(ImGui::Button("DELETE THIS PROGRAM"))
	{

		for(unsigned int i = 0; i < application->Scene->SceneShaderPrograms->size(); i++)
		{
			if(application->Scene->ActiveShaderProgram == (*application->Scene->SceneShaderPrograms)[i].get())
			{
				application->Scene->SceneShaderPrograms->erase(application->Scene->SceneShaderPrograms->begin() + i);
				break;
			}
		}


		delete application->Scene->ActiveShaderProgram;
		application->Scene->ActiveShaderProgram = nullptr;
	}

	ImGui::PopStyleColor();
	ImGui::EndChild();
}