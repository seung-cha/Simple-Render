#pragma once

#include <string>
#include <glad/glad.h>
#include "imgui.h"
#include <glm/glm.hpp>

namespace SimpleRender
{
	class RenderScene;




	class ShaderProgramData
	{
	public:

		static enum RefType
		{
			RunTimei,
			RunTimef,
			LeftClickCont,
			RightClickCont,
			AspectRatio,
			AspectRatioFixed,
			Resoltion,
			ResolutionFixed,
			MousePos,
			MouseDelta,
			ObjPos,
			ObjRot,
			ObjScal,
		};
		
		void* data = nullptr;
		bool ReadOnly = false;
		std::string name = "";
		RefType ReferenceType;


		virtual ~ShaderProgramData()
		{

		}

		ShaderProgramData()
		{

		}


		ShaderProgramData(std::string name) : name(name)
		{
			
		}

		/// <summary>
		/// send the containing data to the shader program.
		/// Assumes shaderProgram is in use prior to calling this function.
		/// </summary>
		virtual void Apply(GLuint shaderProgram) = 0;

		/// <summary>
		/// Let the data pointer point to its internal variable (i.e make it constant)
		/// </summary>
		virtual void ToConstant()
		{
			ReadOnly = false;
			// Logic to change data pointer will be wrritten by child classes
		}

		/// <summary>
		/// Convert this program data to track a variable.
		/// Becomes readonly.
		/// </summary>
		/// <param name="data"></param>
		virtual void ToVariable(void* data)
		{
			ReadOnly = true;
			this->data = data;
		}


		/// <summary>
		/// Draw UI to manipulate this value. Assumes ImGui::Begin() is called beforehand.
		/// </summary>
		virtual void DrawUI() = 0;


		/// <summary>
		/// Draw ImGui pop up to select variable pointers.
		/// Assumes this is called between ImGui::BeginPopupContextItem() and ImGui::EndPopup().
		/// This may call ImGui::CloseCurrentPopup() to close the popup.
		/// </summary>
		/// <param name="scene"></param>
		virtual void VariablePopup(RenderScene* scene) = 0;
		


	};








	class ShaderDataFloat : public ShaderProgramData
	{
	public:

		ShaderDataFloat()
		{
			ToConstant();
		}

		void Apply(GLuint shaderProgram) override;
		void DrawUI() override;

		void ToConstant() override
		{
			ShaderProgramData::ToConstant();
			data = static_cast<void*>(&value);
		}

		void VariablePopup(RenderScene* scene) override;

	private:
		float value = 0.0f;

	};









	class ShaderDataInt : public ShaderProgramData
	{
	public:
		ShaderDataInt()
		{
			ToConstant();
		}

		void Apply(GLuint shaderProgram) override;
		void DrawUI() override;

		void ToConstant() override
		{
			ShaderProgramData::ToConstant();
			data = static_cast<void*>(&value);
		}

		void VariablePopup(RenderScene* scene) override;

	private:
		int value = 0.0f;

	};








	class ShaderDataVec2 : public ShaderProgramData
	{
	public:
		ShaderDataVec2()
		{
			ToConstant();
		}

		void Apply(GLuint shaderProgram) override;
		void DrawUI() override;

		void ToConstant() override
		{
			ShaderProgramData::ToConstant();
			data = static_cast<void*>(&value);
		}

		void VariablePopup(RenderScene* scene) override;

	private:
		glm::vec2 value = glm::vec2(0.0f);

	};









	class ShaderDataVec3 : public ShaderProgramData
	{
	public:
		ShaderDataVec3()
		{
			ToConstant();
		}

		~ShaderDataVec3() override;

		void Apply(GLuint shaderProgram) override;

		void DrawUI() override;

		void ToVariable(void* data) override;

		void ToConstant() override
		{
			ShaderProgramData::ToConstant();
			data = static_cast<void*>(&value);
		}

		void VariablePopup(RenderScene* scene) override;

	private:
		glm::vec3 value = glm::vec3(0.0f);

	};


}