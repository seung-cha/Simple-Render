#include "ShaderUI.h"
#include <string>
#include <vector>
#include <sstream>
#include "FileReader/FileReader.h"


using namespace SimpleRenderUI;
using namespace SimpleRender;
using namespace std;

void ShaderUI::UpdateWidget()
{
	ImGui::Begin(title.c_str());

	if(ImGui::IsWindowAppearing())
	{
		scene->ActiveShader = nullptr;
		scene->ActiveShader = nullptr;
	}

	ShaderProgramsWidget();

	ShadersWidget(ShaderType::Vertex);
	ShadersWidget(ShaderType::Fragment);
	ShadersWidget(ShaderType::Geometry);


	if(scene->ActiveShader)
	{
		FocusedShaderDetails();
	}

	if(scene->ActiveShaderProgram)
	{
		FocusedShaderProgramDetails();
	}


	ImGui::End();

}


void ShaderUI::ShadersWidget(enum ShaderType type)
{
	string title = RenderShader::ShaderTypeToString(type);
	vector<RenderShader*>* shaders = scene->GetShadersOfType(type);

	ImGui::SeparatorText(title.c_str());

	for(int i = 0; i < shaders->size(); i++)
	{

		ostringstream s;
		s << title << i;
		if(ImGui::Button(s.str().c_str(), ImVec2(64.0f, 64.0f)))
		{
			if(scene->ActiveShader == (*shaders)[i])
				scene->ActiveShader = nullptr;
			else
				scene->ActiveShader = (*shaders)[i];

			cout << "Pressed" << endl;
		}

		ImGui::SameLine();
	}

	// button to create a new shader
	ostringstream s;
	s << "New " << title;

	if(ImGui::Button(s.str().c_str(), ImVec2(64.0f, 64.0f)))
	{
		vector<RenderShader*>* vec = scene->GetShadersOfType(type);
		vec->push_back(new RenderShader(type));

		std::cout << scene->GetShadersOfType(type)->size() << endl;
	}

}

void ShaderUI::FocusedShaderDetails()
{
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_FrameBg));
	ImGui::BeginChild("ShaderDetails", ImVec2(ImGui::GetContentRegionAvail().x, 320.0f));

	ImGui::Text("Type: ");
	ImGui::SameLine();
	ImGui::Text(RenderShader::ShaderTypeToString(scene->ActiveShader->Type()).c_str());

	ImGui::Text("Path: ");
	ImGui::SameLine();
	ImGui::Text(scene->ActiveShader->Path().c_str());

	ImGui::Text("Source: ");
	ImGui::Text(scene->ActiveShader->Source() ? scene->ActiveShader->Source() : "This shader does not have a source.");

	if(scene->ActiveShader->State() == ShaderState::ShaderNew)
	{
		ImGui::Text("This shader is newly created.");
	}

	else if(scene->ActiveShader->State() == ShaderState::ShaderError)
	{
		ImGui::Text("This shader contains errors.");
	}
	else
	{
		ImGui::Text("This shader is compiled.");
	}

	if(ImGui::Button("Replace source"))
	{
		scene->ActiveShader->ShaderSource(FileReader::OpenFileDialogue());
		scene->ActiveShader->CompileShader();
	}


	ImGui::EndChild();
	ImGui::PopStyleColor();
	
}

void ShaderUI::ShaderProgramsWidget()
{
	ImGui::SeparatorText("Shader Program");

	for(unsigned int i = 0; i < scene->SceneShaderPrograms->size(); i++)
	{
		ostringstream stream;
		stream << "Program" << i;

		if(ImGui::Button(stream.str().c_str(), ImVec2(64.0f, 64.0f)))
		{
			// Deselect if the same item is pressed.
			if(scene->ActiveShaderProgram == (*scene->SceneShaderPrograms)[i])
				scene->ActiveShaderProgram = nullptr;
			else
				scene->ActiveShaderProgram = (*scene->SceneShaderPrograms)[i];
		}

		ImGui::SameLine();
	}

	if(ImGui::Button("New Program", ImVec2(64.0f, 64.0f)))
	{
		vector<RenderShaderProgram*>* vec = scene->SceneShaderPrograms;
		vec->push_back(new RenderShaderProgram());

	}

}

void ShaderUI::FocusedShaderProgramDetails()
{
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_FrameBg));
	ImGui::BeginChild("ShaderProgramDetails", ImVec2(ImGui::GetContentRegionAvail().x, 320.0f));

	string stateStr = RenderShaderProgram::ShaderProgramStateToString(scene->ActiveShaderProgram->State());

	ImGui::Text("State: ");
	ImGui::SameLine();
	ImGui::Text(stateStr.c_str());

	ImGui::SeparatorText("Shader attachment status");

	ImGui::Text("Vertex: ");
	ImGui::SameLine();
	ImGui::Text(scene->ActiveShaderProgram->IsShaderAttached(ShaderType::Vertex) ? "O" : "X");

	ImGui::Text("Fragment: ");
	ImGui::SameLine();
	ImGui::Text(scene->ActiveShaderProgram->IsShaderAttached(ShaderType::Fragment) ? "O" : "X");

	ImGui::Text("Geometry: ");
	ImGui::SameLine();
	ImGui::Text(scene->ActiveShaderProgram->IsShaderAttached(ShaderType::Geometry) ? "O" : "X");

	if(scene->ActiveShader)
	{
		if(ImGui::Button("Replace shader with the selected one"))
		{
			scene->ActiveShaderProgram->AttachShader(scene->ActiveShader);
			scene->ActiveShaderProgram->LinkProgram();
		}
	}

	ImGui::PopStyleColor();
	ImGui::EndChild();
}