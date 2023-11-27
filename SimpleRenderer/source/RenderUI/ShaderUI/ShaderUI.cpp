#include "ShaderUI.h"
#include <string>
#include <vector>
#include <sstream>


using namespace SimpleRenderUI;
using namespace SimpleRender;
using namespace std;

void ShaderUI::UpdateWidget()
{
	ImGui::Begin(title.c_str());

	if(ImGui::IsWindowAppearing())
	{
		selectedShader = nullptr;
	}

	ShadersWidget(ShaderType::Vertex);
	ShadersWidget(ShaderType::Fragment);
	ShadersWidget(ShaderType::Geometry);


	if(selectedShader)
	{
		FocusedShaderDetails();
	}


	ImGui::End();

}


void ShaderUI::ShadersWidget(enum ShaderType type)
{
	string title = RenderShader::ShaderTypeToString(type);
	vector<RenderShader>* shaders = scene->GetShadersOfType(type);

	ImGui::SeparatorText(title.c_str());

	for(int i = 0; i < shaders->size(); i++)
	{
		ostringstream s;
		s << title << i;
		if(ImGui::Button(s.str().c_str(), ImVec2(64.0f, 64.0f)))
		{
			selectedShader = &((* shaders)[i]);
			cout << "Pressed" << endl;
		}

	}
}

void ShaderUI::FocusedShaderDetails()
{
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_FrameBg));
	ImGui::BeginChild("ShaderDetails", ImVec2(ImGui::GetContentRegionAvail().x, 320.0f));

	ImGui::Text("Type: ");
	ImGui::SameLine();
	ImGui::Text(RenderShader::ShaderTypeToString(selectedShader->Type()).c_str());

	ImGui::Text("Path: ");
	ImGui::SameLine();
	ImGui::Text(selectedShader->Path().c_str());

	ImGui::Text("Source: ");
	ImGui::Text(selectedShader->Source() ? selectedShader->Source() : "This shader does not have a source.");

	if(selectedShader->State() == ShaderState::ShaderNew)
	{
		ImGui::Text("This shader is newly created.");
	}

	else if(selectedShader->State() == ShaderState::ShaderError)
	{
		ImGui::Text("This shader contains errors.");
	}
	else
	{
		ImGui::Text("This shader is compiled.");
	}



	ImGui::EndChild();
	ImGui::PopStyleColor();
	
}