#pragma once

#include <glad/glad.h>

#include <vector>
#include <iostream>

#include "RenderShaderProgram/RenderShaderProgram.h"
#include "RenderShader/RenderShader.h"
#include "RenderCamera/RenderCamera.h"


namespace SimpleRender
{
	// Forward declare all classes
	class RenderObject;


	class RenderScene
	{
	public:
		RenderScene();
		void LoadDefaultScene();

		void DrawScene();

		/// <summary>
		/// Free allocated memory.
		/// As of now does nothing.
		/// Should implement an interface to release OpenGL IDs of each class.
		/// </summary>
		inline void Dispose()
		{

		}


		inline std::vector<RenderShader*>* GetShadersOfType(enum ShaderType type)
		{
			if(type == ShaderType::Vertex)
				return SceneVertexShaders;
			else if(type == ShaderType::Fragment)
				return SceneFragmentShaders;
			else
				return SceneGeometryShaders;
		}

		std::vector<RenderObject*>* SceneObjects;
		std::vector<RenderCamera*>* SceneCameras;

		std::vector<RenderShader*>* SceneVertexShaders;
		std::vector<RenderShader*>* SceneFragmentShaders;
		std::vector<RenderShader*>* SceneGeometryShaders;

		std::vector<RenderShaderProgram*>* SceneShaderPrograms;
		
		RenderCamera* ActiveCamera = nullptr;
		RenderObject* ActiveObject = nullptr;

	private:

	};


}