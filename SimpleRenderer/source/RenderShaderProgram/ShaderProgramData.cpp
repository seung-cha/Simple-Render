#include "RenderShaderProgram/ShaderProgramData.h"
#include "RenderScene/RenderScene.h"
#include "RenderApplication/RenderApplication.h"
#include "RenderObject/RenderObject.h"


void SimpleRender::ShaderDataInt::VariablePopup(RenderScene* scene)
{
	if(ImGui::Button("Run Time"))
	{
		ToVariable(&scene->Application->Status->Timei);
		ReferenceType = ShaderProgramData::RefType::RunTimei;

		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Left Click (Continuous)"))
	{
		ToVariable(&scene->Application->Status->Mouse->LeftClick);
		ReferenceType = ShaderProgramData::RefType::LeftClickCont;

		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Right Click (Continuous)"))
	{
		ToVariable(&scene->Application->Status->Mouse->RightClick);
		ReferenceType = ShaderProgramData::RefType::RightClickCont;

		ImGui::CloseCurrentPopup();
	}

}

void SimpleRender::ShaderDataFloat::VariablePopup(RenderScene* scene)
{
	if(ImGui::Button("Run Time"))
	{
		ToVariable(&scene->Application->Status->Timef);
		ReferenceType = ShaderProgramData::RefType::RunTimef;


		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Aspect Ratio"))
	{
		ToVariable(&scene->Application->Status->AspectRatio);
		ReferenceType = ShaderProgramData::RefType::AspectRatio;

		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Aspect Ratio (Fixed)"))
	{
		ToVariable(&scene->Application->Status->FixedAspectRatio);
		ReferenceType = ShaderProgramData::RefType::AspectRatioFixed;

		ImGui::CloseCurrentPopup();
	}

}


void SimpleRender::ShaderDataVec2::VariablePopup(RenderScene* scene)
{
	if(ImGui::Button("Resolution"))
	{
		ToVariable(&scene->Application->Status->Resolution);
		ReferenceType = ShaderProgramData::RefType::Resoltion;

		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Fixed Resolution"))
	{
		ToVariable(&scene->Application->Status->FixedResolution);
		ReferenceType = ShaderProgramData::RefType::ResolutionFixed;

		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Mouse Position"))
	{
		ToVariable(&scene->Application->Status->Mouse->MouseCoordinates);
		ReferenceType = ShaderProgramData::RefType::MousePos;

		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Mouse Delta"))
	{
		ToVariable(&scene->Application->Status->Mouse->MouseDelta);
		ReferenceType = ShaderProgramData::RefType::MouseDelta;

		ImGui::CloseCurrentPopup();
	}

}


void SimpleRender::ShaderDataVec3::VariablePopup(RenderScene* scene)
{
	if(!scene->ActiveObject)
		return;

	if(ImGui::Button("Active Object Position"))
	{

		ToVariable(scene->ActiveObject);
		ReferenceType = ShaderProgramData::RefType::ObjPos;

		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Active Object Rotation"))
	{

		ToVariable(scene->ActiveObject);
		ReferenceType = ShaderProgramData::RefType::ObjRot;

		ImGui::CloseCurrentPopup();
	}

	if(ImGui::Button("Active Object Scale"))
	{

		ToVariable(scene->ActiveObject);
		ReferenceType = ShaderProgramData::RefType::ObjScal;

		ImGui::CloseCurrentPopup();
	}


}

void SimpleRender::ShaderDataFloat::DrawUI()
{
	ImGui::BeginDisabled(ReadOnly);

	ImGui::DragFloat("", ReadOnly ? static_cast<float*>(data) : &value, 0.05f);

	ImGui::EndDisabled();

}


void SimpleRender::ShaderDataInt::DrawUI()
{
	ImGui::BeginDisabled(ReadOnly);

	ImGui::DragInt("", ReadOnly ? static_cast<int*>(data) : &value, 0.05f);

	ImGui::EndDisabled();

}

void SimpleRender::ShaderDataVec2::DrawUI()
{
	ImGui::BeginDisabled(ReadOnly);

	ImGui::DragFloat2("", ReadOnly ? &(*static_cast<glm::vec2*>(data))[0] : &value[0], 0.05f);

	ImGui::EndDisabled();

}

void SimpleRender::ShaderDataVec3::DrawUI()
{
	ImGui::BeginDisabled(ReadOnly);

	if(ReadOnly)
	{

		RenderObject* obj = static_cast<RenderObject*>(data);


		if(!obj)
		{
			ImGui::Text("Object reference is broken!");
		}
		else
		{
			switch(ReferenceType)
			{
			case ShaderProgramData::RefType::ObjPos:
				ImGui::DragFloat3("", &obj->Transform->Position[0]);

				break;

			case ShaderProgramData::RefType::ObjRot:
				ImGui::DragFloat3("", &obj->Transform->Rotation[0]);
				break;

			case ShaderProgramData::RefType::ObjScal:
				ImGui::DragFloat3("", &obj->Transform->Scale[0]);
				break;

			}

		}

	}
	else
	{
		ImGui::DragFloat3("", &value[0], 0.05f);
	}

	ImGui::EndDisabled();

}



void SimpleRender::ShaderDataVec3::ToVariable(void* data) 
{
	// Remove the reference to previous object, if exists
	RenderObject* obj = static_cast<RenderObject*>(this->data);

	if(ReadOnly && obj)
	{
		obj->ShaderReference.erase(this);
	}

	ShaderProgramData::ToVariable(data);

	// Insert reference to the object
	obj = static_cast<RenderObject*>(data);
	obj->ShaderReference.insert(this);

}


SimpleRender::ShaderDataVec3::~ShaderDataVec3()
{
	if(!ReadOnly)
	{
		return;
	}
	
	RenderObject* obj = static_cast<RenderObject*>(this->data);

	if(!obj)
	{
		return;
	}

	obj->ShaderReference.erase(this);

	
}



void SimpleRender::ShaderDataFloat::Apply(GLuint shaderProgram)
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), *static_cast<float*>(data));
}

void SimpleRender::ShaderDataInt::Apply(GLuint shaderProgram)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), *static_cast<int*>(data));
}

void SimpleRender::ShaderDataVec2::Apply(GLuint shaderProgram)
{
	glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &(*static_cast<glm::vec2*>(data))[0]);
}

void SimpleRender::ShaderDataVec3::Apply(GLuint shaderProgram)
{
	if(ReadOnly)
	{
		RenderObject* obj = static_cast<RenderObject*>(data);

		if(obj)
		{
			switch(ReferenceType)
			{
			case ShaderProgramData::RefType::ObjPos:
				glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &obj->Transform->Position[0]);
				break;

			case ShaderProgramData::RefType::ObjRot:
				glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &obj->Transform->Rotation[0]);
				break;

			case ShaderProgramData::RefType::ObjScal:
				glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &obj->Transform->Scale[0]);
				break;
			}
		}
		else
		{
			glm::vec3 v(0.0f, 0.0f, 0.0f);
			glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &v[0]);
		}


	

	}
	else
	{
		glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &(*static_cast<glm::vec3*>(data))[0]);
	}
}