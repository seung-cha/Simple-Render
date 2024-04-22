#include "RenderingUI.h"
#include "RenderApplication/RenderApplication.h"
#include "RenderScene/RenderScene.h"


#include "RenderShaderProgram/RenderShaderProgram.h"
#include "RenderDeferredRender/RenderDeferredRender.h"
#include "RenderShaderProgram/ShaderProgramData.h"

#include "RenderObject/RenderObject.h"

#include "misc/cpp/imgui_stdlib.h"
#include <sstream>


SimpleRenderUI::RenderingUI::RenderingUI(SimpleRender::RenderApplication* const& application, const std::string& title) :
	RenderUI(title, application)
{

}


void SimpleRenderUI::RenderingUI::UpdateWidget()
{
	ImGui::Begin(title.c_str());


	int removeIndex = -1;		// Specify the index of the variable to remove
	for(int i = 0; i < application->Scene->DeferredRender->ShaderProgram->UniformData->size(); i++)
	{
		auto item = (*application->Scene->DeferredRender->ShaderProgram->UniformData)[i];
		ImGui::PushID(i);



		item->DrawUI();
		ImGui::SameLine();
		ImGui::InputText("Name", &item->name);



		if(ImGui::BeginPopupContextItem())
		{
			if(ImGui::Button("Select Constant"))
			{
				// Let the data pointer point to its value again
				item->ToConstant();
				ImGui::CloseCurrentPopup();

			}


			item->VariablePopup(application->Scene);


			if(ImGui::Button("Delete This Variable"))
			{
				removeIndex = i;
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}


		ImGui::PopID();
	}

	// Delete the object
	if(removeIndex >= 0)
	{
		delete (*application->Scene->DeferredRender->ShaderProgram->UniformData)[removeIndex];
		application->Scene->DeferredRender->ShaderProgram->UniformData->erase
		(application->Scene->DeferredRender->ShaderProgram->UniformData->begin() + removeIndex);

	}
	


	if(ImGui::Button("Add Uniform Int"))
	{
		application->Scene->DeferredRender->ShaderProgram->AddUniformData(new SimpleRender::ShaderDataInt());
	}

	if(ImGui::Button("Add Uniform Float"))
	{
		application->Scene->DeferredRender->ShaderProgram->AddUniformData(new SimpleRender::ShaderDataFloat());
	}

	if(ImGui::Button("Add Uniform Vec2"))
	{
		application->Scene->DeferredRender->ShaderProgram->AddUniformData(new SimpleRender::ShaderDataVec2());
	}

	if(ImGui::Button("Add Uniform Vec3"))
	{
		application->Scene->DeferredRender->ShaderProgram->AddUniformData(new SimpleRender::ShaderDataVec3());

	}


	if(ImGui::Button("Reload Shader"))
	{
		application->Scene->UpdateDeferredRender();
	}

	ImGui::End();

}



