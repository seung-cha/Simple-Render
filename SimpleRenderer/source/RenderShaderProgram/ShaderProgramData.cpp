#include "RenderShaderProgram/ShaderProgramData.h"
#include "RenderScene/RenderScene.h"
#include "RenderApplication/RenderApplication.h"
#include "RenderObject/RenderObject.h"


void SimpleRender::ShaderDataInt::VariablePopup(RenderScene* scene)
{
	if(ImGui::Button("Run Time"))
	{
		ToVariable(&scene->Application->Status->Timei);
		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Left Click (Continuous)"))
	{
		ToVariable(&scene->Application->Status->Mouse->LeftClick);
		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Right Click (Continuous)"))
	{
		ToVariable(&scene->Application->Status->Mouse->RightClick);
		ImGui::CloseCurrentPopup();
	}

}

void SimpleRender::ShaderDataFloat::VariablePopup(RenderScene* scene)
{
	if(ImGui::Button("Run Time"))
	{
		ToVariable(&scene->Application->Status->Timef);
		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Aspect Ratio"))
	{
		ToVariable(&scene->Application->Status->AspectRatio);
		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Aspect Ratio (Fixed)"))
	{
		ToVariable(&scene->Application->Status->FixedAspectRatio);
		ImGui::CloseCurrentPopup();
	}

}


void SimpleRender::ShaderDataVec2::VariablePopup(RenderScene* scene)
{
	if(ImGui::Button("Resolution"))
	{
		ToVariable(&scene->Application->Status->Resolution);
		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Fixed Resolution"))
	{
		ToVariable(&scene->Application->Status->FixedResolution);
		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Mouse Position"))
	{
		ToVariable(&scene->Application->Status->Mouse->MouseCoordinates);
		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Mouse Delta"))
	{
		ToVariable(&scene->Application->Status->Mouse->MouseDelta);
		ImGui::CloseCurrentPopup();
	}

}


void SimpleRender::ShaderDataVec3::VariablePopup(RenderScene* scene)
{
	if(!scene->ActiveObject)
		return;

	if(ImGui::Button("Active Object Position"))
	{
		ToVariable(&scene->ActiveObject->Transform->Position);
		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Active Object Rotation"))
	{
		ToVariable(&scene->ActiveObject->Transform->Rotation);
		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Active Object Scale"))
	{
		ToVariable(&scene->ActiveObject->Transform->Scale);
		ImGui::CloseCurrentPopup();
	}


}