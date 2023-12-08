#pragma once

#include <glad/glad.h>

#include <vector>
#include <iostream>

#include "RenderShaderProgram/RenderShaderProgram.h"
#include "RenderShader/RenderShader.h"
#include "RenderCamera/RenderCamera.h"

// To do: Consider using different data structure for Scene elements

namespace SimpleRender
{
	// Forward declare all classes
	class RenderObject;


	class RenderScene
	{
	public:
		RenderScene(int width, int height);
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

		std::vector<RenderObject*>* SceneObjects = &objects;
		std::vector<RenderCamera*>* SceneCameras = &cameras;

		std::vector<RenderShader*>* SceneVertexShaders = &vertexShaders;
		std::vector<RenderShader*>* SceneFragmentShaders = &fragmentShaders;
		std::vector<RenderShader*>* SceneGeometryShaders = &geometryShaders;

		std::vector<RenderShaderProgram*>* SceneShaderPrograms = &shaderPrograms;
		
		RenderCamera* ActiveCamera = nullptr;
		RenderObject* ActiveObject = nullptr;
		RenderShaderProgram* ActiveShaderProgram = nullptr;
		RenderShader* ActiveShader = nullptr;

		GLuint* SceneFrameBuffer = &framebuffer;
		GLuint* SceneTexture = &screenTexture;

		int* Width = &width;
		int* Height = &height;

	private:

		int width, height;

		std::vector<RenderObject*> objects;
		std::vector<RenderCamera*> cameras;

		std::vector<RenderShader*> vertexShaders;
		std::vector<RenderShader*> fragmentShaders;
		std::vector<RenderShader*> geometryShaders;

		std::vector<RenderShaderProgram*> shaderPrograms;

		GLuint framebuffer = 0;
		GLuint screenTexture = 0;
	};


}