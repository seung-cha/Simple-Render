#pragma once

#include <string>
#include <glad/glad.h>
#include "imgui.h"
#include <glm/glm.hpp>


namespace SimpleRender
{
	class ShaderProgramData
	{
	public:
		
		void* data = 0;
		bool readOnly = false;
		std::string name = "";

		/// <summary>
		/// Required for ImGui
		/// </summary>
		int ID = 0;
		std::string idstr = "idstr1 ";
		std::string idstr2 = "idstr2 ";

		virtual ~ShaderProgramData()
		{

		}

		ShaderProgramData(int ID)
		{
			this->ID = ID;
			idstr += ID;
			idstr2 += ID + 1;
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
		/// Draw UI to manipulate this value. Assumes ImGui::Begin() is called beforehand.
		/// </summary>
		virtual void DrawUI() = 0;

		


	};

	class ShaderDataFloat : public ShaderProgramData
	{
	public:
		ShaderDataFloat(int ID) : ShaderProgramData(ID)
		{
			data = static_cast<void*>(&value);
		}

		void Apply(GLuint shaderProgram) override
		{
			glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), *static_cast<float*>(data));
		}

		void DrawUI() override
		{
			ImGui::BeginDisabled(readOnly);


			ImGui::DragFloat(idstr.c_str(), readOnly ? static_cast<float*>(data) : &value, 0.05f);

			ImGui::EndDisabled();

		}

	private:
		float value = 0.0f;

	};

	class ShaderDataInt : public ShaderProgramData
	{
	public:
		ShaderDataInt(int ID) : ShaderProgramData(ID)
		{
			data = static_cast<void*>(&value);
		}

		void Apply(GLuint shaderProgram) override
		{
			glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), *static_cast<int*>(data));
		}

		void DrawUI() override
		{
			ImGui::BeginDisabled(readOnly);

			ImGui::DragInt(idstr.c_str(), readOnly ? static_cast<int*>(data) : &value, 0.05f);

			ImGui::EndDisabled();

		}

	private:
		int value = 0.0f;

	};

	class ShaderDataVec2 : public ShaderProgramData
	{
	public:
		ShaderDataVec2(int ID) : ShaderProgramData(ID)
		{
			data = static_cast<void*>(&value);
		}

		void Apply(GLuint shaderProgram) override
		{
			glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &(*static_cast<glm::vec2*>(data))[0]);
		}

		void DrawUI() override
		{
			ImGui::BeginDisabled(readOnly);

	
			ImGui::DragFloat2(idstr.c_str(), readOnly ? &(*static_cast<glm::vec2*>(data))[0] : &value[0], 0.05f);

			ImGui::EndDisabled();

		}

	private:
		glm::vec2 value = glm::vec2(0.0f);

	};

	class ShaderDataVec3 : public ShaderProgramData
	{
	public:
		ShaderDataVec3(int ID) : ShaderProgramData(ID)
		{
			data = static_cast<void*>(&value);
		}

		void Apply(GLuint shaderProgram) override
		{
			glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &(*static_cast<glm::vec3*>(data))[0]);
		}

		void DrawUI() override
		{
			ImGui::BeginDisabled(readOnly);

			ImGui::DragFloat3(idstr.c_str(), readOnly ? &(*static_cast<glm::vec3*>(data))[0] : &value[0], 0.05f);

			ImGui::EndDisabled();

		}

	private:
		glm::vec3 value = glm::vec3(0.0f);

	};



}