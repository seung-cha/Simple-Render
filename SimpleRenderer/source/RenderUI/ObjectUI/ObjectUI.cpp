#include "ObjectUI.h"
#include <vector>
#include "FileReader/FileReader.h"

#include "RenderApplication/RenderApplication.h"
#include "RenderScene/RenderScene.h"

#include "ImGuizmo.h"
#include "misc/cpp/imgui_stdlib.h"

using namespace SimpleRenderUI;
using namespace SimpleRender;
using namespace std;

ObjectUI::ObjectUI(SimpleRender::RenderApplication* const& application, const std::string& title): RenderUI(title, application)
{
	selectedTexture = nullptr;
}


// 
//	Add null check later
//
void ObjectUI::UpdateWidget()
{

	if(!application->Scene->ActiveObject)
		return;

	ImGui::Begin(title.c_str());



	if(ImGui::IsWindowAppearing())
	{
		cout << "Object UI focused" << endl;
		selectedTexture = nullptr;
	}


	TransformWidget();
	TextureWidget();

	if(selectedTexture)
	{
		FocusedTextureDetails();
	}

	if(application->Scene->ActiveShaderProgram && application->Scene->ActiveShaderProgram->State() == ShaderProgramState::ShaderProgramLinked)
	{
		if(ImGui::Button("Change Shader Program"))
		{
			application->Scene->ActiveObject->ReplaceShaderProgram(application->Scene->ActiveShaderProgram);
		}
	}

	if(ImGui::Button("DELETE THIS OBJECT"))
	{
		application->Scene->DeleteActiveObject();
	}


	ImGui::End();
}


void ObjectUI::TransformWidget()
{
	
	ImGui::InputText("Name", &application->Scene->ActiveObject->Name);

	// Render Object Transformation
	ImGui::SeparatorText("Transform");


	ImGui::DragFloat3("Position", &application->Scene->ActiveObject->Transform->Position[0], 0.5f);
	ImGui::DragFloat3("Rotation", &application->Scene->ActiveObject->Transform->Rotation[0], 0.5f);
	ImGui::DragFloat3("Scale", &application->Scene->ActiveObject->Transform->Scale[0], 0.01f);
	


}

void ObjectUI::TextureWidget()
{
	// Render Texture Transforms
	ImGui::SeparatorText("Textures");

	// Create buttons for each texture
	// ImTextureID is just GLuint that contains texture ID
	TextureTable(TextureType::Diffuse);
	TextureTable(TextureType::Specular);
	TextureTable(TextureType::Normal);

}



void ObjectUI::TextureTable(enum TextureType type)
{
	vector<RenderTexture*> textures = application->Scene->ActiveObject->TextureMapOfType(type);

	ImGui::BeginGroup();
	for(RenderTexture* texture : textures)
	{
		if(texture->Status() == TextureStatus::NotReady)
		{
			if(ImGui::Button(SimpleRender::RenderTexture::TextureTypeToString(type).c_str(), textureButtonSize))
			{
				if(selectedTexture == texture)
					selectedTexture = nullptr;
				else
					selectedTexture = texture;
			}
		}
		else
		{
			if(ImGui::ImageButton((ImTextureID)texture->ID(), textureButtonSize))
			{
				if(selectedTexture == texture)
					selectedTexture = nullptr;
				else
					selectedTexture = texture;
			}

		}
	}
	ImGui::EndGroup();

}


void ObjectUI::FocusedTextureDetails()
{
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_FrameBg));
	ImGui::BeginChild("TextureDetails", ImVec2(ImGui::GetContentRegionAvail().x, 320.0f));

	ImGui::Image((ImTextureID)selectedTexture->ID(), ImVec2(128, 128));

	ImGui::Text("Path ");
	ImGui::SameLine();
	ImGui::Text(selectedTexture->Path()->c_str());

	if(ImGui::Button("Replace This Texture"))
	{
		selectedTexture->Replace(FileReader::OpenFileDialogue().c_str());
	}


	ImGui::EndChild();
	ImGui::PopStyleColor();

}