#pragma once

#include <glad/glad.h>

#include <vector>
#include <iostream>

#include <RenderObject/RenderObject.h>
#include <RenderShaderProgram/RenderShaderProgram.h>
#include <RenderShader/RenderShader.h>
#include <RenderCamera/RenderCamera.h>


namespace SimpleRender
{

	class RenderScene
	{
	public:
		void LoadDefaultScene();

		// To do: Associate a shader program to each object
		// So that they can be drawn uniquely.
		// For now, use only one shader.
		inline void DrawScene(GLuint& program)
		{
			glUseProgram(program);

			glUniformMatrix4fv(glGetUniformLocation(program, "transform.Perspective"), 1, GL_FALSE, &ActiveCamera->PerspectiveMatrix()[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(program, "transform.View"), 1, GL_FALSE, &ActiveCamera->ViewMatrix()[0][0]);

			for(auto& object : SceneObjects)
			{
				object.Draw(program);
			}

			glUseProgram(0); 

		}


		inline std::vector<RenderShader>* GetShadersOfType(enum ShaderType type)
		{
			if(type == ShaderType::Vertex)
				return &SceneVertexShaders;
			else if(type == ShaderType::Fragment)
				return &SceneFragmentShaders;
			else
				return &SceneGeometryShaders;
		}

		std::vector<RenderObject> SceneObjects;
		std::vector<RenderCamera> SceneCameras;

		std::vector<RenderShader> SceneVertexShaders;
		std::vector<RenderShader> SceneFragmentShaders;
		std::vector<RenderShader> SceneGeometryShaders;

		std::vector<RenderShaderProgram> SceneShaderPrograms;
		
		RenderCamera* ActiveCamera;
		RenderObject* ActiveObject;

	private:

	};


}