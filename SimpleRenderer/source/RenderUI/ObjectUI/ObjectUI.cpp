#include "ObjectUI.h"
#include <vector>
#include <FileReader/FileReader.h>


using namespace SimpleRenderUI;
using namespace SimpleRender;
using namespace std;


void ObjectUI::UpdateWidget()
{

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



	ImGui::End();
}


void ObjectUI::TransformWidget()
{
	// Render Object Transformation
	ImGui::SeparatorText("Transform");

	ImGui::DragFloat3("Position", &object->Position[0], 0.5f);
	ImGui::DragFloat3("Rotation", &object->Rotation[0], 0.5f);
	ImGui::DragFloat3("Scale", &object->Scale[0], 0.01f);
}

void ObjectUI::TextureWidget()
{
	// Render Texture Transforms
	ImGui::SeparatorText("Textures");

	// Create buttons for each texture
	// ImTextureID is just GLuint that contains texture ID
	TextureTable(TextureType::Diffuse);
	TextureTable(TextureType::Specular);

}



void ObjectUI::TextureTable(enum TextureType type)
{
	vector<RenderTexture*> textures = object->TextureMapOfType(type);

	ImGui::BeginGroup();
	for(RenderTexture* texture : textures)
	{
		if(texture->Status() == TextureStatus::NotReady)
		{
			if(ImGui::Button("NO IMAGE", textureButtonSize))
			{
				selectedTexture = texture;
			}
		}
		else
		{
			if(ImGui::ImageButton((ImTextureID)texture->ID(), textureButtonSize))
			{
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