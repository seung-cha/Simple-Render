#pragma once

#include <string>
#include <glad/glad.h>
#include "RenderShader/RenderShader.h"

#include "RenderPure/Disposable.h"

#include <iostream>
#include <unordered_set>

namespace SimpleRender 
{

	class RenderObject;

	enum ShaderProgramState
	{
		ShaderProgramNew,
		ShaderProgramLinked,
		ShaderProgramError
	};

	class RenderShaderProgram : public SimpleRenderPure::Disposable
	{
	public:

		RenderShaderProgram();

		inline void AttachShader(RenderShader* shader)
		{
			GLenum type = shader->Type();

			// Detach the shader from the program if exists
			if(shaders[type])
			{
				glDetachShader(programID, shaders[type]->ID());
				shaders[type]->ParentShaderPrograms->erase(this);
			}


			shaders[type] = shader;
			shaders[type]->ParentShaderPrograms->insert(this);
			glAttachShader(programID, shaders[type]->ID());

			std::cout << "Attached a " << RenderShader::ShaderTypeToString(shader->Type()) << " shader" << std::endl << std::endl;

		}

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

		std::unordered_set<RenderObject*>* AssociatedObjects = &associatedObjects;
		
		/// <summary>
		/// Delete the shader program.
		/// This object practically becomes useless.
		/// All objects that use this shader must not use it after calling this function.
		/// Attached shaders are automatically detached by OpenGL.
		/// </summary>
		virtual void Dispose() override;


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


		
	private:


		std::unordered_set<RenderObject*> associatedObjects;

		enum ShaderProgramState state = ShaderProgramNew;
		GLuint programID;
		RenderShader* shaders[3] = {nullptr, nullptr, nullptr};

		
	};

}