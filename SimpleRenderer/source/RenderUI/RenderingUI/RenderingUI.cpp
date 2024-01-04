#include "RenderingUI.h"
#include "RenderApplication/RenderApplication.h"
#include "RenderScene/RenderScene.h"


#include "RenderShaderProgram/RenderShaderProgram.h"
#include "RenderDeferredRender/RenderDeferredRender.h"
#include "RenderShaderProgram/ShaderProgramData.h"

#include "RenderObject/RenderObject.h"

#include "misc/cpp/imgui_stdlib.h"
#include <sstream>


SimpleRenderUI::RenderingUI::RenderingUI(SimpleRender::RenderApplication* application, std::string title) :
	RenderUI(title, application)
{

}


void SimpleRenderUI::RenderingUI::UpdateWidget()
{
	ImGui::Begin(title.c_str());

	for(auto item : *application->Scene->DeferredRender->ShaderProgram->UniformData)
	{
		item->DrawUI();

		ImGui::SameLine();

		std::stringstream s;
		s << item->ID;
		ImGui::InputText(item->idstr2.c_str(), &item->name);

		if(ImGui::BeginPopupContextItem())
		{
			if(ImGui::Button("Select Constant"))
			{
				// Let the data pointer point to its value again
				item->ToConstant();

				ImGui::CloseCurrentPopup();

			}

			item->VariablePopup(application->Scene);

			ImGui::EndPopup();
		}


	}

	if(ImGui::Button("Add Uniform Int"))
	{
		application->Scene->DeferredRender->
			ShaderProgram->UniformData->push_back(new SimpleRender::ShaderDataInt(application->Scene->DeferredRender->
				ShaderProgram->UniformData->size()));
	}

	if(ImGui::Button("Add Uniform Float"))
	{
		application->Scene->DeferredRender->
			ShaderProgram->UniformData->push_back(new SimpleRender::ShaderDataFloat(application->Scene->DeferredRender->
				ShaderProgram->UniformData->size()));
	}

	if(ImGui::Button("Add Uniform Vec2"))
	{
		application->Scene->DeferredRender->
			ShaderProgram->UniformData->push_back(new SimpleRender::ShaderDataVec2(application->Scene->DeferredRender->
				ShaderProgram->UniformData->size()));

	}

	if(ImGui::Button("Add Uniform Vec3"))
	{
		application->Scene->DeferredRender->
			ShaderProgram->UniformData->push_back(new SimpleRender::ShaderDataVec3(application->Scene->DeferredRender->
				ShaderProgram->UniformData->size()));

	}


	if(ImGui::Button("Reload Shader"))
	{
		application->Scene->UpdateDeferredRender();
	}

	ImGui::End();

}


void SimpleRenderUI::RenderingUI::ReflectUpdate()
{

}

