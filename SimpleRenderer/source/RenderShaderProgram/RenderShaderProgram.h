#pragma once

#include <string>
#include <glad/glad.h>
#include "RenderShader/RenderShader.h"
#include "RenderPure/Disposable.h"

#include "ShaderProgramData.h"

#include <iostream>
#include <unordered_set>
#include <memory>


namespace SimpleRender 
{

	class RenderObject;

	enum ShaderProgramState
	{
		ShaderProgramNew,
		ShaderProgramLinked,
		ShaderProgramError
	};

	class RenderShaderProgram
	{
	public:

		RenderShaderProgram();
		~RenderShaderProgram();
		void AttachShader(RenderShader* shader);

		inline void DetachShader(enum ShaderType type)
		{
			if(shaders[type])
			{
				glDetachShader(programID, shaders[type]->ID());
				shaders[type]->ParentShaderPrograms->erase(this);
				shaders[type] = nullptr;
			}

		}

		inline void DetachAllShaders()
		{
			for(int i = 0; i < 3; i++)
			{
				if(shaders[i])
					DetachShader(shaders[i]->Type());
			}

		}

		void LinkProgram();

		inline bool IsShaderAttached(enum ShaderType type)
		{
			return shaders[type];
		}

		inline bool IsShaderAttached(int index)
		{
			return shaders[index];
		}



		inline GLuint ID()
		{
			return programID;
		}

		inline enum ShaderProgramState State()
		{
			return state;
		}
 
		static inline std::string ShaderProgramStateToString(enum ShaderProgramState state)
		{
			if(state == ShaderProgramNew)
				return "New";
			else if(state == ShaderProgramLinked)
				return "Linked";
			else
				return "Error";
		}

		
		std::unordered_set<RenderObject*>* const AssociatedObjects = &associatedObjects;
		std::vector<ShaderProgramData*>* const UniformData = &programData;

		/// <summary>
		/// Apply all data in UniformData to this GLSL shader.
		/// shader program is unbound afterwards.
		/// </summary>
		void ApplyUniformVariables();
		
	private:


		std::unordered_set<RenderObject*> associatedObjects;

		std::vector<ShaderProgramData*> programData;



		enum ShaderProgramState state = ShaderProgramNew;
		GLuint programID;
		RenderShader* shaders[3] = {nullptr, nullptr, nullptr};

		
	};

}