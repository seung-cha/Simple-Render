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

}

void SimpleRender::ShaderDataFloat::VariablePopup(RenderScene* scene)
{
	if(ImGui::Button("Run Time"))
	{
		ToVariable(&scene->Application->Status->Timef);
		ImGui::CloseCurrentPopup();
	}

}


void SimpleRender::ShaderDataVec2::VariablePopup(RenderScene* scene)
{


}


void SimpleRender::ShaderDataVec3::VariablePopup(RenderScene* scene)
{
	if(!scene->ActiveObject)
		return;

	if(ImGui::Button("Active Object Position"))
	{
		ToVariable(&scene->ActiveObject->Position);
		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Active Object Rotation"))
	{
		ToVariable(&scene->ActiveObject->Rotation);
		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Active Object Scale"))
	{
		ToVariable(&scene->ActiveObject->Scale);
		ImGui::CloseCurrentPopup();
	}


}